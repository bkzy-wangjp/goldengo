package goldengo

import (
	"strings"
	"sync"
)

//庚顿数据库结构
type Golden struct {
	RTDBService
}

//庚顿工作池结构
type GoldenPool struct {
	Worker   chan int   //工作通道
	Req      chan int   //请求队列
	Handel   chan int32 //连接池句柄
	Tenant   sync.Map   //注册的租户map,key为Handel,value为租户字符串
	size     int        //工作池大小
	hostname string     //主机IP
	username string     //用户名
	password string     //密码
	port     int        //端口号
}

/*******************************************************************************
- 功能:实例化庚顿工作池
- 参数:
	[hostname]  字符串，输入，GOLDEN 数据平台服务器的网络地址或机器名
	[username]	用户名,字符串,缺省值 sa
	[password]	密码,字符串,缺省值 golden
	[port]      端口号,整型,缺省值 6327
	[cap]       连接池大小,最小1,最大50
- 输出:[*GoldenPool] 连接池指针
	[error] 创建句柄连接池时候的错误信息
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func NewGoldenPool(hostname, username, password string, port, cap int) (*GoldenPool, error) {
	if port == 0 {
		port = 6327
	}
	if cap < 1 {
		cap = 1
	}
	if cap > 50 {
		cap = 50
	}
	pool := &GoldenPool{
		Worker:   make(chan int, cap),   //工作者通道
		Req:      make(chan int, 10000), //请求通道数量
		Handel:   make(chan int32, cap), //池句柄池
		size:     cap,                   //工作池大小
		hostname: hostname,              //Golden数据库主机名
		username: username,              //用户名
		password: password,              //密码
		port:     port,                  //端口号
	}
	var err error
	for i := 0; i < cap; i++ { //创建句柄连接池
		g := new(Golden)
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
	return pool, err
}

/*******************************************************************************
- 功能:删除庚顿连接池通道资源
- 参数:无
- 输出:无
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func (p *GoldenPool) RemovePool() {
	close(p.Worker)
	close(p.Req)
	for h := range p.Handel {
		g := new(Golden)
		g.Handle = h
		g.disConnect()
	}
	close(p.Handel)
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
		TenantName string
	}
	var tenants []tenant
	p.Tenant.Range(func(k, v interface{}) bool {
		t := tenant{
			Handel:     k.(int32),
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
func (p *GoldenPool) GetConnect(tenant ...string) (*Golden, error) {
	var tenantstr string //租户名称
	for i, str := range tenant {
		if i != 0 {
			tenantstr += "."
		}
		tenantstr += str
	}

	p.Req <- 1
	g := new(Golden)
	select { //有资源就分配资源，没有资源就阻塞等待
	case p.Worker <- 1: //有资源可分配
		g.Handle = <-p.Handel //从连接池取句柄
		<-p.Req               //请求数量减少
	}
	//从连接池获取基本信息
	g.HostName = p.hostname
	g.UserName = p.username
	g.Password = p.password
	g.Port = p.port
	_, err := g.HostTime() //测试句柄
	if err != nil {
		//无效的句柄\远程主机强迫关闭了一个现有的连接\你的主机中的软件中止了一个已建立的连接
		if stringContains(err.Error(), "0xFFFF2005",
			"0xFFFFA746",
			"0xFFFFA745",
			"0xFFFFA736",
			"0xFFFFC010") {
			err = g.connect() //重新创建句柄
			if err != nil {   //创建连接失败
				g.Handle = 0x0FFFFFFF
				g.DisConnect(p) //释放资源
			}
		}
	}

	if g.Handle != 0 {
		p.Tenant.Store(g.Handle, tenantstr) //记录租户名称
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
func (g *Golden) GetConnect(p *GoldenPool, tenant ...string) error {
	if g.Handle <= 0 { //是否已经获取了句柄
		var tenantstr string //租户名称
		for i, str := range tenant {
			if i != 0 {
				tenantstr += "."
			}
			tenantstr += str
		}

		p.Req <- 1
		select { //有资源就分配资源，没有资源就阻塞等待
		case p.Worker <- 1: //有资源可分配
			g.Handle = <-p.Handel //从连接池取句柄
			<-p.Req               //请求数量减少
		}
		//从连接池获取基本信息
		g.HostName = p.hostname
		g.UserName = p.username
		g.Password = p.password
		g.Port = p.port
		_, err := g.HostTime() //测试句柄
		if err != nil {
			//无效的句柄\远程主机强迫关闭了一个现有的连接\你的主机中的软件中止了一个已建立的连接
			if stringContains(err.Error(), "0xFFFF2005", "0xFFFFA746", "0xFFFFA745") {
				err = g.connect() //重新创建句柄
				if err != nil {   //创建连接失败
					g.Handle = 0x0FFFFFFF
					g.DisConnect(p) //释放资源
				}
			}
		}
		if g.Handle != 0 {
			p.Tenant.Store(g.Handle, tenantstr) //记录租户名称
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
func (g *Golden) DisConnect(p *GoldenPool) {
	if g.Handle > 0 { //有资源的时候才准许释放
		<-p.Worker                //释放连接资源
		p.Handel <- g.Handle      //归还句柄到连接池
		p.Tenant.Delete(g.Handle) //删除租户记录
		g.Handle = 0              //复位
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
