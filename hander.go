package goldengo

import (
	"C"
	"fmt"

	"syscall"
	"unsafe"
)

/*******************************************************************************
-功能：格式化错误码
-参数: [ecode] 错误码,为0时无错误
-返回: [error] 错误信息；ecode为0时返回nil
*******************************************************************************/
func (s *RTDBService) FormatErrMsg(ecode uintptr) error {
	var eMsg error
	if ecode > 0 {
		size := 256
		_message := make([]byte, size)
		_name := make([]byte, size)
		code, _, _ := go_format_message.Call(
			ecode,
			uintptr(unsafe.Pointer(&_message[0])),
			uintptr(unsafe.Pointer(&_name[0])),
			uintptr(size),
		)
		if code == 0 {
			eMsg = fmt.Errorf("ECODE:0x%X, ENAME:%s, DESC:%s",
				ecode, GbkToUtf8(_name),
				GbkToUtf8(_message),
			)
		} else {
			eMsg = fmt.Errorf("ECODE:0x%X", code)
		}
	}
	return eMsg
}

/*******************************************************************************
// 获取API版本号
*******************************************************************************/
func (s *RTDBService) GetAPIVersion() string {
	var major int32
	var minor int32
	var beta int32
	go_get_api_version.Call(
		uintptr(unsafe.Pointer(&major)),
		uintptr(unsafe.Pointer(&minor)),
		uintptr(unsafe.Pointer(&beta)),
	)
	return fmt.Sprintf("%d.%d.%d", major, minor, beta)
}

/*******************************************************************************
- 功能：建立同 GOLDEN 数据库的网络连接
- 参数：
	[hostname]     字符串，输入，GOLDEN 数据平台服务器的网络地址或机器名
	[port]         整型，输入，缺省值 6327，连接端口
	[error]        错误信息
- 备注：在调用所有的接口函数之前，必须先调用本函数建立同Golden服务器的连接。
*******************************************************************************/
func (s *RTDBService) Connect(hostname, user, password string, port ...int32) error {
	host, _ := syscall.BytePtrFromString(hostname)
	var p int32 = 6327 //默认端口号
	if len(port) > 0 { //如果设置了端口号
		p = port[0] //赋值端口号
	}
	code, _, _ := go_connect.Call(uintptr(unsafe.Pointer(host)), uintptr(p), uintptr(unsafe.Pointer(&s.Handle)))
	var err error
	if code == 0 {
		err = s.login(user, password) //登录
	} else {
		err = s.FormatErrMsg(code)
	}
	return err
}

/*******************************************************************************
- 功能：断开同 GOLDEN 数据平台的连接
- 参数：无
- 备注：完成对 GOLDEN 的访问后调用本函数断开连接。
  连接一旦断开，则需要重新连接后才能调用其他的接口函数。
*******************************************************************************/
func (s *RTDBService) DisConnect() error {
	code, _, _ := go_disconnect.Call(uintptr(s.Handle))
	return s.FormatErrMsg(code)
}

/*******************************************************************************
- 功能：以有效帐户登录
- 参数：
 	[user]      字符串，输入，登录帐户
	[password]  字符串，输入，帐户口令
- 返回：登录正确返回nil，错误返回错误码
/*******************************************************************************/
func (s *RTDBService) login(user string, password string) error {
	usr, _ := syscall.BytePtrFromString(user)
	pad, _ := syscall.BytePtrFromString(password)
	code, _, _ := go_login.Call(uintptr(s.Handle), uintptr(unsafe.Pointer(usr)), uintptr(unsafe.Pointer(pad)), uintptr(unsafe.Pointer(&s.Priv)))
	return s.FormatErrMsg(code)
}

/*******************************************************************************
- 功能：获取 GOLDEN 服务器当前UTC时间
- 参数：无
- 返回：[hosttime]     整型，输出，Golden服务器的当前UTC时间，表示距离1970年1月1日08:00:00的秒数。
/*******************************************************************************/
func (s *RTDBService) HostTime() int32 {
	var hosttime int32 = 0
	go_host_time.Call(uintptr(s.Handle), uintptr(unsafe.Pointer(&hosttime)))
	return hosttime
}

/*******************************************************************************
- 功能：搜索符合条件的标签点，使用标签点名时支持通配符
- 参数：
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
- 返回: [ids]           整型数组，输出，返回搜索到的标签点标识列表
	 [error]         错误信息
- 备注：用户须保证分配给 ids 的空间与 count 相符，各参数中包含的搜索条件之间的关系为"与"的关系，
	用包含通配符的标签点名称作搜索条件时，如果第一个字符不是通配符(如"ai67*")，会得到最快的搜索速度。
 	如果 tagmask、tablemask 为空指针，则表示使用缺省设置"*",
 	多个搜索条件可以通过空格分隔，比如"demo_*1 demo_*2"，会将满足demo_*1或者demo_*2条件的标签点搜索出来。
*******************************************************************************/
func (s *RTDBService) Search(tagmask, tablemask, source, unit, desc, instrument string, mode int32) ([]int32, error) {
	_tagmask, _ := syscall.BytePtrFromString(tagmask)
	_tablemask, _ := syscall.BytePtrFromString(tablemask)
	_source, _ := syscall.BytePtrFromString(source)
	_unit, _ := syscall.BytePtrFromString(unit)
	_desc, _ := syscall.BytePtrFromString(desc)
	_instrument, _ := syscall.BytePtrFromString(instrument)

	var count int32 = 10000
	ids := make([]int32, count)
	code, _, _ := gob_search.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(_tagmask)),
		uintptr(unsafe.Pointer(_tablemask)),
		uintptr(unsafe.Pointer(_source)),
		uintptr(unsafe.Pointer(_unit)),
		uintptr(unsafe.Pointer(_desc)),
		uintptr(unsafe.Pointer(_instrument)),
		uintptr(mode), uintptr(unsafe.Pointer(&ids[0])),
		uintptr(unsafe.Pointer(&count)),
	)
	return ids[:count], s.FormatErrMsg(code)
}

/*******************************************************************************
- 功能：根据 "表名.标签点名" 格式批量获取标签点标识
- 参数：
	 [table_dot_tags]   字符串数组，输入，"表名.标签点名" 列表
- 返回:
	 [ids]              整型数组，输出，标签点标识列表, 返回 0 表示未找到
	 [types]            整型数组，输出，标签点数据类型
	 [classof]          整型数组，输出，标签点类别
	 [use_ms]           整型数组，输出，时间戳精度， 返回 1 表示时间戳精度为毫秒， 为 0 表示为秒。
- 备注：
*******************************************************************************/
func (s *RTDBService) FindPoints(table_dot_tags []string) ([]int32, []int32, []int32, []int32, error) {
	count := len(table_dot_tags) //标签点个数(即table_dot_tags、ids、types、classof、use_ms 的长度
	tags := make([]*byte, count)
	ids := make([]int32, count)
	types := make([]int32, count)
	classof := make([]int32, count)
	use_ms := make([]int16, count)
	for i, tagstr := range table_dot_tags {
		tag, _ := syscall.BytePtrFromString(tagstr)
		tags[i] = tag
	}

	code, _, _ := gob_find_points.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(&count)),
		uintptr(unsafe.Pointer(&tags[0])),
		uintptr(unsafe.Pointer(&ids[0])),
		uintptr(unsafe.Pointer(&types[0])),
		uintptr(unsafe.Pointer(&classof[0])),
		uintptr(unsafe.Pointer(&use_ms[0])),
	)
	var isms []int32
	for _, ms := range use_ms {
		isms = append(isms, int32(ms))
	}
	return ids, types, classof, isms, s.FormatErrMsg(code)
}

/*******************************************************************************
- 功能：批量读取开关量、模拟量快照数值
- 参数：
     [ids]       整型数组，输入，标签点标识列表
- 返回：
     [datetimes] 整型数组，输出，实时数值时间列表,表示距离1970年1月1日08:00:00的毫秒数
     [values]    双精度浮点型数组，输出，实时浮点型数值列表，对于数据类型为 GOLDEN_REAL16、
    	GOLDEN_REAL32、GOLDEN_REAL64 的标签点，返回相应的快照值；否则为 0
     [states]    64 位整型数组，输出，实时整型数值列表，对于数据类型为 GOLDEN_BOOL、
    	GOLDEN_UINT8、GOLDEN_INT8、GOLDEN_CHAR、GOLDEN_UINT16、GOLDEN_INT16、
		GOLDEN_UINT32、GOLDEN_INT32、GOLDEN_INT64 的标签点，返回相应的快照值；否则为0
     [qualities] 短整型数组，输出，实时数值品质列表，数据库预定义的品质参见枚举 GOLDEN_QUALITY
     [errors]    错误信息数组，输出，读取实时数据的错误返回值列表，参考golden_error.h
- 备注：本接口对数据类型为 GOLDEN_COOR、GOLDEN_STRING、GOLDEN_BLOB 的标签点无效。
*******************************************************************************/
func (s *RTDBService) GetSnapshots(ids []int32) ([]int64, []float64, []int64, []int32, []error) {
	var count int32 = int32(len(ids))

	secondes := make([]int32, count)  //秒,表示距离1970年1月1日08:00:00的秒数
	ms := make([]int16, count)        //毫秒，对于时间精度为毫秒的标签点，返回相应的毫秒值；否则为 0
	values := make([]float64, count)  //浮点型值
	states := make([]int64, count)    //整数值
	qualities := make([]int32, count) //质量码
	errs := make([]uint32, count)     //错误码

	datetimes := make([]int64, count) //unix毫秒值，表示距离1970年1月1日08:00:00的毫秒数
	errors := make([]error, count)    //错误信息

	gos_get_snapshots.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(&count)),
		uintptr(unsafe.Pointer(&ids[0])),
		uintptr(unsafe.Pointer(&secondes[0])),
		uintptr(unsafe.Pointer(&ms[0])),
		uintptr(unsafe.Pointer(&values[0])),
		uintptr(unsafe.Pointer(&states[0])),
		uintptr(unsafe.Pointer(&qualities[0])),
		uintptr(unsafe.Pointer(&errs[0])),
	)

	for i, _ := range ids {
		datetimes[i] = int64(secondes[i])*1000 + int64(ms[i])
		errors[i] = s.FormatErrMsg(uintptr(errs[i]))
	}
	return datetimes, values, states, qualities, errors
}

/*******************************************************************************
- 功能：批量写入开关量、模拟量快照数值
- 参数：
     [ids]       整型数组，输入，标签点标识列表，同一个标签点标识可以出现多次，但它们的时间戳必需是递增的。
     [datatimes] 整型数组，输入，实时数值时间列表,表示距离1970年1月1日08:00:00的纳秒数
     [values]    双精度浮点型数组，输入，实时浮点型数值列表，对于数据类型为 GOLDEN_REAL16、
    	GOLDEN_REAL32、GOLDEN_REAL64 的标签点，存放相应的快照值；否则忽略
     [states]    64 位整型数组，输入，实时整型数值列表，对于数据类型为 GOLDEN_BOOL、
    	GOLDEN_UINT8、GOLDEN_INT8、GOLDEN_CHAR、GOLDEN_UINT16、GOLDEN_INT16、
		GOLDEN_UINT32、GOLDEN_INT32、GOLDEN_INT64 的标签点，存放相应的快照值；否则忽略
     [qualities] 短整型数组，输入，实时数值品质列表，数据库预定义的品质参见枚举 GOLDEN_QUALITY
-返回:
     [errors]    错误信息数组，输出，写入实时数据的返回值列表，参考golden_error.h
-备注：用户须保证 ids、datatimes、ms、values、states、qualities的长度一致。
 本接口对数据类型为 GOLDEN_COOR、GOLDEN_STRING、GOLDEN_BLOB 的标签点无效。
*******************************************************************************/
func (s *RTDBService) PutSnapshots(ids []int32, datatimes []int64, values []float64, states []int64, qualities []int16) []error {
	var count int32 = int32(len(ids))

	secondes := make([]int32, count) //秒,表示距离1970年1月1日08:00:00的秒数
	ms := make([]int16, count)       //毫秒，对于时间精度为毫秒的标签点，返回相应的毫秒值；否则为 0
	errs := make([]uint32, count)    //错误码
	errors := make([]error, count)
	for i, dtime := range datatimes { //将时间戳分为毫秒和秒两部分
		secondes[i], ms[i] = splitUnixNanoSec(dtime)
	}

	gos_put_snapshots.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(&count)),
		uintptr(unsafe.Pointer(&ids[0])),
		uintptr(unsafe.Pointer(&secondes[0])),
		uintptr(unsafe.Pointer(&ms[0])),
		uintptr(unsafe.Pointer(&values[0])),
		uintptr(unsafe.Pointer(&states[0])),
		uintptr(unsafe.Pointer(&qualities[0])),
		uintptr(unsafe.Pointer(&errs[0])),
	)
	for i, err := range errs {
		errors[i] = s.FormatErrMsg(uintptr(err))
	}
	return errors
}

/*******************************************************************************
- 功能：获取单个标签点在一段时间范围内的存储值数量.
- 输入：
     [id]       整型，输入，标签点标识
     [bgtime]   整型，输入，表示起始时间UnixNano秒数。如果为 0，表示从存档中最早时间的数据开始读取
     [endtime]  整型，输入，表示结束时间UnixNano秒数。如果为 0，表示读取直至存档中数据的最后时间
- 输出:
     [count]    整型，输出，返回上述时间范围内的存储值数量
备注：bgtime可以大于endtime,此时前者表示结束时间，后者表示起始时间。
*******************************************************************************/
func (s *RTDBService) ArchivedValuesCount(id int32, bgtime, endtime int64) int32 {
	var count int32 = 0
	sec1, ms1 := splitUnixNanoSec(bgtime)
	sec2, ms2 := splitUnixNanoSec(endtime)
	goh_archived_values_count.Call(
		uintptr(s.Handle),
		uintptr(id),
		uintptr(sec1),
		uintptr(ms1),
		uintptr(sec2),
		uintptr(ms2),
		uintptr(unsafe.Pointer(&count)),
	)
	return count
}

/*******************************************************************************
- 功能：读取单个标签点一段时间内的储存数据
- 输入：
     [id]       整型，输入，标签点标识
     [bgtime]   整型，输入，表示起始时间UnixNano秒数。如果为 0，表示从存档中最早时间的数据开始读取
     [endtime]  整型，输入，表示结束时间UnixNano秒数。如果为 0，表示读取直至存档中数据的最后时间
- 输出:
	 [times]    整型数组，输出，实时数值时间列表,表示距离1970年1月1日08:00:00的毫秒数
     [values]   双精度浮点数数组，输出，历史浮点型数值列表,对于数据类型为 GOLDEN_REAL16、
    	GOLDEN_REAL32、GOLDEN_REAL64 的标签点，存放相应的历史存储值；否则为 0
     [states]   64位整数数组，输出，历史整型数值列表，对于数据类型为 GOLDEN_BOOL、
	    GOLDEN_UINT8、GOLDEN_INT8、GOLDEN_CHAR、GOLDEN_UINT16、
	    GOLDEN_INT16、GOLDEN_UINT32、GOLDEN_INT32、GOLDEN_INT64 的标签点，存
	    放相应的历史存储值；否则为 0
     [qualities] 短整型数组，输出，历史数值品质列表，数据库预定义的品质参见枚举GOLDEN_QUALITY
- 备注：bgtime可以大于endtime,此时前者表示结束时间，后者表示起始时间。
    本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
*******************************************************************************/
func (s *RTDBService) GetArchivedValues(id int32, bgtime int64, endtime int64) ([]int64, []float64, []int64, []int16) {
	count := s.ArchivedValuesCount(id, bgtime, endtime) //读取历史数据数量

	//整型数组，输入/输出，输入时第一个元素表示起始时间秒数，最后一个元素表示结束时间
	//秒数，如果为 0，表示直到数据的最后时间；输出时表示对应的历史数值时间秒数。
	datetimes := make([]int32, count)

	//短整型数组，输入/输出，如果 id 指定的标签点时间精度为毫秒，则输入时第一个元素
	//表示起始时间毫秒，最后一个元素表示结束时间毫秒；输出时表示对应的历史数值时间毫
	//秒。否则忽略输入，输出时为 0。
	ms := make([]int16, count)
	times := make([]int64, count)

	values := make([]float64, count)
	states := make([]int64, count)
	qualities := make([]int16, count)
	if count > 0 {
		datetimes[count-1], ms[count-1] = splitUnixNanoSec(endtime)
		datetimes[0], ms[0] = splitUnixNanoSec(bgtime)

		goh_get_archived_values.Call(
			uintptr(s.Handle),
			uintptr(id),
			uintptr(unsafe.Pointer(&count)),
			uintptr(unsafe.Pointer(&datetimes[0])),
			uintptr(unsafe.Pointer(&ms[0])),
			uintptr(unsafe.Pointer(&values[0])),
			uintptr(unsafe.Pointer(&states[0])),
			uintptr(unsafe.Pointer(&qualities[0])),
		)
	}
	for i, sec := range datetimes {
		times[i] = int64(sec)*1e3 + int64(ms[i])
	}
	return times, values, states, qualities
}

/*******************************************************************************
- 功能：读取单个标签点某个时间的历史数据
- 输入：
     [id]       整型，输入，标签点标识
     [mode]     整型，输入，取值 GOLDEN_NEXT、GOLDEN_PREVIOUS、GOLDEN_EXACT、
    			GOLDEN_INTER 之一：
    				 GOLDEN_NEXT(0) 寻找下一个最近的数据；
   					 GOLDEN_PREVIOUS(1) 寻找上一个最近的数据；
    				 GOLDEN_EXACT(2) 取指定时间的数据，如果没有则返回错误 GoE_DATA_NOT_FOUND；
    				 GOLDEN_INTER(3) 取指定时间的内插值数据。
     [datetime] 整型，输入，表示UnixNano秒数
- 输出:
	 [datatime] 整型,Unix毫秒数；表示实际取得的历史数值对应的时间秒数。
     [value]    双精度浮点数，输出，浮点型历史数值,对于数据类型为 GOLDEN_REAL16、
    			GOLDEN_REAL32、GOLDEN_REAL64 的标签点，存放相应的历史值；否则为 0
     [state]    64 位整数，输出，整型历史数值，对于数据类型为 GOLDEN_BOOL、GOLDEN_UINT8、
    			GOLDEN_INT8、GOLDEN_CHAR、GOLDEN_UINT16、GOLDEN_INT16、
				GOLDEN_UINT32、GOLDEN_INT32、GOLDEN_INT64 的标签点，存放相应的历史值；否则为 0
     [quality]  短整型，输出，历史值品质，数据库预定义的品质参见枚举 GOLDEN_QUALITY
 备注：本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
*******************************************************************************/
func (s *RTDBService) GetSingleValue(id, mode int32, datetime int64) (int64, float64, int64, int16, error) {
	sec, ms := splitUnixNanoSec(datetime)
	var values float64
	var states int64
	var qualities int16
	var datatime int64
	code, _, _ := goh_get_single_value.Call(
		uintptr(s.Handle),
		uintptr(id),
		uintptr(mode),
		uintptr(unsafe.Pointer(&sec)),
		uintptr(unsafe.Pointer(&ms)),
		uintptr(unsafe.Pointer(&values)),
		uintptr(unsafe.Pointer(&states)),
		uintptr(unsafe.Pointer(&qualities)),
	)
	datatime = int64(sec)*1e3 + int64(ms)
	return datatime, values, states, qualities, s.FormatErrMsg(code)
}

/*******************************************************************************
- 功能：获取单个标签点一段时间内的统计值，以及用于计算统计值的数据个数。
- 输入：
     [id]       整型，输入，标签点标识
     [bgtime]   整型，输入，表示起始时间UnixNano秒数。如果为 0，表示从存档中最早时间的数据开始读取
     [endtime]  整型，输入，表示结束时间UnixNano秒数。如果为 0，表示读取直至存档中数据的最后时间
- 输出:
	 [max_time]    整形,最大值对应的Unix毫秒时间.如果为 0,则表示无最大值
	 [min_time]    整形,最小值对应的Unix毫秒时间.如果为 0,则表示无最小值
     [max_value]   双精度浮点型，输出，表示统计时间段内的最大数值。
     [min_value]   双精度浮点型，输出，表示统计时间段内的最小数值。
     [total_value] 双精度浮点型，输出，表示统计时间段内的累计值，结果的单位为标签点的工程单位。
     [calc_avg]    双精度浮点型，输出，表示统计时间段内的算术平均值。
     [power_avg]   双精度浮点型，输出，表示统计时间段内的加权平均值。
     [count]       整型，输出，表示统计时间段内用于计算统计值的数据个数。
- 备注：bgtime可以大于endtime,此时前者表示结束时间，后者表示起始时间。
	如果输出的最大值或最小值的时间戳秒值为 0，则表明仅有累计值和加权平均值输出有效，其余统计结果无效。
  	本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
*******************************************************************************/
func (s *RTDBService) SummaryEx(id int32, bgtime, endtime int64) (int64, int64, float64, float64, float64, float64, float64, int32) {
	var count int32 = 0
	sec1, ms1 := splitUnixNanoSec(bgtime)
	sec2, ms2 := splitUnixNanoSec(endtime)
	var min_time, max_time int64
	var min_value, max_value, total_value, calc_avg, power_avg float64
	goh_summary_ex.Call(
		uintptr(s.Handle),
		uintptr(id),
		uintptr(unsafe.Pointer(&sec1)),
		uintptr(unsafe.Pointer(&ms1)),
		uintptr(unsafe.Pointer(&sec2)),
		uintptr(unsafe.Pointer(&ms2)),
		uintptr(unsafe.Pointer(&max_value)),
		uintptr(unsafe.Pointer(&min_value)),
		uintptr(unsafe.Pointer(&total_value)),
		uintptr(unsafe.Pointer(&calc_avg)),
		uintptr(unsafe.Pointer(&power_avg)),
		uintptr(unsafe.Pointer(&count)),
	)
	max_time = int64(sec1)*1e3 + int64(ms1)
	min_time = int64(sec2)*1e3 + int64(ms2)
	return max_time, min_time, max_value, min_value, total_value, calc_avg, power_avg, count
}

/*******************************************************************************
- 功能：获取单个标签点一段时间内用于绘图的历史数据
- 参数：
     [id]       整型，输入，标签点标识
     [interval] 整型，输入，时间区间数量，单位为个，一般会使用绘图的横轴(时间轴)所用屏幕像素数，
				   	该功能将起始至结束时间等分为 interval 个区间，并返回每个区间的第一个和最
					后一个数值、最大和最小数值、一条异常数值；故参数 count 有可能输出五倍于
					interval 的历史值个数，所以推荐输入的 count 至少是 interval 的五倍。
     [bgtime]   整型，输入，表示起始时间UnixNano秒数。如果为 0，表示从存档中最早时间的数据开始读取
     [endtime]  整型，输入，表示结束时间UnixNano秒数。如果为 0，表示读取直至存档中数据的最后时间
- 输出:
	 [datatimes]整型数组，输出，实时数值时间列表,表示距离1970年1月1日08:00:00的毫秒数
     [values]   双精度浮点数数组，输出，浮点型历史值数值列表,对于数据类型为 GOLDEN_REAL16、
    				GOLDEN_REAL32、GOLDEN_REAL64 的标签点，存放相应的历史值；否则为 0
     [states]   64 位整数数组，输出，整型历史值数值列表，对于数据类型为 GOLDEN_BOOL、
    				GOLDEN_UINT8、GOLDEN_INT8、GOLDEN_CHAR、GOLDEN_UINT16、
					GOLDEN_INT16、GOLDEN_UINT32、GOLDEN_INT32、GOLDEN_INT64 的标签点，存
					放相应的历史值；否则为 0
     [qualities]短整型数组，输出，历史值品质列表，数据库预定义的品质参见枚举 GOLDEN_QUALITY
- 备注：用户须保证 datetimes、ms、values、states、qualities 的长度与 count 一致，在输入时，
		datetimes、ms 中至少应有一个元素，用以存放起始及结束时间。
		第一个元素形成的时间可以大于最后一个元素形成的时间，此时第一个元素表示结束时间，
		最后一个元素表示开始时间。
   		本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
*******************************************************************************/
func (s *RTDBService) GetPlotValues(id int32, interval int32, bgtime, endtime int64) ([]int64, []float64, []int64, []int16) {
	if interval == 0 { //不可为0
		interval = 10
	}
	var count int32 = interval * 6
	//整型数组，输入/输出，输入时第一个元素表示起始时间秒数，最后一个元素表示结束时间
	//秒数，如果为 0，表示直到数据的最后时间；输出时表示对应的历史数值时间秒数。
	datetimes := make([]int32, count)

	//短整型数组，输入/输出，如果 id 指定的标签点时间精度为毫秒，则输入时第一个元素
	//表示起始时间毫秒，最后一个元素表示结束时间毫秒；输出时表示对应的历史数值时间毫
	//秒。否则忽略输入，输出时为 0。
	ms := make([]int16, count)
	datatimes := make([]int64, count)

	values := make([]float64, count)
	states := make([]int64, count)
	qualities := make([]int16, count)

	datetimes[count-1], ms[count-1] = splitUnixNanoSec(endtime)
	datetimes[0], ms[0] = splitUnixNanoSec(bgtime)

	goh_get_plot_values.Call(
		uintptr(s.Handle),
		uintptr(id),
		uintptr(interval),
		uintptr(unsafe.Pointer(&count)),
		uintptr(unsafe.Pointer(&datetimes[0])),
		uintptr(unsafe.Pointer(&ms[0])),
		uintptr(unsafe.Pointer(&values[0])),
		uintptr(unsafe.Pointer(&states[0])),
		uintptr(unsafe.Pointer(&qualities[0])),
	)
	for i, sec := range datetimes {
		datatimes[i] = int64(sec)*1e3 + int64(ms[i])
	}
	return datatimes[:count], values[:count], states[:count], qualities[:count]
}

/*******************************************************************************
- 功能：写入单个标签点在某一时间的历史数据。
- 参数：
     [id]       整型，输入，标签点标识列表，同一个标签点标识可以出现多次，但它们的时间戳必需是递增的。
     [datatime] 整型，输入，实时数值时间列表,表示距离1970年1月1日08:00:00的纳秒数
     [value]    双精度浮点型，输入，实时浮点型数值列表，对于数据类型为 GOLDEN_REAL16、
    	GOLDEN_REAL32、GOLDEN_REAL64 的标签点，存放相应的快照值；否则忽略
     [state]    64 位整型，输入，实时整型数值列表，对于数据类型为 GOLDEN_BOOL、
    	GOLDEN_UINT8、GOLDEN_INT8、GOLDEN_CHAR、GOLDEN_UINT16、GOLDEN_INT16、
		GOLDEN_UINT32、GOLDEN_INT32、GOLDEN_INT64 的标签点，存放相应的快照值；否则忽略
     [quality] 短整型，输入，实时数值品质列表，数据库预定义的品质参见枚举 GOLDEN_QUALITY
 备注：本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
      如果 datatime 标识的数据已经存在，其值将被替换。
    【【【【【【【写入的数据始终为0】】】】】】
*******************************************************************************/
func (s *RTDBService) PutSingleValue(id int32, datatime int64, value float64, state int64, quality int16) error {
	sec, ms := splitUnixNanoSec(datatime)
	//fmt.Println(id, datatime, value, sec, ms)
	code, _, _ := goh_put_single_value.Call(
		uintptr(s.Handle),
		uintptr(id),
		uintptr(sec),
		uintptr(ms),
		uintptr(value),
		uintptr(state),
		uintptr(quality),
	)
	return s.FormatErrMsg(code)
}

/*******************************************************************************
- 功能：写入批量标签点批量历史存储数据
- 输入：
     [ids]           整型数组，输入，标签点标识，同一个标签点标识可以出现多次，但它们的时间戳必需是递增的。
     [datatimes] 	 整型数组，输入，实时数值时间列表,表示距离1970年1月1日08:00:00的纳秒数
     [values]        双精度浮点数数组，输入，浮点型历史数值列表,对于数据类型为 GOLDEN_REAL16、
    					GOLDEN_REAL32、GOLDEN_REAL64 的标签点，表示相应的历史存储值；否则忽略
     [states]        64 位整数数组，输入，整型历史数值列表，对于数据类型为 GOLDEN_BOOL、
    					GOLDEN_UINT8、GOLDEN_INT8、GOLDEN_CHAR、GOLDEN_UINT16、
						GOLDEN_INT16、GOLDEN_UINT32、GOLDEN_INT32、GOLDEN_INT64 的标签点，表
						示相应的历史存储值；否则忽略
     [qualities]     短整型数组，输入，历史数值品质列表，数据库预定义的品质参见枚举GOLDEN_QUALITY
- 输出:
     [errors]        无符号整型数组，输出，写入历史数据的返回值列表，参考golden_error.h
  备注：用户须保证 ids、datetimes、ms、values、states、qualities、errors 的长度与 count 一致，
	本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
  	如果 datetimes、ms 标识的数据已经存在，其值将被替换。
*******************************************************************************/
func (s *RTDBService) PutArchivedValues(ids []int32, datatimes []int64, values []float64, states []int64, qualities []int16) []error {
	var count int32 = int32(len(ids))

	secondes := make([]int32, count) //秒,表示距离1970年1月1日08:00:00的秒数
	ms := make([]int16, count)       //毫秒，对于时间精度为毫秒的标签点，返回相应的毫秒值；否则为 0
	errs := make([]uint32, count)    //错误码
	errors := make([]error, count)
	for i, dtime := range datatimes { //将时间戳分为毫秒和秒两部分
		secondes[i], ms[i] = splitUnixNanoSec(dtime)
	}
	goh_put_archived_values.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(&count)),
		uintptr(unsafe.Pointer(&ids[0])),
		uintptr(unsafe.Pointer(&secondes[0])),
		uintptr(unsafe.Pointer(&ms[0])),
		uintptr(unsafe.Pointer(&values[0])),
		uintptr(unsafe.Pointer(&states[0])),
		uintptr(unsafe.Pointer(&qualities[0])),
		uintptr(unsafe.Pointer(&errs[0])),
	)
	for i, err := range errs {
		errors[i] = s.FormatErrMsg(uintptr(err))
		s.FlushArchivedValues(ids[i]) //补写缓存进入历史文档
	}
	return errors
}

/*******************************************************************************
- 功能：将标签点未写满的补历史缓存页写入存档文件中。
- 输入：
     [id]            整型，输入，标签点标识。
- 输出:
     [count]         整型，输出，缓存页中数据个数。
- 备注：补历史缓存页写满后会自动写入存档文件中，不满的历史缓存页也会写入文件，但会有一个时间延迟，
		在此期间此段数据可能查询不到，为了及时看到补历史的结果，应在结束补历史后调用本接口。
  count 参数可为空指针，对应的信息将不再返回。
*******************************************************************************/
func (s *RTDBService) FlushArchivedValues(id int32) int32 {
	var count int32 = 0
	goh_flush_archived_values.Call(
		uintptr(s.Handle),
		uintptr(id),
		uintptr(unsafe.Pointer(&count)),
	)
	return count
}

/*******************************************************************************
- 功能：取得标签点表总数
- 输入：
- 输出:
     [count]  整型，输出，标签点表总数。
- 备注：
*******************************************************************************/
func (s *RTDBService) GetTablesCount() (int32, error) {
	var count int32 = 0
	code, _, _ := gob_tables_count.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(&count)),
	)
	return count, s.FormatErrMsg(code)
}

/*******************************************************************************
- 功能：配置 api 行为参数
- 参数：
   [type]   整型，输入，选项类别：参见枚举 GOLDEN_API_OPTION
				GOLDEN_API_AUTO_RECONN(0):api 在连接中断后是否自动重连, 0 不重连；1 重连。默认为 0 不重连
				GOLDEN_API_CONN_TIMEOUT(1):api 连接超时值设置（单位：秒）,0 阻塞模式，无限等待，默认为0
   [value]  整型，输入，选项值。
- 备注：选项设置后在下一次调用 api 时才生效。
*******************************************************************************/
func (s *RTDBService) SetOption(apiType int32, value int32) {
	go_set_option.Call(uintptr(apiType), uintptr(value))
}

/*******************************************************************************
- 功能：取得标签点表总数
- 输入：
- 输出:
     [count]  整型，输出，标签点表总数。
- 备注：【未测试成功】
*******************************************************************************/
func (s *RTDBService) GetTablesProperty(tableid int) (GOLDEN_TABLE, error) {
	var table GOLDEN_TABLE
	table.Id = tableid
	code, _, _ := gob_get_table_property_by_id.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(&table)),
	)
	return table, s.FormatErrMsg(code)
}
