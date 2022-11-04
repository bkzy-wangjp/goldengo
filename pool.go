package goldengo

import (
	"fmt"
	"strings"
	"sync"
	"time"
)

//庚顿的部分需要重新连接的错误码
var _Golden_Err_Codes = []string{
	"0xFFFF2005", // 无效的句柄
	"0xFFFFA746",
	"0xFFFFA745",
	"0xFFFFA736",
	"0xFFFFC010",
	"0xFFFF703C", // 连接请求超时，未能建立连接
	"0xFFFF703D", // 连接被拒绝
	"0xFFFF703E", // 连接被关闭
}

//庚顿数据库结构
type GoldenConnect struct {
	RTDBService
}

//庚顿工作池结构
type GoldenPool struct {
	Worker     chan int   //工作通道
	Req        chan int   //请求队列
	Handel     chan int32 //连接池句柄
	Tenant     sync.Map   //注册的租户map,key为Handel,value为租户字符串
	BegineTime sync.Map   //注册的租户map,key为Handel,value为起租时间
	size       int        //工作池大小
	maxSec     int64      //最长租借时间(秒)
	hostname   string     //主机IP
	username   string     //用户名
	password   string     //密码
	port       int        //端口号
	isclose    bool       //关闭指令
	Version    string     //版本号
}

/*******************************************************************************
- 功能:实例化庚顿工作池
- 参数:
	[hostname]  字符串，输入，GOLDEN 数据平台服务器的网络地址或机器名
	[username]	用户名,字符串,缺省值 sa
	[password]	密码,字符串,缺省值 golden
	[port]      端口号,整型,缺省值 6327
	[cap]       连接池大小,最小1,最大50
	[max_sec]   最大租借时间(秒)
- 输出:[*GoldenPool] 连接池指针
	[error] 创建句柄连接池时候的错误信息
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func NewGoldenPool(hostname, username, password string, port, cap int, max_sec ...int64) (*GoldenPool, error) {
	if port == 0 {
		port = 6327
	}
	if cap < 1 {
		cap = 1
	}
	if cap > 50 {
		cap = 50
	}
	var maxSec int64 = 3600
	if len(max_sec) > 0 {
		maxSec = max_sec[0]
		if maxSec < 60 {
			maxSec = 60
		}
	}

	pool := &GoldenPool{
		Worker:   make(chan int, cap),   //工作者通道
		Req:      make(chan int, 10000), //请求通道数量
		Handel:   make(chan int32, cap), //池句柄池
		size:     cap,                   //工作池大小
		maxSec:   maxSec,                //超时时间
		hostname: hostname,              //Golden数据库主机名
		username: username,              //用户名
		password: password,              //密码
		port:     port,                  //端口号
		Version:  "v1.0.2102",
	}
	var err error
	for i := 0; i < cap; i++ { //创建句柄连接池
		g := new(GoldenConnect)
		g.HostName = hostname
		g.UserName = username
		g.Password = password
		g.Port = port
		g.Handle = -1
		if err != nil {
			e := g.connect()
			if e != nil { //如果有错误
				err = e //记录错误信息
			}
		}
		pool.Handel <- g.Handle //将句柄压入连接池
	}
	go pool.run()
	return pool, err
}

/*******************************************************************************
- 功能:连接池运行
- 参数:无
- 输出:无
- 备注: 自动释放超时的链接
- 时间: 2021年4月14日
*******************************************************************************/
func (p *GoldenPool) run() {
	defer p.removePool()
	for {
		if p.isclose { //有退出指令
			break
		}
		if len(p.Worker) > 0 {
			p.BegineTime.Range(func(k, v interface{}) bool {
				bgt, _ := v.(time.Time)
				//超时资源自动释放
				if bgt.Before(time.Now().Add(-1 * time.Second * time.Duration(p.maxSec))) {
					g := new(GoldenConnect)
					g.Handle, _ = k.(int32)
					g.DisConnect(p)
				}
				return true
			})
		}
		time.Sleep(time.Second * 5)
	}
}

/*******************************************************************************
- 功能:删除庚顿连接池通道资源
- 参数:无
- 输出:无
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func (p *GoldenPool) removePool() {
	close(p.Worker)
	close(p.Req)
	for h := range p.Handel {
		g := new(GoldenConnect)
		g.Handle = h
		g.disConnect()
	}
	close(p.Handel)
}

func (p *GoldenPool) Close() {
	p.isclose = true
}

/*******************************************************************************
- 功能:显示租户信息
- 参数:无
- 输出:[Handel,TenantName]结构体组
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func (p *GoldenPool) ShowTenant() interface{} {
	type tenant struct {
		Handel     int32
		BegineTime time.Time
		TenantName string
	}
	var tenants []tenant
	p.Tenant.Range(func(k, v interface{}) bool {
		bgt, _ := p.BegineTime.Load(k)
		t := tenant{
			Handel:     k.(int32),
			BegineTime: bgt.(time.Time),
			TenantName: v.(string),
		}
		tenants = append(tenants, t)
		return true
	})
	return tenants
}

/*******************************************************************************
- 功能:请求一个庚顿连接句柄
- 参数:[tenant string]可选的租户名称
- 输出:
	[*Golden] 庚顿数据库连接指针
	[error] 错误信息
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func (p *GoldenPool) GetConnect(tenant ...string) (*GoldenConnect, error) {
	var tenantstr string //租户名称
	for i, str := range tenant {
		if i != 0 {
			tenantstr += "."
		}
		tenantstr += str
	}

	p.Req <- 1
	g := new(GoldenConnect)
	//select { //有资源就分配资源，没有资源就阻塞等待
	//case
	p.Worker <- 1         //有资源可分配
	g.Handle = <-p.Handel //从连接池取句柄
	<-p.Req               //请求数量减少
	//}
	//从连接池获取基本信息
	g.HostName = p.hostname
	g.UserName = p.username
	g.Password = p.password
	g.Port = p.port
	_, err := g.HostTime() //测试句柄
	if err != nil {
		//无效的句柄\远程主机强迫关闭了一个现有的连接\你的主机中的软件中止了一个已建立的连接
		if stringContains(err.Error(), _Golden_Err_Codes...) {
			err = g.connect() //重新创建句柄
			if err != nil {   //创建连接失败
				g.Handle = 0x0FFFFFFF
				g.DisConnect(p) //释放资源
			}
		}
	}

	if g.Handle != 0 {
		p.Tenant.Store(g.Handle, tenantstr)      //记录租户名称
		p.BegineTime.Store(g.Handle, time.Now()) //记录起租时间
	}
	return g, err
}

/*******************************************************************************
- 功能:请求一个庚顿连接句柄
- 参数:无
- 输出:
	[error] 错误信息
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func (g *GoldenConnect) GetConnect(p *GoldenPool, tenant ...string) error {
	if g.Handle <= 0 { //是否已经获取了句柄
		var tenantstr string //租户名称
		for i, str := range tenant {
			if i != 0 {
				tenantstr += "."
			}
			tenantstr += str
		}

		p.Req <- 1
		//select { //有资源就分配资源，没有资源就阻塞等待
		//case
		p.Worker <- 1         //有资源可分配
		g.Handle = <-p.Handel //从连接池取句柄
		<-p.Req               //请求数量减少
		//}
		//从连接池获取基本信息
		g.HostName = p.hostname
		g.UserName = p.username
		g.Password = p.password
		g.Port = p.port
		_, err := g.HostTime() //测试句柄
		if err != nil {
			//无效的句柄\远程主机强迫关闭了一个现有的连接\你的主机中的软件中止了一个已建立的连接
			if stringContains(err.Error(), _Golden_Err_Codes...) {
				err = g.connect() //重新创建句柄
				if err != nil {   //创建连接失败
					g.Handle = 0x0FFFFFFF
					g.DisConnect(p) //释放资源
				}
			}
		}
		if g.Handle != 0 {
			p.Tenant.Store(g.Handle, tenantstr)      //记录租户名称
			p.BegineTime.Store(g.Handle, time.Now()) //记录起租时间
		}
		return err
	} else { //已经获取了句柄
		return nil
	}
}

/*******************************************************************************
- 功能:断开连接
- 参数:[p *GoldenPool] 庚顿连接池指针
- 输出:无
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func (g *GoldenConnect) DisConnect(p *GoldenPool) {
	if g.Handle > 0 { //有资源的时候才准许释放
		<-p.Worker                    //释放连接资源
		p.Handel <- g.Handle          //归还句柄到连接池
		p.Tenant.Delete(g.Handle)     //删除租户记录
		p.BegineTime.Delete(g.Handle) //删除起租时间
		g.Handle = 0                  //复位
	}
}

/*******************************************************************************
- 功能:字符串是否包含子字符串
- 参数:[s string] 待检测字符串
	[substrs ...string] 子字符串切片
- 输出:如果字符串中含有任意一个子字符串，则返回true,否则返回false
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func stringContains(s string, substrs ...string) bool {
	for _, sub := range substrs {
		if strings.Contains(s, sub) {
			return true
		}
	}
	return false
}

/*******************************************************************************
- 功能: 通过变量全名获取快照值
- 参数:
	[tagfullnames]  字符串切片，输入. 变量全名格式:tablename.tagname
- 输出:
	[map[string]SnapData] 快照Map,key为变量全名
	[error] 错误信息
- 备注:
- 时间: 2020年5月15日
*******************************************************************************/
func (p *GoldenPool) GetSnapShotByName(tagfullnames ...string) (map[string]SnapData, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	return g.GetSnapShotByName(tagfullnames...)
}

/*******************************************************************************
- 功能: 通过变量id获取快照值
- 参数:
	[ids]  id切片，输入
- 输出:
	[map[int]SnapData] 快照Map,key为变量全名
	[error] 错误信息
- 备注:
- 时间: 2020年5月15日
*******************************************************************************/
func (p *GoldenPool) GetSnapShotById(ids, dtypes []int) (map[int]SnapData, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	return g.GetSnapShotById(ids, dtypes)
}

/*******************************************************************************
- 功能: 通过变量全名获取历史数据值
- 参数:
	[bgtime]   整型，输入，表示起始时间UnixNano秒数。如果为 0，表示从存档中最早时间的数据开始读取
    [endtime]  整型，输入，表示结束时间UnixNano秒数。如果为 0，表示读取直至存档中数据的最后时间
	[tagfullnames]  字符串切片，输入. 变量全名格式:tablename.tagname
- 输出:
	[map[string][]RealTimeSeriesData] 历史Map,key为变量全名
	[error] 错误信息
- 备注:
- 时间: 2020年5月15日
*******************************************************************************/
func (p *GoldenPool) GetHistoryByName(bgtime, endtime int64, tagfullnames ...string) (map[string][]RealTimeSeriesData, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	return g.GetHistoryByName(bgtime, endtime, tagfullnames...)
}

/*******************************************************************************
- 功能: 通过变量全名获取历史数据统计信息
- 参数:
	[bgtime]   整型，输入，表示起始时间UnixNano秒数。如果为 0，表示从存档中最早时间的数据开始读取
    [endtime]  整型，输入，表示结束时间UnixNano秒数。如果为 0，表示读取直至存档中数据的最后时间
	[tagfullnames]  字符串切片，输入. 变量全名格式:tablename.tagname
- 输出:
	[max_time]    整形,最大值对应的Unix毫秒时间.如果为 0,则表示无最大值
	[min_time]    整形,最小值对应的Unix毫秒时间.如果为 0,则表示无最小值
    [max_value]   双精度浮点型，输出，表示统计时间段内的最大数值。
    [min_value]   双精度浮点型，输出，表示统计时间段内的最小数值。
    [total_value] 双精度浮点型，输出，表示统计时间段内的累计值，结果的单位为标签点的工程单位。
    [calc_avg]    双精度浮点型，输出，表示统计时间段内的算术平均值。
    [power_avg]   双精度浮点型，输出，表示统计时间段内的加权平均值。
    [count]       整型，输出，表示统计时间段内用于计算统计值的数据个数。
    [error]       错误信息
- 备注:如果输出的最大值或最小值的时间戳秒值为 0，则表明仅有累计值和加权平均值输出有效，其余统计结果无效。
  	本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
- 时间: 2020年12月04日
*******************************************************************************/
func (p *GoldenPool) GetHistorySummaryByName(bgtime, endtime int64, tagfullname string) (int64,
	int64, float64, float64, float64, float64, float64, int, error) {
	g, err := p.GetConnect()
	if err != nil {
		return 0, 0, 0., 0., 0., 0., 0., 0, err
	}
	defer g.DisConnect(p)
	return g.GetHistorySummaryByName(bgtime, endtime, tagfullname)
}

/*******************************************************************************
- 功能: 通过变量全名获取单个时间点的历史数据值
- 参数:
	[mode]   整型，输入，取值 GOLDEN_NEXT(0)、GOLDEN_PREVIOUS(1)、GOLDEN_EXACT(2)、
    			GOLDEN_INTER(3) 之一:
    				 GOLDEN_NEXT(0) 寻找下一个最近的数据；
   					 GOLDEN_PREVIOUS(1) 寻找上一个最近的数据；
    				 GOLDEN_EXACT(2) 取指定时间的数据，如果没有则返回错误 GoE_DATA_NOT_FOUND；
    				 GOLDEN_INTER(3) 取指定时间的内插值数据。
    [datatime]  整型，输入，时间UnixNano秒数。
	[tagfullnames]  字符串切片，输入. 变量全名格式:tablename.tagname
- 输出:
	[map[string]RealTimeSeriesData] 快照Map,key为变量全名
	[error] 错误信息
- 备注:
- 时间: 2020年5月15日
*******************************************************************************/
func (p *GoldenPool) GetHistorySingleByName(mode int, datatime int64, tagfullnames ...string) (map[string]RealTimeSeriesData, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	return g.GetHistorySingleByName(mode, datatime, tagfullnames...)
}

/*******************************************************************************
- 功能: 通过变量全名获取等间隔历史数据值
- 参数:
	[count]	整形,需要的插值个数
	[bgtime]   整型，输入，表示起始时间UnixNano秒数。如果为 0，表示从存档中最早时间的数据开始读取
    [endtime]  整型，输入，表示结束时间UnixNano秒数。如果为 0，表示读取直至存档中数据的最后时间
	[tagfullnames]  字符串切片，输入. 变量全名格式:tablename.tagname
- 输出:
	[map[string][]RealTimeSeriesData] 快照Map,key为变量全名
	[error] 错误信息
- 备注:
- 时间: 2020年5月15日
*******************************************************************************/
func (p *GoldenPool) GetHisIntervalByName(count int, bgtime, endtime int64, tagfullnames ...string) (map[string][]RealTimeSeriesData, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	return g.GetHisIntervalByName(count, bgtime, endtime, tagfullnames...)
}

/*******************************************************************************
功能:获取补全了开头和结尾时刻数据的历史数据
输入:[bginTime] 开始时间,UnixNano
	[endTime] 结束时间,UnixNano
	[Interval] 两个数据点之间的间隔时间,单位:秒.如果不大于0，则读取原始历史数据.如果大于零,则读取等间隔差值历史数据
				如果Interval小于0,则不对开头和结尾的数据进行补全
	[tagnames] 变量名,至少要有一个,可以为多个
输出:[map[string][]RealTimeSeriesData] 数据Map,以变量名为key
	[map[string]error] 变量的错误信息Map,以变量名为key
	[map[string]bool] 快照数据时间大于endTime,则为true,否则为false
	[error]
时间:2020年5月16日
编辑:wang_jp
*******************************************************************************/
func (p *GoldenPool) GetHistoryDataAlignHeadAndTail(bgtime, endtime int64, Interval int, tagfullnames ...string) (map[string]HisData, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	return g.GetHistoryDataAlignHeadAndTail(bgtime, endtime, Interval, tagfullnames...)
}

/*******************************************************************************
功能:获取表中的标签点名称列表
输入:可选的表名称列表
输出:标签点表Map,Map的key为表名
说明:如果不输入表名,则读取数据库中所有表下的标签点
	如果输入表名,则读取输入的每个表下的标签点
	如果输入的表不存在,对应的map下的字符串切片为空
时间:2020年5月16日
编辑:wang_jp
*******************************************************************************/
func (p *GoldenPool) GetTagNameListInTables(tbnames ...string) (map[string][]string, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	return g.GetTagNameListInTables(tbnames...)
}

/*******************************************************************************
功能:获取表中的标签点列表
输入:可选的表名称列表
输出:标签点表Map,Map的key为表名
说明:如果不输入表名,则读取数据库中所有表下的标签点
	如果输入表名,则读取输入的每个表下的标签点
	如果输入的表不存在,对应的map下的字符串切片为空
时间:2020年5月16日
编辑:wang_jp
*******************************************************************************/
func (p *GoldenPool) GetTagListInTables(tbnames ...string) (map[string][]GoldenPoint, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	return g.GetTagListInTables(tbnames...)
}

/*******************************************************************************
功能:根据标签点全名获取标签点的配置信息
输入:标签点名列表
输出:标签点Map,Map的key为标签名
说明:
时间:2020年5月16日
编辑:wang_jp
*******************************************************************************/
func (p *GoldenPool) GetTagPointInfoByName(tagnames ...string) (map[string]GoldenPoint, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	return g.GetTagPointInfoByName(tagnames...)
}

/*******************************************************************************
功能:根据标签点全名获取标签点的配置信息
输入:标签点ID
输出:标签点和错误信息
说明:
时间:2020年5月16日
编辑:wang_jp
*******************************************************************************/
func (p *GoldenPool) GetTagPointInfoById(id int) (GoldenPoint, error) {
	g, err := p.GetConnect()
	if err != nil {
		var gdp GoldenPoint
		return gdp, err
	}
	defer g.DisConnect(p)
	return g.GetSinglePointPropterty(id)
}

/*******************************************************************************
功能:根据标签点名写快照
输入:[tagname]   标签点全名
	[datavalue] 数值
	[qualitie]  质量码
	[datatime]  可选的时间,UnixNano。省略时采用当前服务器时间
输出:
说明:
时间:2020年5月16日
编辑:wang_jp
*******************************************************************************/
func (p *GoldenPool) SetSnapShot(tagname string, datavalue float64, qualitie int, datatime ...int64) error {
	g, err := p.GetConnect()
	if err != nil {
		return err
	}
	defer g.DisConnect(p)
	return g.SetSnapShot(tagname, datavalue, qualitie, datatime...)
}

/*******************************************************************************
功能:批量写快照
输入:[tagnames]   标签点全名.同一个标签点标识可以出现多次，但它们的时间戳必需是递增的
	[datavalues] 数值
	[qualities]  质量码
	[datatimes]  时间,UnixNano
输出:
说明:
时间:2020年5月16日
编辑:wang_jp
*******************************************************************************/
func (p *GoldenPool) SetSnapShotBatch(tagnames []string, datavalues []float64, qualities []int, datatimes []int64) error {
	g, err := p.GetConnect()
	if err != nil {
		return err
	}
	defer g.DisConnect(p)
	return g.SetSnapShotBatch(tagnames, datavalues, qualities, datatimes)
}

/*******************************************************************************
功能:根据标签点名写历史值
输入:[tagname]   标签点全名
	[datavalue] 数值
	[qualitie]  质量码
	[datatime]  可选的时间,UnixNano。省略时采用当前服务器时间
输出:
说明:
时间:2020年8月14日
编辑:wang_jp
*******************************************************************************/
func (p *GoldenPool) SetArchivedValue(tagname string, datavalue float64, qualitie int, datatime ...int64) error {
	g, err := p.GetConnect()
	if err != nil {
		return err
	}
	defer g.DisConnect(p)
	return g.SetArchivedValue(tagname, datavalue, qualitie, datatime...)
}

/*******************************************************************************
功能:根据标签点名批量写历史值
输入:[tagnames]   标签点全名.同一个标签点标识可以出现多次，但它们的时间戳必需是递增的
	[datavalues] 数值
	[qualities]  质量码
	[datatimes]  时间,UnixNano
输出:
说明:
时间:2020年8月14日
编辑:wang_jp
*******************************************************************************/
func (p *GoldenPool) SetArchivedValuesBatch(tagnames []string, datavalues []float64, qualities []int, datatimes []int64) error {
	g, err := p.GetConnect()
	if err != nil {
		return err
	}
	defer g.DisConnect(p)
	return g.SetArchivedValuesBatch(tagnames, datavalues, qualities, datatimes)
}

/***************************************************
功能:读取庚顿服务器时间
输入:无
输出:时间,err
时间:2020年3月19日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) GetServerTime() (time.Time, error) {
	var st time.Time
	g, err := p.GetConnect()
	if err != nil {
		return st, err
	}
	defer g.DisConnect(p)
	t, err := g.HostTime()
	if err != nil {
		return st, err
	}
	st = time.UnixMilli(int64(t) * 1e3)
	return st, nil
}

/***************************************************
功能:读取庚顿服务器版本号
输入:无
输出:版本号,err
时间:2020年3月19日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) GetApiVersion() (string, error) {
	g, err := p.GetConnect()
	if err != nil {
		return "", err
	}
	defer g.DisConnect(p)
	return g.GetAPIVersion()
}

/***************************************************
功能:读取庚顿服务器数据标签点
输入:无
输出:map[int]GoldenPoint,err
时间:2022年3月20日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) Points() (map[int]GoldenPoint, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	////////////////////////////////////////////////////////////////
	err = g.GetTables(true)
	return g.Points, err
}

/***************************************************
功能:读取庚顿服务器数据标签表
输入:[selector] 不输入或者0:读取数据表列表,反馈为数据表列表的map,以表id为key([]goldengo.Tables)
		1: 读取数据表列表,反馈为数据表ID数组([]int)
		2: 读取数据表列表,反馈为数据表名字符串数组([]string)
		其他:同0
输出:数据接口,err
时间:2020年3月19日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) TablesGet(selector ...int) (interface{}, error) {
	g, err := p.GetConnect()
	if err != nil {
		return nil, err
	}
	defer g.DisConnect(p)
	////////////////////////////////////////////////////////////////
	err = g.GetTables()
	if err != nil {
		return nil, err
	}
	if len(selector) > 0 {
		switch selector[0] {
		case 1:
			return g.TableIds, err //返回ID数组
		case 2:
			var names []string
			for _, id := range g.TableIds {
				names = append(names, g.Tables[id].Name)
			}
			return names, nil //返回表名数组
		default:
			return g.Tables, nil //返回表信息Map
		}
	}
	return g.Tables, nil
}

/***************************************************
功能:根据表名读取庚顿服务器数据标签表信息
输入:[tablenames] 零个一个或者多个数据表名,如果不输入,则返回所有表的信息
输出:map[string]goldengo.GoldenTable,以表名为Key
	err,错误信息
时间:2020年3月19日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) TablesPropertys(tablenames ...string) (map[string]GoldenTable, error) {
	datas := make(map[string]GoldenTable)
	tabp, err := p.TablesGet(0)
	if err != nil {
		return datas, err
	}
	tbinfs, _ := tabp.(map[int]GoldenTable)
	if len(tablenames) == 0 {
		for _, tb := range tbinfs {
			datas[tb.Name] = tb
		}
	} else {
		var gdtb GoldenTable
		for _, name := range tablenames {
			for _, tb := range tbinfs {
				datas[name] = gdtb
				if strings.EqualFold(tb.Name, name) {
					datas[name] = tb
					break
				}
			}
		}
	}
	return datas, nil
}

/***************************************************
功能:添加表
输入:[tableName]  表名称
	[tableDesc]  表描述
输出:[int] 表ID
	[error] 错误信息
说明:
时间:2020年6月18日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) TableInsert(tableName, tableDesc string) (int, error) {
	g, err := p.GetConnect()
	if err != nil {
		return 0, err
	}
	defer g.DisConnect(p)
	////////////////////////////////////////////////////////////////
	tb := new(GoldenTable)
	tb.Name = tableName
	tb.Desc = tableDesc
	err = tb.AppendTable(g.Handle)

	return tb.Id, err
}

/***************************************************
功能:添加表或者更新表
输入:[tableName]  表名称
	[tableDesc]  表描述
输出:[bool] 如果新建表，则为true;更新表为false
	[int] 表ID
	[error] 错误信息
说明:如果表名称不存在，则添加表，如果存在，则更新表的描述信息
时间:2020年6月18日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) TableInsertOrUpdate(tableName, tableDesc string) (bool, int, error) {
	m, err := p.GetConnect()
	if err != nil {
		return false, 0, err
	}
	defer m.DisConnect(p)
	////////////////////////////////////////////////////////////////
	isinsert := false
	tb := new(GoldenTable)
	tb.Name = tableName
	tb.Desc = tableDesc
	e := tb.GetTablePropertyByName(m.Handle)
	if e != nil || tb.Id == 0 { //如果读取时有错误或者没有读取到ID
		err = tb.AppendTable(m.Handle) //插入新数据
		isinsert = true
	} else {
		err = tb.UpdateTableDescByName(m.Handle) //更新描述信息
	}
	return isinsert, tb.Id, err
}

/***************************************************
功能:删除表
输入:[tableName]  表名称
输出:[error] 错误信息
说明:
时间:2020年6月18日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) TableRemove(tableName string) error {
	m, err := p.GetConnect()
	if err != nil {
		return err
	}
	defer m.DisConnect(p)
	////////////////////////////////////////////////////////////////
	tb := new(GoldenTable)
	tb.Name = tableName
	return tb.RemoveTableByName(m.Handle)
}

/***************************************************
功能:重命名表
输入:[oldtableName]  旧表名称
	[newtableName]  新表名称
输出:[error] 错误信息
说明:
时间:2020年6月18日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) TableReName(oldtableName, newtableName string) error {
	m, err := p.GetConnect()
	if err != nil {
		return err
	}
	defer m.DisConnect(p)
	////////////////////////////////////////////////////////////////
	tb := new(GoldenTable)
	tb.Name = oldtableName
	return tb.UpdateTableNameByOldName(m.Handle, newtableName)
}

/***************************************************
功能:通过表名获取表ID
输入:[tableName]  表名称
输出:[int] 表ID
	[error] 错误信息
说明:
时间:2020年6月18日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) TableGetIdByName(tableName string) (int, error) {
	m, err := p.GetConnect()
	if err != nil {
		return 0, err
	}
	defer m.DisConnect(p)
	////////////////////////////////////////////////////////////////
	tb := new(GoldenTable)
	tb.Name = tableName
	err = tb.GetTablePropertyByName(m.Handle)
	return tb.Id, err
}

/***************************************************
功能:获取标签点的属性
输入:[fullname string]  标签点全名
输出:
    [gdp *GoldenPoint] 标签点属性
	[error] 错误信息
说明:
时间:2022年2月17日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) PointPropterty(fullname string) (gdp *GoldenPoint, err error) {
	g, err := p.GetConnect()
	if err != nil {
		return
	}
	defer g.DisConnect(p)
	////////////////////////////////////////////////////////////////
	ids, _, _, _, err := g.FindPoints(fullname)
	if err != nil || ids[0] == 0 {
		if err == nil {
			err = fmt.Errorf("tagname [%s] not exist inGolden", fullname)
		}
		return
	}
	gdp = new(GoldenPoint)
	gdp.Base.Id = ids[0]
	gdp.GetPointProptertyById(g.Handle)
	return
}

/***************************************************
功能:新建标签点
输入:[GoldenPoint]  标签点属性
输出:
	[error] 错误信息
说明:
时间:2020年6月18日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) PointInsert(gdp *GoldenPoint) error {
	m, err := p.GetConnect()
	if err != nil {
		return err
	}
	defer m.DisConnect(p)
	////////////////////////////////////////////////////////////////
	return gdp.InsertPoint(m.Handle)
}

/***************************************************
功能:更新标签点
输入:[gdp *GoldenPoint]  标签点属性
输出:
	[error] 错误信息
说明:
时间:2022年2月17日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) PointUpdate(gdp *GoldenPoint) error {
	g, err := p.GetConnect()
	if err != nil {
		return err
	}
	defer g.DisConnect(p)
	////////////////////////////////////////////////////////////////
	return gdp.UpdatePointById(g.Handle)
}

/***************************************************
功能:删除标签点
输入:[fullname string]  标签点全名
输出:
	[error] 错误信息
说明:
时间:2022年2月17日
编辑:wang_jp
***************************************************/
func (p *GoldenPool) PointRemove(fullname string) error {
	g, err := p.GetConnect()
	if err != nil {
		return err
	}
	defer g.DisConnect(p)
	////////////////////////////////////////////////////////////////
	ids, _, _, _, err := g.FindPoints(fullname)
	if err != nil || ids[0] == 0 {
		if err == nil {
			err = fmt.Errorf("tagname [%s] not exist inGolden", fullname)
		}
		return err
	}
	gdp := new(GoldenPoint)
	gdp.Base.Id = ids[0]
	return gdp.RemovePointById(g.Handle)
}

/***************************************************
- 功能:搜索符合条件的标签点，使用标签点名时支持通配符
- 参数:
	 [tagmask]       字符串，输入，标签点名称掩码，支持"*"和"?"通配符，缺省设置为"*"，
						长度不得超过GOLDEN_TAG_SIZE，支持多个搜索条件，以空格分隔。
	 [tablemask]     字符串，输入，标签点表名称掩码，支持"*"和"?"通配符，缺省设置为"*"，
						长度不得超过 GOLDEN_TAG_SIZE，支持多个搜索条件，以空格分隔。
	 [source]        字符串，输入，数据源集合，字符串中的每个字符均表示一个数据源，空字符串
						表示不用数据源作搜索条件，缺省设置为空，长度不得超过 GOLDEN_DESC_SIZE。
	 [unit]          字符串，输入，标签点工程单位的子集，工程单位中包含该参数的标签点均满足条件，
						空字符串表示不用工程单位作搜索条件，缺省设置为空，长度不得超GOLDEN_UNIT_SIZE。
	 [desc]          字符串，输入，标签点描述的子集，描述中包含该参数的标签点均满足条件，
						空字符串表示不用描述作搜索条件，缺省设置为空，长度不得超过 GOLDEN_SOURCE_SIZE。
	 [instrument]    字符串，输入参数，标签点设备名称。缺省设置为空，长度不得超过GOLDEN_INSTRUMENT_SIZE。
	 [mode]          整型，GOLDEN_SORT_BY_TABLE(0)、GOLDEN_SORT_BY_TAG(1)、GOLDEN_SORT_BY_ID(2) 之一，
						搜索结果的排序模式，输入，缺省值为GOLDEN_SORT_BY_TABLE
- 返回: [[]ids]           整型数组，输出，返回搜索到的标签点标识列表
		[[]tagnames]	字符串数组,标签点全名
	 	[error]         错误信息
- 备注:用户须保证分配给 ids 的空间与 count 相符，各参数中包含的搜索条件之间的关系为"与"的关系，
	用包含通配符的标签点名称作搜索条件时，如果第一个字符不是通配符(如"ai67*")，会得到最快的搜索速度。
 	如果 tagmask、tablemask 为空指针，则表示使用缺省设置"*",
 	多个搜索条件可以通过空格分隔，比如"demo_*1 demo_*2"，会将满足demo_*1或者demo_*2条件的标签点搜索出来。
***************************************************/
func (p *GoldenPool) PointSearch(tagmask, tablemask, source, unit, desc, instrument string, mode int) (tagids []int, tagnames []string, err error) {
	g, e := p.GetConnect()
	if e != nil {
		err = e
		return
	}
	defer g.DisConnect(p)
	////////////////////////////////////////////////////////////////
	ids, e := g.Search(tagmask, tablemask, source, unit, desc, instrument, mode)
	if e != nil {
		err = e
		return
	}
	tagids = append(tagids, ids...)
	err = g.GetPointPropterty(ids...)
	if err != nil {
		return
	}
	for _, id := range ids {
		tagnames = append(tagnames, g.Points[id].Base.TableDotTag)
	}
	return
}
