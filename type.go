package goldengo

const (
	_TIME_LAYOUT         = "2006-01-02 15:04:05"
	_MAX_POINT_IN_SEARCH = 10000 //查询的最大数据点数
)

//庚顿实时数据库
type RTDBService struct {
	HostName    string              //主机ip或者计算机名
	Port        int                 //端口号,默认6327
	UserName    string              //用户名,默认sa
	Password    string              //密码,默认golden
	Handle      int32               //连接句柄
	Priv        int                 //整型，GOLDEN_RO, GOLDEN_DW, GOLDEN_TA, GOLDEN_SA 之一，帐户权限
	TableCounts int                 //标签点表数量
	TableIds    []int               //标签点表的ID列表
	Tables      map[int]GoldenTable //标签点表,以id为key
	Points      map[int]GoldenPoint //数据标签点,以id为key
}

type GoldenTable struct {
	Id       int    //表id
	Size     int    //标签数量
	Name     string //表名称
	Desc     string //表描述
	PointIds []int  //标签点ID列表
}
type GoldenPoint struct {
	Base GoldenBasePoint //基本属性
	Scan GoldenScanPoint //采集属性
	Calc GoldenCalcPoint //计算属性
}

//基本标签点属性集
type GoldenBasePoint struct {
	Id             int     //全库唯一标识
	Tag            string  //用于在表中唯一标识一个标签点,最长79
	DataType       int     //标签点的数值类型
	TableId        int     //标签点所属表ID
	Desc           string  //有关标签点的描述性文字,最长99
	Unit           string  //工程单位,最长19
	IsArchive      bool    //是否存档
	Digits         int     //数值位数,>=-20、<=10,默认-5;如果为0或正数，表示数值的小数位数，如果为负数，表示数值的有效位数
	IsShutDown     bool    //停机状态字,定义该点在停机状态下是否补写停机状态值.1 表示补写；0 表示不补写
	LowLimit       float64 //量程下限,缺省0
	HighLimit      float64 //量程上限,缺省100
	IsStep         bool    //是否阶跃.
	Typical        float64 //典型值
	IsCompress     bool    //是否压缩,缺省true
	CompDev        float64 //压缩偏差,单位:标签工程单位,缺省:1
	CompDevPercent float64 //压缩偏差百分比
	CompTimeMax    int     //最大压缩间隔,单位:秒,缺省值:28800
	CompTimeMin    int     //最短压缩间隔,单位:秒,缺省值:0
	ExcDev         float64 //例外偏差,单位:标签工程单位.缺省0.5
	ExcDevPercent  float64 //例外偏差百分比
	ExcTimeMax     int     //最大例外间隔,单位:秒,缺省值600
	ExcTimeMin     int     //最短例外间隔,单位:秒,缺省值0
	ClassOf        uint    //标签点类别,基本点(0)、采集点(1)、计算点(2)、采集计算点(3) 、报警点(4)等
	ChangeDate     int     //标签点属性最后一次被修改的时间
	Changer        string  //最后一次修改的用户名
	CreateDate     int     //标签点被创建的时间
	Creator        string  //标签点创建者用户名
	Mirror         int     //镜像收发控制:0:关闭;1:既接收,又发送;2:只接受,不发送;3:只发送,不接收
	MilliSecond    int     //时间戳精度,默认值:0,秒;1:毫秒;创建后不可更改
	ScanIndex      uint    //采集点扩展属性集索引
	CalcIndex      uint    //计算点扩展属性集索引
	AlarmIndex     uint    //报警点扩展属性集索引
	TableDotTag    string  //标签点全名
	IsSummary      bool    //统计加速开关,默认0;用于设定是否生成标签点统计信息，从而加速历史数据统计过程
	Err            string  //错误信息
}

//采集标签点扩展属性集
type GoldenScanPoint struct {
	Id         int        //
	Source     string     //数据源,缺省为空
	IsScan     bool       //是否采集
	Instrument string     //设备标签
	Locations  [5]int     //设备位置
	UserInts   [2]int     //自定义整数
	UserReals  [2]float64 //自定义浮点数
}

//计算点扩展属性集
type GoldenCalcPoint struct {
	Id       int
	Equation string //试试方程式，长度不超过2047字节
	Trigger  int    //计算触发机制
	TimeCopy int    //计算结果时间戳:0: 表示采用计算时间作为计算结果时间戳； 1: 表示采用输入标签点中的最晚时间作为计算结果时间戳；2: 表示采用输入标签点中的最早时间作为计算结果时间戳。
	Period   int    //计算周期,对周期触发的计算点有效,单位:秒
}

/*
//计算点扩展属性集
type GoldenMinCalcPoint struct {
	Id         int
	Equation   string //试试方程式，长度不超过480字节
	Trigger    int    //计算触发机制
	TimeCopy   int    //计算结果时间戳:0: 表示采用计算时间作为计算结果时间戳； 1: 表示采用输入标签点中的最晚时间作为计算结果时间戳；2: 表示采用输入标签点中的最早时间作为计算结果时间戳。
	Period     int    //计算周期,对周期触发的计算点有效,单位:秒
	IsEquation bool   //此方程式中保存的是否是方程式
}

//计算点扩展属性集
type GoldenMaxCalcPoint struct {
	Id       int
	Equation string //试试方程式，长度不超过62*1024字节
	Trigger  int    //计算触发机制
	TimeCopy int    //计算结果时间戳:0: 表示采用计算时间作为计算结果时间戳； 1: 表示采用输入标签点中的最晚时间作为计算结果时间戳；2: 表示采用输入标签点中的最早时间作为计算结果时间戳。
	Period   int    //计算周期,对周期触发的计算点有效,单位:秒
}
*/
