package goldengo

import (
	"C"
	"syscall"
)

var (
	//////////// API 配置接口 //////////////
	go_get_api_version, //取得 goldenapi 库的版本号
	go_set_option, //配置 api 行为参数
	//////////// 网络服务接口 //////////////
	go_connect, //建立同 GOLDEN 数据库的网络连接
	go_disconnect, //断开同 GOLDEN 数据平台的连接
	go_login, //以有效帐户登录
	go_host_time, //获取 GOLDEN 服务器当前UTC时间
	go_format_timespan, //根据时间跨度值生成时间格式字符串
	go_parse_timespan, //根据时间格式字符串解析时间跨度值
	go_parse_time, //根据时间格式字符串解析时间值
	go_format_message, //获取 Golden API 调用返回值的简短描述
	gob_search, //搜索符合条件的标签点，使用标签点名时支持通配符
	gob_find_points, //根据 "表名.标签点名" 格式批量获取标签点标识
	/////////// 实时数据接口 ///////////////
	gos_get_snapshots, //批量读取整数、浮点数快照数值
	gos_put_snapshots, //批量写入整数、浮点数快照数值
	/////////// 历史数据接口 ///////////////
	goh_archived_values_count, //获取单个标签点在一段时间范围内的存储值数量
	goh_get_archived_values, //读取单个标签点一段时间内的储存数据
	goh_get_single_value, //读取单个标签点某个时间的历史数据
	goh_summary_ex, //获取单个标签点一段时间内的统计值，以及用于计算统计值的数据个数
	goh_get_plot_values, //获取单个标签点一段时间内用于绘图的历史数据
	goh_put_single_value, //写入单个标签点在某一时间的历史数据
	goh_put_archived_values, //写入批量标签点批量历史存储数据
	gob_tables_count, //取得标签点表总数
	goh_get_interpo_values, //获取单个标签点一段时间内等间隔历史插值
	gob_insert_point, //使用完整的属性集来创建单个标签点
	gob_get_table_property_by_id, //根据标签点表 id 获取表属性
	gob_get_table_property_by_name, //根据标签点表 name 获取表属性
	goh_flush_archived_values *syscall.Proc //将标签点未写满的补历史缓存页写入存档文件中
)

func init() {

	dll := syscall.MustLoadDLL("goldenapi64.dll")

	go_get_api_version = dll.MustFindProc("go_get_api_version")
	go_set_option = dll.MustFindProc("go_set_option")
	go_connect = dll.MustFindProc("go_connect")
	go_disconnect = dll.MustFindProc("go_disconnect")
	go_login = dll.MustFindProc("go_login")
	go_host_time = dll.MustFindProc("go_host_time")
	go_format_timespan = dll.MustFindProc("go_format_timespan")
	go_parse_timespan = dll.MustFindProc("go_parse_timespan")
	go_parse_time = dll.MustFindProc("go_parse_time")
	go_format_message = dll.MustFindProc("go_format_message")
	gob_search = dll.MustFindProc("gob_search")
	gob_find_points = dll.MustFindProc("gob_find_points")
	gos_get_snapshots = dll.MustFindProc("gos_get_snapshots")
	gos_put_snapshots = dll.MustFindProc("gos_put_snapshots")
	goh_archived_values_count = dll.MustFindProc("goh_archived_values_count")
	goh_get_archived_values = dll.MustFindProc("goh_get_archived_values")
	goh_get_single_value = dll.MustFindProc("goh_get_single_value")
	goh_summary_ex = dll.MustFindProc("goh_summary_ex")
	goh_get_plot_values = dll.MustFindProc("goh_get_plot_values")
	goh_put_single_value = dll.MustFindProc("goh_put_single_value")
	goh_put_archived_values = dll.MustFindProc("goh_put_archived_values")
	goh_flush_archived_values = dll.MustFindProc("goh_flush_archived_values")

	gob_tables_count = dll.MustFindProc("gob_tables_count")             //取得标签点表总数
	goh_get_interpo_values = dll.MustFindProc("goh_get_interpo_values") //获取单个标签点一段时间内等间隔历史插值
	gob_insert_point = dll.MustFindProc("gob_insert_point")
	gob_get_table_property_by_id = dll.MustFindProc("gob_get_table_property_by_id")
	gob_get_table_property_by_name = dll.MustFindProc("gob_get_table_property_by_name")
}
