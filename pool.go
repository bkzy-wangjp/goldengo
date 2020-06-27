package goldengo

//庚顿数据库结构
type Golden struct {
	RTDBService
}

//庚顿工作池结构
type GoldenPool struct {
	Worker     chan int //工作通道
	size       int      //工作池大小
	RequestCnt int      //请求数量
	hostname   string   //主机IP
	username   string   //用户名
	password   string   //密码
	port       int      //端口号
}

/*******************************************************************************
- 功能:实例化庚顿工作池
- 参数:
	[hostname]  字符串，输入，GOLDEN 数据平台服务器的网络地址或机器名
	[username]	用户名,字符串,缺省值 sa
	[password]	密码,字符串,缺省值 golden
	[port]      端口号,整型,缺省值 6327
	[cap]       连接池大小,最小1,最大50
- 输出:无
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func NewGoldenPool(hostname, username, password string, port, cap int) *GoldenPool {
	if port == 0 {
		port = 6327
	}
	if cap < 1 {
		cap = 1
	}
	if cap > 50 {
		cap = 50
	}
	return &GoldenPool{
		Worker:     make(chan int, cap), //工作池通道
		size:       cap,                 //工作池大小
		RequestCnt: 0,                   //请求数量
		hostname:   hostname,            //Golden数据库主机名
		username:   username,            //用户名
		password:   password,            //密码
		port:       port,                //端口号
	}
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
}

/*******************************************************************************
- 功能:请求建立一个庚顿连接
- 参数:无
- 输出:
	[*Golden] 庚顿数据库连接指针
	[error] 错误信息
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func (p *GoldenPool) GetConnect() (*Golden, error) {
	p.RequestCnt++ //请求数量自增
	select {       //有资源就分配资源，没有资源就阻塞等待
	case p.Worker <- 1: //有资源可分配
		p.RequestCnt-- //请求数量减少
	}
	g := CreateGolden(p.hostname, p.username, p.password, p.port)
	err := g.Connect()
	return g, err
}

/*******************************************************************************
- 功能:断开连接
- 参数:[p *GoldenPool] 庚顿连接池指针
- 输出:
	[error] 错误信息
- 备注:
- 时间: 2020年6月27日
*******************************************************************************/
func (g *Golden) DisConnect(p *GoldenPool) error {
	<-p.Worker //释放连接资源
	return g.disConnect()
}
