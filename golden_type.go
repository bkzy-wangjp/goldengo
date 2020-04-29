package goldengo

const (
	_TIME_LAYOUT = "2006-01-02 15:04:05"
	//庚顿数据类型 GOLDEN_TYPE
	GOLDEN_BOOL     = 0  /// 布尔类型，0值或1值。
	GOLDEN_UINT8    = 1  /// 无符号8位整数，占用1字节。
	GOLDEN_INT8     = 2  /// 有符号8位整数，占用1字节。
	GOLDEN_CHAR     = 3  /// 单字节字符，占用1字节。
	GOLDEN_UINT16   = 4  /// 无符号16位整数，占用2字节。
	GOLDEN_INT16    = 5  /// 有符号16位整数，占用2字节。
	GOLDEN_UINT32   = 6  /// 无符号32位整数，占用4字节。
	GOLDEN_INT32    = 7  /// 有符号32位整数，占用4字节。
	GOLDEN_INT64    = 8  /// 有符号64位整数，占用8字节。
	GOLDEN_REAL16   = 9  /// 16位浮点数，占用2字节。
	GOLDEN_REAL32   = 10 /// 32位单精度浮点数，占用4字节。
	GOLDEN_REAL64   = 11 /// 64位双精度浮点数，占用8字节。
	GOLDEN_COOR     = 12 /// 二维坐标，具有x、y两个维度的浮点数，占用8字节。
	GOLDEN_STRING   = 13 /// 字符串，长度不超过存储页面大小。
	GOLDEN_BLOB     = 14 /// 二进制数据块，占用字节不超过存储页面大小。
	GOLDEN_NAMED_T  = 15 /// 自定义类型，由用户创建时确定字节长度。
	GOLDEN_DATETIME = 16 /// 时间格式类型

	//庚顿系统质量码 GOLDEN_QUALITY
	GOLDEN_Q_GOOD      = 0   // 正常
	GOLDEN_Q_NODATA    = 1   // 无数据
	GOLDEN_Q_CREATED   = 2   // 创建
	GOLDEN_Q_SHUTDOWN  = 3   // 停机
	GOLDEN_Q_CALCOFF   = 4   // 计算停止
	GOLDEN_Q_BAD       = 5   // 坏点
	GOLDEN_Q_DIVBYZERO = 6   // 被零除
	GOLDEN_Q_REMOVED   = 7   // 已被删除
	GOLDEN_Q_OPC       = 256 // 从0x0100至0x01FF为OPC质量码
	GOLDEN_Q_USER      = 512 // 此质量码（含）之后为用户自定义

	//庚顿标签点类别 GOLDEN_CLASS
	GOLDEN_BASE  = 0 /// 基本标签点，所有类别标签点均在基本标签点的属性集上扩展自己的属性集。
	GOLDEN_SCAN  = 1 /// 采集标签点。
	GOLDEN_CALC  = 2 /// 计算标签点。
	GOLDEN_ALARM = 4 /// 报警标签点。

	//庚顿数据库用户权限
	GOLDEN_RO = 0 /// 只读
	GOLDEN_DW = 1 /// 数据记录
	GOLDEN_TA = 2 /// 标签点表管理员
	GOLDEN_SA = 3 /// 数据库管理员

	//GOLDEN_API_OPTION的可选内容：
	GOLDEN_API_AUTO_RECONN  = 0 /// api 在连接中断后是否自动重连, 0 不重连；1 重连。默认为 0 不重连
	GOLDEN_API_CONN_TIMEOUT = 1 /// api 连接超时值设置（单位：秒）,0 阻塞模式，无限等待，默认为0

	//标签点搜索结果排序方式GOLDEN_SEARCH_SORT
	GOLDEN_SORT_BY_TABLE = 0 /// 首先按所属表排序，同一个表内的标签点之间按标签点名称排序
	GOLDEN_SORT_BY_TAG   = 1 /// 以标签点名称排序
	GOLDEN_SORT_BY_ID    = 2 /// 以标签点ID排序

	//历史数据历史数据搜索方式 GOLDEN_HIS_MODE
	GOLDEN_NEXT     = 0 ///寻找下一个最近的数据；
	GOLDEN_PREVIOUS = 1 ///寻找上一个最近的数据；
	GOLDEN_EXACT    = 2 ///取指定时间的数据，如果没有则返回错误 GoE_DATA_NOT_FOUND；
	GOLDEN_INTER    = 3 ///取指定时间的内插值数据。

	//庚顿系统常数定义
	GOLDEN_TAG_SIZE                   = 80                               /// 标签点名称占用字节数。
	GOLDEN_DESC_SIZE                  = 100                              /// 标签点描述占用字节数。
	GOLDEN_UNIT_SIZE                  = 20                               /// 标签点单位占用字节数。
	GOLDEN_USER_SIZE                  = 20                               /// 用户名占用字节数。
	GOLDEN_SOURCE_SIZE                = 256                              /// 标签点数据源占用字节数。
	GOLDEN_INSTRUMENT_SIZE            = 50                               /// 标签点所属设备占用字节数。
	GOLDEN_LOCATIONS_SIZE             = 5                                /// 采集标签点位址个数。
	GOLDEN_USERINT_SIZE               = 2                                /// 采集标签点用户自定义整数个数。
	GOLDEN_USERREAL_SIZE              = 2                                /// 采集标签点用户自定义浮点数个数。
	GOLDEN_EQUATION_SIZE              = 2036                             /// 计算标签点方程式占用字节数。
	GOLDEN_TYPE_NAME_SIZE             = 21                               /// 自定义类型名称占用字节数。
	GOLDEN_PACK_OF_SNAPSHOT           = 0                                /// 事件快照备用字节空间。
	GOLDEN_PACK_OF_POINT              = 5                                /// 标签点备用字节空间。
	GOLDEN_PACK_OF_BASE_POINT         = 74                               /// 基本标签点备用字节空间。
	GOLDEN_PACK_OF_SCAN               = 164                              /// 采集标签点备用字节空间。
	GOLDEN_PACK_OF_CALC               = 0                                /// 计算标签点备用字节空间。
	GOLDEN_FILE_NAME_SIZE             = 64                               /// 文件名字符串字节长度
	GOLDEN_PATH_SIZE                  = 1024 - 4 - GOLDEN_FILE_NAME_SIZE /// 路径字符串字节长度
	GOLDEN_MAX_USER_COUNT             = 100                              /// 最大用户个数
	GOLDEN_MAX_AUTH_COUNT             = 100                              /// 最大信任连接段个数
	GOLDEN_MAX_BLACKLIST_LEN          = 100                              /// 连接黑名单最大长度
	GOLDEN_MAX_SUBSCRIBE_SNAPSHOTS    = 1000                             /// 单个连接最大订阅快照数量
	GOLDEN_API_SERVER_DESCRIPTION_LEN = 512                              /// API_SERVER中，decription描述字段的长度

	GOLDEN_MIN_EQUATION_SIZE = 480                                     /// 缩减长度后的方程式占用字节数
	GOLDEN_PACK_OF_MIN_CALC  = 19                                      /// 缩减长度后的计算标签点备用字节空间
	GOLDEN_MAX_EQUATION_SIZE = 62 * 1024                               /// 最大长度的方程式占用字节数
	GOLDEN_PACK_OF_MAX_CALC  = 64*1024 - GOLDEN_MAX_EQUATION_SIZE - 12 /// 最大长度的计算标签点备用字节空间
	GOLDEN_MAX_JSON_SIZE     = 16 * 1024                               /// 允许的json字符串的最大长度

	GOLDEN_OUTPUT_PLUGIN_LIB_VERSION_LENGTH = 0x40 // 输入输出适配器插件库版本号长度 64  Bytes
	GOLDEN_OUTPUT_PLUGIN_LIB_NAME_LENGTH    = 0x80 // 输入输出适配器插件库名长度    128 Bytes
	GOLDEN_OUTPUT_PLUGIN_ACTOR_NAME_LENGTH  = 0x80 // 输入输出适配器执行实例长度    128 Bytes
	GOLDEN_OUTPUT_PLUGIN_NAME_LENGTH        = 0xFF // 输入输出适配器插件名长度      255 Bytes
	GOLDEN_OUTPUT_PLUGIN_DIR_LENGTH         = 0xFF // 输入输出适配器路径长度        255 Bytes
	GOLDEN_PER_OF_USEFUL_MEM_SIZE           = 10   ///历史数据缓存/补历史数据缓存/blob补历史数据缓存/内存大小上限占可用内存百分比值占用的字节数
)

type RTDBService struct {
	Handle int32 //连接句柄
	Priv   int32 //整型，GOLDEN_RO, GOLDEN_DW, GOLDEN_TA, GOLDEN_SA 之一，帐户权限
}

type GOLDEN_TABLE struct {
	Id   int
	Type int
	Name []byte
	Desc []byte
}
