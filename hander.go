package goldengo

/*
/// 标签点索引表属性集。
#include "incloud/golden.h"
int getPointType(GOLDEN_POINT p){
	return p.type;
}
GOLDEN_POINT setPointType(GOLDEN_POINT p,int tp){
	p.type=tp;
	return p;
}
*/
import "C" //注意:import C与上面的C代码之间不能有空行
import (
	"fmt"
	"strconv"
	"strings"
	"syscall"
	"unsafe"

	"github.com/astaxie/beego/logs"
)

/*******************************************************************************
// 获取API版本号
*******************************************************************************/
func (s *RTDBService) GetAPIVersion() (string, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var major int32
	var minor int32
	var beta int32
	ecode, _, _ := go_get_api_version.Call(
		uintptr(unsafe.Pointer(&major)),
		uintptr(unsafe.Pointer(&minor)),
		uintptr(unsafe.Pointer(&beta)),
	)
	return fmt.Sprintf("%d.%d.%d", major, minor, beta), FormatErrMsg(ecode)
}

/*******************************************************************************
- 功能:创建实时数据库对象
- 参数:
	[hostname]  字符串，输入，GOLDEN 数据平台服务器的网络地址或机器名
	[user]		用户名,字符串,缺省值 sa
	[password]	密码,字符串,缺省值 golden
	[port]      端口号,整型,缺省值 6327
- 输出:
	[*RTDBService] 实时数据库对象
- 备注:在调用所有的接口函数之前，必须先调用本函数建立RTDBService对象。
*******************************************************************************/
func CreateRTDB(hostname, username, password string, port ...int) *RTDBService {
	rtdb := new(RTDBService)
	rtdb.HostName = hostname
	rtdb.UserName = username
	rtdb.Password = password
	rtdb.Port = 6327
	if len(port) > 0 {
		rtdb.Port = port[0]
	}
	return rtdb
}

/*******************************************************************************
- 功能:建立同 GOLDEN 数据库的网络连接
- 参数:无
- 输出:
	[error]        错误信息
- 备注:在调用所有的接口函数之前，必须先调用本函数建立同Golden服务器的连接。
*******************************************************************************/
func (s *RTDBService) connect() error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	host, _ := syscall.BytePtrFromString(s.HostName)
	p := int32(s.Port) //默认端口号
	code, _, _ := go_connect.Call(uintptr(unsafe.Pointer(host)), uintptr(p), uintptr(unsafe.Pointer(&s.Handle)))
	var err error
	if code == 0 {
		err = s.login(s.UserName, s.Password) //登录
	} else {
		err = FormatErrMsg(code)
	}
	return err
}

/*******************************************************************************
- 功能:断开同 GOLDEN 数据平台的连接
- 参数:无
- 备注:完成对 GOLDEN 的访问后调用本函数断开连接。
  连接一旦断开，则需要重新连接后才能调用其他的接口函数。
*******************************************************************************/
func (s *RTDBService) disConnect() error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	code, _, _ := go_disconnect.Call(uintptr(s.Handle))
	return FormatErrMsg(code)
}

/*******************************************************************************
- 功能:以有效帐户登录
- 参数:
 	[user]      字符串，输入，登录帐户
	[password]  字符串，输入，帐户口令
- 返回:登录正确返回nil，错误返回错误码
/*******************************************************************************/
func (s *RTDBService) login(user string, password string) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	usr, _ := syscall.BytePtrFromString(user)
	pad, _ := syscall.BytePtrFromString(password)
	code, _, _ := go_login.Call(uintptr(s.Handle), uintptr(unsafe.Pointer(usr)), uintptr(unsafe.Pointer(pad)), uintptr(unsafe.Pointer(&s.Priv)))
	return FormatErrMsg(code)
}

/*******************************************************************************
- 功能:获取 GOLDEN 服务器当前UTC时间
- 参数:无
- 返回:[hosttime]     整型，输出，Golden服务器的当前UTC时间，表示距离1970年1月1日08:00:00的秒数。
/*******************************************************************************/
func (s *RTDBService) HostTime() (int64, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var hosttime int32 = 0
	ecode, _, _ := go_host_time.Call(uintptr(s.Handle), uintptr(unsafe.Pointer(&hosttime)))
	return int64(hosttime), FormatErrMsg(ecode)
}

/*******************************************************************************
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
- 返回: [ids]           整型数组，输出，返回搜索到的标签点标识列表
	 [error]         错误信息
- 备注:用户须保证分配给 ids 的空间与 count 相符，各参数中包含的搜索条件之间的关系为"与"的关系，
	用包含通配符的标签点名称作搜索条件时，如果第一个字符不是通配符(如"ai67*")，会得到最快的搜索速度。
 	如果 tagmask、tablemask 为空指针，则表示使用缺省设置"*",
 	多个搜索条件可以通过空格分隔，比如"demo_*1 demo_*2"，会将满足demo_*1或者demo_*2条件的标签点搜索出来。
*******************************************************************************/
func (s *RTDBService) Search(tagmask, tablemask, source, unit, desc, instrument string, mode int) ([]int, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	_tagmask, _ := syscall.BytePtrFromString(tagmask)
	_tablemask, _ := syscall.BytePtrFromString(tablemask)
	_source, _ := syscall.BytePtrFromString(source)
	_unit, _ := syscall.BytePtrFromString(unit)
	_desc, _ := syscall.BytePtrFromString(desc)
	_instrument, _ := syscall.BytePtrFromString(instrument)

	var count int32 = _MAX_POINT_IN_SEARCH
	ids := make([]int32, count)
	code, _, _ := gob_search.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(_tagmask)),
		uintptr(unsafe.Pointer(_tablemask)),
		uintptr(unsafe.Pointer(_source)),
		uintptr(unsafe.Pointer(_unit)),
		uintptr(unsafe.Pointer(_desc)),
		uintptr(unsafe.Pointer(_instrument)),
		uintptr(int32(mode)), uintptr(unsafe.Pointer(&ids[0])),
		uintptr(unsafe.Pointer(&count)),
	)
	oids := make([]int, count)
	for i := range oids {
		oids[i] = int(ids[i])
	}
	return oids, FormatErrMsg(code)
}

/*******************************************************************************
- 功能:根据 "表名.标签点名" 格式批量获取标签点标识
- 参数:
	 [table_dot_tags]   字符串数组，输入，"表名.标签点名" 列表
- 返回:
	 [ids]              整型数组，输出，标签点标识列表, 返回 0 表示未找到
	 [types]            整型数组，输出，标签点数据类型
	 [classof]          整型数组，输出，标签点类别
	 [use_ms]           整型数组，输出，时间戳精度， 返回 1 表示时间戳精度为毫秒， 为 0 表示为秒。
- 备注:
*******************************************************************************/
func (s *RTDBService) FindPoints(table_dot_tags ...string) ([]int, []int, []int, []int, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	count := len(table_dot_tags) //标签点个数(即table_dot_tags、ids、types、classof、use_ms 的长度
	var isms []int
	var oids []int
	var otypes []int
	var oclassof []int
	var code uintptr
	//var lasterr error
	if count > 0 {
		tags := make([]*byte, count)
		ids := make([]int32, count)
		types := make([]int32, count)
		classof := make([]int32, count)
		use_ms := make([]int16, count)
		for i, tagstr := range table_dot_tags {
			strs := strings.Split(tagstr, ".")
			if len(strs) < 2 {
				return oids, otypes, oclassof, isms, fmt.Errorf("标签名[%s]不合法,标签名应为[tablename.tagname]格式", tagstr)
			}
			tag := Utf8ToGbk([]byte(tagstr))
			tags[i] = &tag[0]
		}
		//fmt.Sprintf("查询标签点时的标签列表:[%+v]\n", table_dot_tags) //=============================
		code, _, _ = gob_find_points.Call(
			uintptr(s.Handle),
			uintptr(unsafe.Pointer(&count)),
			uintptr(unsafe.Pointer(&tags[0])),
			uintptr(unsafe.Pointer(&ids[0])),
			uintptr(unsafe.Pointer(&types[0])),
			uintptr(unsafe.Pointer(&classof[0])),
			uintptr(unsafe.Pointer(&use_ms[0])),
		)
		//fmt.Printf("Code:%+v,R2:%+v,LastErr:+%v\n", code, r2, lasterr) //========================
		for i, ms := range use_ms {
			isms = append(isms, int(ms))
			oids = append(oids, int(ids[i]))
			otypes = append(otypes, int(types[i]))
			oclassof = append(oclassof, int(classof[i]))
		}
	}
	return oids, otypes, oclassof, isms, FormatErrMsg(code)
}

/*******************************************************************************
- 功能:批量读取开关量、模拟量快照数值
- 参数:
     [ids]       整型数组，输入，标签点标识列表
- 返回:
     [datetimes] 整型数组，输出，实时数值时间列表,表示距离1970年1月1日08:00:00的毫秒数
     [values]    双精度浮点型数组，输出，实时浮点型数值列表，对于数据类型为 GOLDEN_REAL16、
    	GOLDEN_REAL32、GOLDEN_REAL64 的标签点，返回相应的快照值；否则为 0
     [states]    64 位整型数组，输出，实时整型数值列表，对于数据类型为 GOLDEN_BOOL、
    	GOLDEN_UINT8、GOLDEN_INT8、GOLDEN_CHAR、GOLDEN_UINT16、GOLDEN_INT16、
		GOLDEN_UINT32、GOLDEN_INT32、GOLDEN_INT64 的标签点，返回相应的快照值；否则为0
     [qualities] 短整型数组，输出，实时数值品质列表，数据库预定义的品质参见枚举 GOLDEN_QUALITY
     [errors]    错误信息数组，输出，读取实时数据的错误返回值列表，参考golden_error.h
- 备注:本接口对数据类型为 GOLDEN_COOR、GOLDEN_STRING、GOLDEN_BLOB 的标签点无效。
*******************************************************************************/
func (s *RTDBService) GetSnapshots(ids []int) ([]int64, []float64, []int64, []int, []error, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var count int32 = int32(len(ids))
	var pids []int32
	for _, id := range ids {
		pids = append(pids, int32(id))
	}
	secondes := make([]int32, count)  //秒,表示距离1970年1月1日08:00:00的秒数
	ms := make([]int16, count)        //毫秒，对于时间精度为毫秒的标签点，返回相应的毫秒值；否则为 0
	values := make([]float64, count)  //浮点型值
	states := make([]int64, count)    //整数值
	qualities := make([]int32, count) //质量码
	errs := make([]uint32, count)     //错误码

	datetimes := make([]int64, count) //unix毫秒值，表示距离1970年1月1日08:00:00的毫秒数
	errors := make([]error, count)    //错误信息
	var qual []int
	var ecode uintptr
	if count > 0 {
		ecode, _, _ = gos_get_snapshots.Call(
			uintptr(s.Handle),
			uintptr(unsafe.Pointer(&count)),
			uintptr(unsafe.Pointer(&pids[0])),
			uintptr(unsafe.Pointer(&secondes[0])),
			uintptr(unsafe.Pointer(&ms[0])),
			uintptr(unsafe.Pointer(&values[0])),
			uintptr(unsafe.Pointer(&states[0])),
			uintptr(unsafe.Pointer(&qualities[0])),
			uintptr(unsafe.Pointer(&errs[0])),
		)

		for i := range ids {
			datetimes[i] = int64(secondes[i])*1000 + int64(ms[i])
			errors[i] = FormatErrMsg(uintptr(errs[i]))
			qual = append(qual, int(qualities[i]))
		}
	}
	return datetimes, values, states, qual, errors, FormatErrMsg(ecode)
}

/*******************************************************************************
- 功能:批量写入开关量、模拟量快照数值
- 参数:
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
    [error]    错误信息
-备注:用户须保证 ids、datatimes、ms、values、states、qualities的长度一致。
 本接口对数据类型为 GOLDEN_COOR、GOLDEN_STRING、GOLDEN_BLOB 的标签点无效。
*******************************************************************************/
func (s *RTDBService) PutSnapshots(ids []int, datatimes []int64, values []float64, states []int64, qualities []int16) ([]error, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var count int32 = int32(len(ids))
	if count > 0 {
		var pids []int32
		for _, id := range ids {
			pids = append(pids, int32(id))
		}
		secondes := make([]int32, count) //秒,表示距离1970年1月1日08:00:00的秒数
		ms := make([]int16, count)       //毫秒，对于时间精度为毫秒的标签点，返回相应的毫秒值；否则为 0
		errs := make([]uint32, count)    //错误码
		errors := make([]error, count)
		for i, dtime := range datatimes { //将时间戳分为毫秒和秒两部分
			secondes[i], ms[i] = splitUnixNanoSec(dtime)
		}

		ecode, _, _ := gos_put_snapshots.Call(
			uintptr(s.Handle),
			uintptr(unsafe.Pointer(&count)),
			uintptr(unsafe.Pointer(&pids[0])),
			uintptr(unsafe.Pointer(&secondes[0])),
			uintptr(unsafe.Pointer(&ms[0])),
			uintptr(unsafe.Pointer(&values[0])),
			uintptr(unsafe.Pointer(&states[0])),
			uintptr(unsafe.Pointer(&qualities[0])),
			uintptr(unsafe.Pointer(&errs[0])),
		)
		for i, err := range errs {
			errors[i] = FormatErrMsg(uintptr(err))
		}
		return errors, FormatErrMsg(ecode)
	} else {
		return nil, fmt.Errorf("写快照时输入的数组长度为0")
	}
}

/*******************************************************************************
- 功能:获取单个标签点在一段时间范围内的存储值数量.
- 输入:
     [id]       整型，输入，标签点标识
     [bgtime]   整型，输入，表示起始时间UnixNano秒数。如果为 0，表示从存档中最早时间的数据开始读取
     [endtime]  整型，输入，表示结束时间UnixNano秒数。如果为 0，表示读取直至存档中数据的最后时间
- 输出:
     [count]    整型，输出，返回上述时间范围内的存储值数量
备注:bgtime可以大于endtime,此时前者表示结束时间，后者表示起始时间。
*******************************************************************************/
func (s *RTDBService) ArchivedValuesCount(id int, bgtime, endtime int64) (int, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var count int32 = 0
	sec1, ms1 := splitUnixNanoSec(bgtime)
	sec2, ms2 := splitUnixNanoSec(endtime)
	ecode, _, _ := goh_archived_values_count.Call(
		uintptr(s.Handle),
		uintptr(int32(id)),
		uintptr(sec1),
		uintptr(ms1),
		uintptr(sec2),
		uintptr(ms2),
		uintptr(unsafe.Pointer(&count)),
	)
	return int(count), FormatErrMsg(ecode)
}

/*******************************************************************************
- 功能:读取单个标签点一段时间内的储存数据
- 输入:
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
- 备注:bgtime可以大于endtime,此时前者表示结束时间，后者表示起始时间。
    本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
*******************************************************************************/
func (s *RTDBService) GetArchivedValues(id int, bgtime int64, endtime int64) ([]int64, []float64, []int64, []int16, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	datacount, err := s.ArchivedValuesCount(id, bgtime, endtime) //读取历史数据数量
	//fmt.Printf("查询到的历史数据的数量为:%d ==============================\n", datacount)
	count := datacount
	if datacount == 1 {
		count += 1
	}
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
	if err == nil {
		if count > 0 {
			datetimes[count-1], ms[count-1] = splitUnixNanoSec(endtime)
			datetimes[0], ms[0] = splitUnixNanoSec(bgtime)

			ecode, _, _ := goh_get_archived_values.Call(
				uintptr(s.Handle),
				uintptr(int32(id)),
				uintptr(unsafe.Pointer(&count)),
				uintptr(unsafe.Pointer(&datetimes[0])),
				uintptr(unsafe.Pointer(&ms[0])),
				uintptr(unsafe.Pointer(&values[0])),
				uintptr(unsafe.Pointer(&states[0])),
				uintptr(unsafe.Pointer(&qualities[0])),
			)
			err = FormatErrMsg(ecode)
		}
		for i, sec := range datetimes {
			times[i] = int64(sec)*1e3 + int64(ms[i])
		}
	}
	//fmt.Printf("结果数组:%v =========1========\n", times)
	if datacount == 1 || (datacount == 2 && endtime/1e6 == times[1] && values[1] == 0) {
		times = append(times[:1], times[2:]...)
		values = append(values[:1], values[2:]...)
		states = append(states[:1], states[2:]...)
		qualities = append(qualities[:1], qualities[2:]...)
	}
	//fmt.Printf("结果数组:%v =========2========\n", times)
	//fmt.Printf("时间:%v,数值:%v,状态:%v,质量:%v,错误信息:%v *******************\n", times, values, states, qualities, err)
	return times, values, states, qualities, err
}

/*******************************************************************************
- 功能:获取单个标签点一段时间内等间隔历史插值
- 输入:
     [id]       整型,输入,标签点标识
     [count]	整形,需要的插值个数
     [bgtime]   整型,输入,表示起始时间UnixNano秒数。如果为 0，表示从存档中最早时间的数据开始读取
     [endtime]  整型,输入,表示结束时间UnixNano秒数。如果为 0，表示读取直至存档中数据的最后时间
- 输出:
	 [times]    整型数组，输出，实时数值时间列表,表示距离1970年1月1日08:00:00的毫秒数
     [values]   双精度浮点数数组，输出，历史浮点型数值列表,对于数据类型为 GOLDEN_REAL16、
    	GOLDEN_REAL32、GOLDEN_REAL64 的标签点，存放相应的历史存储值；否则为 0
     [states]   64位整数数组，输出，历史整型数值列表，对于数据类型为 GOLDEN_BOOL、
	    GOLDEN_UINT8、GOLDEN_INT8、GOLDEN_CHAR、GOLDEN_UINT16、
	    GOLDEN_INT16、GOLDEN_UINT32、GOLDEN_INT32、GOLDEN_INT64 的标签点，存
	    放相应的历史存储值；否则为 0
     [qualities] 短整型数组，输出，历史数值品质列表，数据库预定义的品质参见枚举GOLDEN_QUALITY
- 备注:bgtime可以大于endtime,此时前者表示结束时间，后者表示起始时间。
    本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
*******************************************************************************/
func (s *RTDBService) GetInterpoValues(id, cnt int, bgtime int64, endtime int64) ([]int64, []float64, []int64, []int16, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	count := int32(cnt)
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
	var err error
	if count > 0 {
		datetimes[count-1], ms[count-1] = splitUnixNanoSec(endtime)
		datetimes[0], ms[0] = splitUnixNanoSec(bgtime)

		ecode, _, _ := goh_get_interpo_values.Call(
			uintptr(s.Handle),
			uintptr(int32(id)),
			uintptr(unsafe.Pointer(&count)),
			uintptr(unsafe.Pointer(&datetimes[0])),
			uintptr(unsafe.Pointer(&ms[0])),
			uintptr(unsafe.Pointer(&values[0])),
			uintptr(unsafe.Pointer(&states[0])),
			uintptr(unsafe.Pointer(&qualities[0])),
		)
		err = FormatErrMsg(ecode)
	}
	for i, sec := range datetimes {
		times[i] = int64(sec)*1e3 + int64(ms[i])
	}
	return times, values, states, qualities, err
}

/*******************************************************************************
- 功能:读取单个标签点某个时间点的历史数据
- 输入:
     [id]       整型，输入，标签点标识
     [mode]     整型，输入，取值 GOLDEN_NEXT(0)、GOLDEN_PREVIOUS(1)、GOLDEN_EXACT(2)、
    			GOLDEN_INTER(3) 之一:
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
 备注:本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
*******************************************************************************/
func (s *RTDBService) GetSingleValue(id, mode int, datetime int64) (int64, float64, int64, int16, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	sec, ms := splitUnixNanoSec(datetime)
	var values float64
	var states int64
	var qualities int16
	var datatime int64
	code, _, _ := goh_get_single_value.Call(
		uintptr(s.Handle),
		uintptr(int32(id)),
		uintptr(int32(mode)),
		uintptr(unsafe.Pointer(&sec)),
		uintptr(unsafe.Pointer(&ms)),
		uintptr(unsafe.Pointer(&values)),
		uintptr(unsafe.Pointer(&states)),
		uintptr(unsafe.Pointer(&qualities)),
	)
	datatime = int64(sec)*1e3 + int64(ms)
	return datatime, values, states, qualities, FormatErrMsg(code)
}

/*******************************************************************************
- 功能:获取单个标签点一段时间内的统计值，以及用于计算统计值的数据个数。
- 输入:
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
- 备注:bgtime可以大于endtime,此时前者表示结束时间，后者表示起始时间。
	如果输出的最大值或最小值的时间戳秒值为 0，则表明仅有累计值和加权平均值输出有效，其余统计结果无效。
  	本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
*******************************************************************************/
func (s *RTDBService) SummaryEx(id int, bgtime, endtime int64) (int64, int64, float64, float64, float64, float64, float64, int, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var count int32 = 0
	sec1, ms1 := splitUnixNanoSec(bgtime)
	sec2, ms2 := splitUnixNanoSec(endtime)
	var min_time, max_time int64
	var min_value, max_value, total_value, calc_avg, power_avg float64
	ecode, _, _ := goh_summary_ex.Call(
		uintptr(s.Handle),
		uintptr(int32(id)),
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
	return max_time, min_time, max_value, min_value, total_value, calc_avg, power_avg, int(count), FormatErrMsg(ecode)
}

/*******************************************************************************
- 功能:获取单个标签点一段时间内用于绘图的历史数据
- 参数:
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
- 备注:用户须保证 datetimes、ms、values、states、qualities 的长度与 count 一致，在输入时，
		datetimes、ms 中至少应有一个元素，用以存放起始及结束时间。
		第一个元素形成的时间可以大于最后一个元素形成的时间，此时第一个元素表示结束时间，
		最后一个元素表示开始时间。
   		本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
*******************************************************************************/
func (s *RTDBService) GetPlotValues(id, interval int, bgtime, endtime int64) ([]int64, []float64, []int64, []int16, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	if interval == 0 { //不可为0
		interval = 10
	}
	var count int32 = int32(interval) * 6
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

	ecode, _, _ := goh_get_plot_values.Call(
		uintptr(s.Handle),
		uintptr(int32(id)),
		uintptr(int32(interval)),
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
	return datatimes[:count], values[:count], states[:count], qualities[:count], FormatErrMsg(ecode)
}

/*******************************************************************************
- 功能:写入单个标签点在某一时间的历史数据。
- 参数:
     [id]       整型，输入，标签点标识列表，同一个标签点标识可以出现多次，但它们的时间戳必需是递增的。
     [datatime] 整型，输入，实时数值时间列表,表示距离1970年1月1日08:00:00的纳秒数
     [value]    双精度浮点型，输入，实时浮点型数值列表，对于数据类型为 GOLDEN_REAL16、
    	GOLDEN_REAL32、GOLDEN_REAL64 的标签点，存放相应的快照值；否则忽略
     [state]    64 位整型，输入，实时整型数值列表，对于数据类型为 GOLDEN_BOOL、
    	GOLDEN_UINT8、GOLDEN_INT8、GOLDEN_CHAR、GOLDEN_UINT16、GOLDEN_INT16、
		GOLDEN_UINT32、GOLDEN_INT32、GOLDEN_INT64 的标签点，存放相应的快照值；否则忽略
     [quality] 短整型，输入，实时数值品质列表，数据库预定义的品质参见枚举 GOLDEN_QUALITY
 备注:本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
      如果 datatime 标识的数据已经存在，其值将被替换。
    【【【【【【【测试未通过:写入的数据始终为0】】】】】】
*******************************************************************************/
func (s *RTDBService) putSingleValue(id int, datatime int64, value float64, state int64, quality int16) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	sec, ms := splitUnixNanoSec(datatime)
	code, _, _ := goh_put_single_value.Call(
		uintptr(s.Handle),
		uintptr(int32(id)),
		uintptr(sec),
		uintptr(ms),
		uintptr(value),
		uintptr(state),
		uintptr(int16(quality)),
	)
	s.FlushArchivedValues(id) //补写缓存进入历史文档
	return FormatErrMsg(code)
}

/*******************************************************************************
- 功能:写入批量标签点批量历史存储数据
- 输入:
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
  备注:用户须保证 ids、datetimes、ms、values、states、qualities、errors 的长度与 count 一致，
	本接口对数据类型为 GOLDEN_COOR、GOLDEN_BLOB、GOLDEN_STRING 的标签点无效。
  	如果 datetimes、ms 标识的数据已经存在，其值将被替换。
*******************************************************************************/
func (s *RTDBService) PutArchivedValues(ids []int, datatimes []int64, values []float64, states []int64, qualities []int16) ([]error, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var count int32 = int32(len(ids))
	var pids []int32
	for _, id := range ids {
		pids = append(pids, int32(id))
	}
	secondes := make([]int32, count) //秒,表示距离1970年1月1日08:00:00的秒数
	ms := make([]int16, count)       //毫秒，对于时间精度为毫秒的标签点，返回相应的毫秒值；否则为 0
	errs := make([]uint32, count)    //错误码
	errors := make([]error, count)
	for i, dtime := range datatimes { //将时间戳分为毫秒和秒两部分
		secondes[i], ms[i] = splitUnixNanoSec(dtime)
	}
	ecode, _, _ := goh_put_archived_values.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(&count)),
		uintptr(unsafe.Pointer(&pids[0])),
		uintptr(unsafe.Pointer(&secondes[0])),
		uintptr(unsafe.Pointer(&ms[0])),
		uintptr(unsafe.Pointer(&values[0])),
		uintptr(unsafe.Pointer(&states[0])),
		uintptr(unsafe.Pointer(&qualities[0])),
		uintptr(unsafe.Pointer(&errs[0])),
	)
	for i, err := range errs {
		errors[i] = FormatErrMsg(uintptr(err))
		s.FlushArchivedValues(ids[i]) //补写缓存进入历史文档
	}
	return errors, FormatErrMsg(ecode)
}

/*******************************************************************************
- 功能:将标签点未写满的补历史缓存页写入存档文件中。
- 输入:
     [id]            整型，输入，标签点标识。
- 输出:
     [count]         整型，输出，缓存页中数据个数。
- 备注:补历史缓存页写满后会自动写入存档文件中，不满的历史缓存页也会写入文件，但会有一个时间延迟，
		在此期间此段数据可能查询不到，为了及时看到补历史的结果，应在结束补历史后调用本接口。
  count 参数可为空指针，对应的信息将不再返回。
*******************************************************************************/
func (s *RTDBService) FlushArchivedValues(id int) (int, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var count int32 = 0
	ecode, _, _ := goh_flush_archived_values.Call(
		uintptr(s.Handle),
		uintptr(int32(id)),
		uintptr(unsafe.Pointer(&count)),
	)
	return int(count), FormatErrMsg(ecode)
}

/*******************************************************************************
- 功能:配置 api 行为参数
- 参数:
   [type]   整型，输入，选项类别:参见枚举 GOLDEN_API_OPTION
				GOLDEN_API_AUTO_RECONN(0):api 在连接中断后是否自动重连, 0 不重连；1 重连。默认为 0 不重连
				GOLDEN_API_CONN_TIMEOUT(1):api 连接超时值设置（单位:秒）,0 阻塞模式，无限等待，默认为0
   [value]  整型，输入，选项值。
- 备注:选项设置后在下一次调用 api 时才生效。
*******************************************************************************/
func (s *RTDBService) SetOption(apiType int, value int) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	go_set_option.Call(uintptr(int32(apiType)), uintptr(int32(value)))
}

/*******************************************************************************
* 功能:取得标签点表总数
* 输入:
* 输出:
     [count]  整型，输出，标签点表总数。
* 备注:
*******************************************************************************/
func (s *RTDBService) GetTablesCount() (int, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var count int32 = 0
	code, _, _ := gob_tables_count.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(&count)),
	)
	return int(count), FormatErrMsg(code)
}

/*******************************************************************************
- 功能:取得标签点表信息
- 输入:[needpointmsg]是否需要标签点信息,0不需要,1需要；省略不需要
- 输出:  [error] 错误信息
- 备注:标签表数和标签ID同时保存到结构体中
- 时间:2020年5月14日
*******************************************************************************/
func (s *RTDBService) GetTables(needpointmsg ...bool) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	count, err := s.GetTablesCount()
	if err != nil {
		return fmt.Errorf("获取表数量时错误:[%s]", err.Error())
	}
	var ids [1000]int32
	code, _, _ := gob_get_tables.Call( //获取全部表的ID
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(&ids)),
		uintptr(unsafe.Pointer(&count)),
	)
	if e := FormatErrMsg(code); e != nil {
		return fmt.Errorf("获取表ID示错误:[%s]", e.Error())
	}
	s.TableCounts = int(count)
	s.TableIds = s.TableIds[0:0] //清空
	for _, id := range ids[:count] {
		s.TableIds = append(s.TableIds, int(id))
	}
	s.Tables = make(map[int]GoldenTable, count) //重置表
	s.Points = make(map[int]GoldenPoint)        //重置标签点
	for _, id := range s.TableIds {
		tryCnt := 0
	readtable:
		tb, err := s.GetTablesProperty(id) //获取标签点表的属性
		if err != nil {
			//return fmt.Errorf("获取标签点表属性时错误:[%s]", err.Error())
			tb.Id = id
			if strings.Contains(err.Error(), "0xFFFF2016") || strings.Contains(err.Error(), "0xFFFF2017") || strings.Contains(err.Error(), "0xFFFF2002") {
				tryCnt++
				if tryCnt < 10 {
					goto readtable
				} else {
					tb.Err = fmt.Errorf("获取标签点表属性时通讯错误,并且重试超过规定次数:[%s]", err.Error())
				}
			} else {
				tb.Err = fmt.Errorf("获取标签点表属性时错误:[%s]", err.Error())
			}
		}
		tryCnt = 0
		if len(needpointmsg) > 0 && len(tb.PointIds) > 0 { //需要标签点信息
			if needpointmsg[0] {
			readpoint:
				err = s.GetPointPropterty(tb.PointIds...) //获取变量点属性
				if err != nil {
					if strings.Contains(err.Error(), "0xFFFF2016") || strings.Contains(err.Error(), "0xFFFF2017") || strings.Contains(err.Error(), "0xFFFF2002") {
						tryCnt++
						if tryCnt < 10 {
							goto readpoint
						} else {
							tb.Err = fmt.Errorf("获取标签点属性时通讯错误,并且重试超过规定次数:[%s]", err.Error())
						}
					} else {
						tb.Err = fmt.Errorf("获取标签点属性时错误:[%s]", err.Error())
					}
				}
			}
		}
		s.Tables[int(id)] = tb
	}
	return nil
}

/*******************************************************************************
- 功能:根据表 id 获取表中包含的标签点数量
- 输入:
- 输出:
- 备注:
- 时间:2020年5月14日
*******************************************************************************/
func (t *GoldenTable) GetTableSizeById(handle int32) (int, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var size int32 = 0
	ecode, _, _ := gob_get_table_size_by_id.Call(
		uintptr(handle),
		uintptr(t.Id),
		uintptr(unsafe.Pointer(&size)),
	)
	return int(size), FormatErrMsg(ecode)
}

/*******************************************************************************
- 功能:获取表下的所有标签ID列表
- 输入: [handle] 连接句柄
		[tablename] 可选的表名切片,可以多个表名
- 输出: [[]int] id数组
		[error] 错误信息
- 备注:
- 时间:2020年5月14日
*******************************************************************************/
func (t *GoldenTable) GetPointIds(handle int32, tablename ...string) ([]int, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var nullstring string
	tbname := t.Name
	if len(tablename) > 0 {
		tbname = ""
		for i, name := range tablename {
			tbname += name
			if i+1 < len(tablename) {
				tbname += " "
			}
		}
	}
	tbname = string(Utf8ToGbk([]byte(tbname)))

	_tagmask, _ := syscall.BytePtrFromString("*")
	_tablemask, _ := syscall.BytePtrFromString(tbname)
	_source, _ := syscall.BytePtrFromString(nullstring)
	_unit, _ := syscall.BytePtrFromString(nullstring)
	_desc, _ := syscall.BytePtrFromString(nullstring)
	_instrument, _ := syscall.BytePtrFromString(nullstring)
	mode := 2 //以标签点ID排序

	var count int32 = _MAX_POINT_IN_SEARCH
	ids := make([]int32, count)
	code, _, _ := gob_search.Call(
		uintptr(handle),
		uintptr(unsafe.Pointer(_tagmask)),
		uintptr(unsafe.Pointer(_tablemask)),
		uintptr(unsafe.Pointer(_source)),
		uintptr(unsafe.Pointer(_unit)),
		uintptr(unsafe.Pointer(_desc)),
		uintptr(unsafe.Pointer(_instrument)),
		uintptr(mode),
		uintptr(unsafe.Pointer(&ids[0])),
		uintptr(unsafe.Pointer(&count)),
	)
	var pids []int
	for _, id := range ids[:count] {
		pids = append(pids, int(id))
	}
	t.PointIds = pids
	return pids, FormatErrMsg(code)
}

/*******************************************************************************
- 功能:通过已知的表名称取得标签点表属性（不含标签点信息）
- 输入:[handle] 连接句柄
- 输出:[error] 错误信息
- 备注:
- 时间:2020年6月1日
*******************************************************************************/
func (t *GoldenTable) GetTablePropertyByName(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var table C.GOLDEN_TABLE
	table.name = string2C80chars(t.Name)
	code, _, _ := gob_get_table_property_by_name.Call(
		uintptr(handle),
		uintptr(unsafe.Pointer(&table)),
	)
	if code > 0 { //有错误
		return FormatErrMsg(code)
	}

	t.Id = int(table.id)
	t.Desc = cChars2String(table.desc[:])
	return nil
}

/*******************************************************************************
- 功能:通过已知的表ID取得标签点表属性（不含标签点信息）
- 输入:[handle] 连接句柄
- 输出:[error] 错误信息
- 备注:
- 时间:2020年6月1日
*******************************************************************************/
func (t *GoldenTable) GetTablePropertyById(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var table C.GOLDEN_TABLE
	table.id = C.int(t.Id)
	code, _, _ := gob_get_table_property_by_id.Call(
		uintptr(handle),
		uintptr(unsafe.Pointer(&table)),
	)
	if code > 0 { //有错误
		return FormatErrMsg(code)
	}

	t.Name = cChars2String(table.name[:])
	t.Desc = cChars2String(table.desc[:])

	return nil
}

/*******************************************************************************
- 功能:取得标签点表属性
- 输入:
- 输出:
- 备注:
- 时间:2020年5月14日
*******************************************************************************/
func (s *RTDBService) GetTablesProperty(tableid int) (GoldenTable, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var table C.GOLDEN_TABLE
	var gtb GoldenTable
	table.id = C.int(tableid)
	code, _, _ := gob_get_table_property_by_id.Call(
		uintptr(s.Handle),
		uintptr(unsafe.Pointer(&table)),
	)
	if code > 0 { //有错误
		return gtb, FormatErrMsg(code)
	}

	gtb.Id = tableid
	gtb.Name = cChars2String(table.name[:])
	gtb.Desc = cChars2String(table.desc[:])

	_, err := gtb.GetPointIds(s.Handle)
	if err != nil {
		return gtb, err
	}
	gtb.Size = len(gtb.PointIds)
	return gtb, nil
}

/*******************************************************************************
* 命名:gob_get_points_property
* 功能:批量获取标签点属性
* 参数:[ids]   需要读取属性的id切片
* 输出:[error] 错误信息
* 备注:读取到的标签点信息保存到结构体数组的Point Map中
- 时间:2020年5月14日
*******************************************************************************/
func (s *RTDBService) GetPointPropterty(ids ...int) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	count := int32(len(ids))
	if count > 0 {
		bases := make([]C.GOLDEN_POINT, count)
		scans := make([]C.GOLDEN_SCAN_POINT, count)
		calcs := make([]C.GOLDEN_CALC_POINT, count)
		errors := make([]uint32, count)
		for i, id := range ids { //标签点ID赋值
			bases[i].id = C.int(id)
		}
		ecode, _, _ := gob_get_points_property.Call(
			uintptr(s.Handle),
			uintptr(count),
			uintptr(unsafe.Pointer(&bases[0])),
			uintptr(unsafe.Pointer(&scans[0])),
			uintptr(unsafe.Pointer(&calcs[0])),
			uintptr(unsafe.Pointer(&errors[0])),
		)
		if s.Points == nil {
			s.Points = make(map[int]GoldenPoint)
		}
		for i, id := range ids { //标签点ID赋值
			var point GoldenPoint
			base := cBasePoint2GoBasePoint(bases[i])
			err := FormatErrMsg(uintptr(errors[i]))
			if err != nil {
				base.Err = err.Error()
			}
			point.Base = base
			point.Scan = cScanPoint2GoScanPoint(scans[i])
			point.Calc = cCalcPoint2GoCalcPoint(calcs[i])
			point.PlatEx.GetFromScanPadding(point.Scan.Padding)
			s.Points[id] = point
		}
		return FormatErrMsg(ecode)
	}
	return nil
}

/*******************************************************************************
* 命名:gob_get_points_property
* 功能:获取单个标签点的属性
* 参数:[ids]   需要读取属性的id切片
* 输出:[GoldenPoint]标签点信息
	   [error] 错误信息
* 备注:读取到的信息只返回，不保存
- 时间:2020年5月14日
*******************************************************************************/
func (s *RTDBService) GetSinglePointPropterty(id int) (GoldenPoint, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var count int32 = 1
	bases := make([]C.GOLDEN_POINT, count)
	scans := make([]C.GOLDEN_SCAN_POINT, count)
	calcs := make([]C.GOLDEN_CALC_POINT, count)
	errors := make([]uint32, count)
	bases[0].id = C.int(id)
	ecode, _, _ := gob_get_points_property.Call(
		uintptr(s.Handle),
		uintptr(count),
		uintptr(unsafe.Pointer(&bases[0])),
		uintptr(unsafe.Pointer(&scans[0])),
		uintptr(unsafe.Pointer(&calcs[0])),
		uintptr(unsafe.Pointer(&errors[0])),
	)

	var point GoldenPoint
	base := cBasePoint2GoBasePoint(bases[0])
	err := FormatErrMsg(uintptr(errors[0]))
	if err != nil {
		base.Err = err.Error()
	}
	point.Base = base
	point.Scan = cScanPoint2GoScanPoint(scans[0])
	point.Calc = cCalcPoint2GoCalcPoint(calcs[0])
	point.PlatEx.GetFromScanPadding(point.Scan.Padding)

	return point, FormatErrMsg(ecode)
}

/*******************************************************************************
* 命名:gob_get_points_property
* 功能:获取单个标签点的属性
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:需要事先在结构体中保存标签点的ID，读取到的信息保存到标签点结构体中
* 时间:2020年5月27日
*******************************************************************************/
func (p *GoldenPoint) GetPointProptertyById(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	var count int32 = 1
	bases := make([]C.GOLDEN_POINT, count)
	scans := make([]C.GOLDEN_SCAN_POINT, count)
	calcs := make([]C.GOLDEN_CALC_POINT, count)
	errors := make([]uint32, count)
	bases[0].id = C.int(p.Base.Id)
	ecode, _, _ := gob_get_points_property.Call(
		uintptr(handle),
		uintptr(count),
		uintptr(unsafe.Pointer(&bases[0])),
		uintptr(unsafe.Pointer(&scans[0])),
		uintptr(unsafe.Pointer(&calcs[0])),
		uintptr(unsafe.Pointer(&errors[0])),
	)

	base := cBasePoint2GoBasePoint(bases[0])
	err := FormatErrMsg(uintptr(errors[0]))
	if err != nil {
		base.Err = err.Error()
	}
	p.Base = base
	p.Scan = cScanPoint2GoScanPoint(scans[0])
	p.Calc = cCalcPoint2GoCalcPoint(calcs[0])
	p.PlatEx.GetFromScanPadding(p.Scan.Padding)

	return FormatErrMsg(ecode)
}

/*******************************************************************************
* 命名:gob_update_point_property
* 功能:单个更新标签的属性
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:标签点由 base 参数的 id 字段指定，其中 id、table、type、millisecond 字段不能修改
changedate、changer、createdate、creator 字段由系统维护，其余字段均可修改
* 时间:2020年5月26日
*******************************************************************************/
func (p *GoldenPoint) UpdatePointById(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	//bases := new(C.GOLDEN_POINT)
	//scans := new(C.GOLDEN_SCAN_POINT)
	//calcs := new(C.GOLDEN_CALC_POINT)

	pscan := p.Scan
	pscan.Padding = p.PlatEx.SetToScanPadding()
	bases := goBasePoint2CBasePoint(p.Base)
	scans := goScanPoint2CScanPoint(pscan)
	calcs := goCalcPoint2CCalcPoint(p.Calc)

	ecode, _, _ := gob_update_point_property.Call(
		uintptr(handle),
		uintptr(unsafe.Pointer(bases)),
		uintptr(unsafe.Pointer(scans)),
		uintptr(unsafe.Pointer(calcs)),
	)

	return FormatErrMsg(ecode)
}

/*******************************************************************************
* 命名:gob_insert_point
* 功能:使用完整的属性集来创建单个标签点
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:需设置除 id, createdate, creator, changedate, changer 字段外的其它字段
	返回id字段
* 时间:2020年5月27日
*******************************************************************************/
func (p *GoldenPoint) InsertPoint(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	//bases := new(C.GOLDEN_POINT)
	//scans := new(C.GOLDEN_SCAN_POINT)
	//calcs := new(C.GOLDEN_CALC_POINT)

	pscan := p.Scan
	pscan.Padding = p.PlatEx.SetToScanPadding()
	bases := goBasePoint2CBasePoint(p.Base)
	scans := goScanPoint2CScanPoint(pscan)
	calcs := goCalcPoint2CCalcPoint(p.Calc)

	ecode, _, _ := gob_insert_point.Call(
		uintptr(handle),
		uintptr(unsafe.Pointer(bases)),
		uintptr(unsafe.Pointer(scans)),
		uintptr(unsafe.Pointer(calcs)),
	)
	p.Base.Id = int(bases.id)
	return FormatErrMsg(ecode)
}

/*******************************************************************************
* 命名:gob_remove_point_by_id
* 功能:根据 id 删除单个标签点(可回收)
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:需设置 id
* 时间:2020年5月27日
*******************************************************************************/
func (p *GoldenPoint) RemovePointById(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	ecode, _, _ := gob_remove_point_by_id.Call(
		uintptr(handle),
		uintptr(int32(p.Base.Id)),
	)

	return FormatErrMsg(ecode)
}

/*******************************************************************************
* 命名:gob_remove_table_by_id
* 功能:根据表 id 删除表及表中标签点;
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:删除的表不可恢复，删除的标签点可以通过 gob_recover_point 接口恢复。
* 时间:2020年5月27日
*******************************************************************************/
func (t *GoldenTable) RemoveTableById(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	ecode, _, _ := gob_remove_table_by_id.Call(
		uintptr(handle),
		uintptr(int32(t.Id)),
	)

	return FormatErrMsg(ecode)
}

/*******************************************************************************
* 命名:gob_remove_table_by_name
* 功能:根据表 名称 删除表及表中标签点;
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:删除的表不可恢复，删除的标签点可以通过 gob_recover_point 接口恢复。
* 时间:2020年5月27日
*******************************************************************************/
func (t *GoldenTable) RemoveTableByName(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	tbname := string2C80chars(t.Name)
	ecode, _, _ := gob_remove_table_by_name.Call(
		uintptr(handle),
		uintptr(unsafe.Pointer(&tbname)),
	)

	return FormatErrMsg(ecode)
}

/*******************************************************************************
* 命名:gob_update_table_name
* 功能:根据表 id 修改表名称;
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:
* 时间:2020年5月27日
*******************************************************************************/
func (t *GoldenTable) UpdateTableNameById(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	newname := string2C80chars(t.Name)
	ecode, _, _ := gob_update_table_name.Call(
		uintptr(handle),
		uintptr(int32(t.Id)),
		uintptr(unsafe.Pointer(&newname)),
	)

	return FormatErrMsg(ecode)
}

/*******************************************************************************
* 功能:根据表 名称(旧) 修改表名称(新);
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:
* 时间:2020年6月1日
*******************************************************************************/
func (t *GoldenTable) UpdateTableNameByOldName(handle int32, newname string) error {
	err := t.GetTablePropertyByName(handle)
	if err != nil {
		return err
	}
	t.Name = newname
	return t.UpdateTableNameById(handle)
}

/*******************************************************************************
* 命名:gob_update_table_desc_by_id
* 功能:根据表 id 修改表描述;
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:
* 时间:2020年5月27日
*******************************************************************************/
func (t *GoldenTable) UpdateTableDescById(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	desc := string2C100chars(t.Desc)
	ecode, _, _ := gob_update_table_desc_by_id.Call(
		uintptr(handle),
		uintptr(int32(t.Id)),
		uintptr(unsafe.Pointer(&desc)),
	)

	return FormatErrMsg(ecode)
}

/*******************************************************************************
* 命名:gob_update_table_desc_by_name
* 功能:根据表 名称 修改表描述;
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:
* 时间:2020年5月27日
*******************************************************************************/
func (t *GoldenTable) UpdateTableDescByName(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	name := string2C80chars(t.Name)
	desc := string2C100chars(t.Desc)
	ecode, _, _ := gob_update_table_desc_by_name.Call(
		uintptr(handle),
		uintptr(unsafe.Pointer(&name)),
		uintptr(unsafe.Pointer(&desc)),
	)

	return FormatErrMsg(ecode)
}

/*******************************************************************************
* 命名:gob_append_table
* 功能:根据表 名称 新建表;
* 参数:[handle]   数据库访问句柄
* 输出:[error] 错误信息
* 备注:需要输入表名称和描述,新建成功后，自动返回ID
* 时间:2020年5月27日
*******************************************************************************/
func (t *GoldenTable) AppendTable(handle int32) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	gdt := new(C.GOLDEN_TABLE)
	gdt.name = string2C80chars(t.Name)
	gdt.desc = string2C100chars(t.Desc)

	ecode, _, _ := gob_append_table.Call(
		uintptr(handle),
		uintptr(unsafe.Pointer(gdt)),
	)
	if ecode > 0 {
		return FormatErrMsg(ecode)
	} else {
		t.Id = int(gdt.id)
		return nil
	}
}

/*******************************************************************************
* 命名:GetFromScanPadding
* 功能:将标签点采集扩展属性中的padding属性中存储的内容解释到智云平台扩展属性
* 参数:[padding]   标签点采集扩展属性中的padding属性
* 输出:无
* 备注:解释的数据直接存储到结构体中
* 时间:2020年5月27日
*******************************************************************************/
func (p *PointMicPlatEx) GetFromScanPadding(padding []byte) {
	if len(padding) > 9 {
		pes := strings.Split(string(padding), ",")
		if len(pes) >= 5 {
			for i, pe := range pes {
				switch i {
				case 0:
					id, e := strconv.ParseInt(pe, 10, 64)
					if e == nil {
						p.Id = id
					}
				case 1:
					fv, e := strconv.ParseFloat(pe, 64)
					if e == nil {
						p.LLv = fv
					}
				case 2:
					fv, e := strconv.ParseFloat(pe, 64)
					if e == nil {
						p.Lv = fv
					}
				case 3:
					fv, e := strconv.ParseFloat(pe, 64)
					if e == nil {
						p.Hv = fv
					}
				case 4:
					fv, e := strconv.ParseFloat(pe, 64)
					if e == nil {
						p.HHv = fv
					}
				default:

				}
			}
		}
	}
}

/*******************************************************************************
* 命名:SetToScanPadding
* 功能:将智云平台扩展属性存储到标签点采集扩展属性中的padding属性中
* 参数:无
* 输出:[padding]   标签点采集扩展属性中的padding属性
* 备注:数据需要预先存储到结构体中
* 时间:2020年5月27日
*******************************************************************************/
func (p *PointMicPlatEx) SetToScanPadding() []byte {
	padding := fmt.Sprintf("%d,%f,%f,%f,%f", p.Id, p.LLv, p.Lv, p.Hv, p.HHv)
	return []byte(padding)
}

/*******************************************************************************
- 功能:C的GOLDEN_POINT转换为go BasePoint
- 输入:
	[GOLDEN_POINT] C的GOLDEN_POINT
- 输出:
	[GoldenBasePoint] go GoldenBasePoint结构体
- 时间:2020年5月14日
*******************************************************************************/
func cBasePoint2GoBasePoint(c C.GOLDEN_POINT) (g GoldenBasePoint) {
	g.Id = int(c.id)                                  //int     //全库唯一标识
	g.Tag = cChars2String(c.tag[:])                   //string  //用于在表中唯一标识一个标签点,最长79
	g.DataType = int(C.getPointType(c))               //int     //标签点的数值类型
	g.TableId = int(c.table)                          //int     //标签点所属表ID
	g.Desc = cChars2String(c.desc[:])                 //string  //有关标签点的描述性文字,最长99
	g.Unit = cChars2String(c.unit[:])                 //string  //工程单位,最长19
	g.IsArchive = cByte2Bool(c.archive)               //bool    //是否存档
	g.Digits = int(c.digits)                          //int     //数值位数,>=-20、<=10,默认-5;如果为0或正数，表示数值的小数位数，如果为负数，表示数值的有效位数
	g.IsShutDown = cByte2Bool(c.shutdown)             //int     //停机状态字,定义该点在停机状态下是否补写停机状态值.1 表示补写；0 表示不补写
	g.LowLimit = float64(c.lowlimit)                  //float64 //量程下限,缺省0
	g.HighLimit = float64(c.highlimit)                //float64 //量程上限,缺省100
	g.IsStep = cByte2Bool(c.step)                     //bool    //是否阶跃.
	g.Typical = float64(c.typical)                    //float64 //典型值
	g.IsCompress = cByte2Bool(c.compress)             //bool    //是否压缩,缺省true
	g.CompDev = float64(c.compdev)                    //float64 //压缩偏差,单位:标签工程单位,缺省:1
	g.CompDevPercent = float64(c.compdevpercent)      //float64 //压缩偏差百分比
	g.CompTimeMax = int(c.comptimemax)                //int     //最大压缩间隔,单位:秒,缺省值:28800
	g.CompTimeMin = int(c.comptimemin)                //int     //最短压缩间隔,单位:秒,缺省值:0
	g.ExcDev = float64(c.excdev)                      //float64 //例外偏差,单位:标签工程单位.缺省0.5
	g.ExcDevPercent = float64(c.excdevpercent)        //float64 //例外偏差百分比
	g.ExcTimeMax = int(c.exctimemax)                  //int     //最大例外间隔,单位:秒,缺省值600
	g.ExcTimeMin = int(c.exctimemin)                  //int     //最短例外间隔,单位:秒,缺省值0
	g.ClassOf = uint(c.classof)                       //uint    //标签点类别,基本点(0)、采集点(1)、计算点(2)、采集计算点(3) 、报警点(4)等
	g.changeDate = int(c.changedate)                  //int     //标签点属性最后一次被修改的时间
	g.changer = cChars2String(c.changer[:])           //string  //最后一次修改的用户名
	g.createDate = int(c.createdate)                  //int     //标签点被创建的时间
	g.creator = cChars2String(c.creator[:])           //string  //标签点创建者用户名
	g.Mirror = int(c.mirror)                          //int     //镜像收发控制:0:关闭;1:既接收,又发送;2:只接受,不发送;3:只发送,不接收
	g.MilliSecond = int(c.millisecond)                //int     //时间戳精度,默认值:0,秒;1:毫秒;创建后不可更改
	g.scanIndex = uint(c.scanindex)                   //uint    //采集点扩展属性集索引
	g.calcIndex = uint(c.calcindex)                   //uint    //计算点扩展属性集索引
	g.alarmIndex = uint(c.alarmindex)                 //uint    //报警点扩展属性集索引
	g.TableDotTag = cChars2String(c.table_dot_tag[:]) //string  //标签点全名
	g.IsSummary = cByte2Bool(c.summary)               //bool    //统计加速开关,默认0;用于设定是否生成标签点统计信息，从而加速历史数据统计过程
	g.NamedTypeId = uint(c.named_type_id)
	g.Padding = cUchar2bytes(c.padding[:])
	return g
}

/*******************************************************************************
- 功能:go的BasePoint转换为c GOLDEN_POINT
- 输入:
	[BasePoint] go的BasePoint
- 输出:
	[GOLDEN_POINT] c GOLDEN_POINT结构体
- 时间:2020年5月26日
*******************************************************************************/
func goBasePoint2CBasePoint(g GoldenBasePoint) *C.GOLDEN_POINT {
	c := new(C.GOLDEN_POINT)
	*c = C.setPointType(*c, C.int(g.DataType))        //int     //标签点的数值类型
	c.id = C.int(g.Id)                                //int     //全库唯一标识
	c.tag = string2C80chars(g.Tag)                    //string  //用于在表中唯一标识一个标签点,最长79
	c.table = C.int(g.TableId)                        //int     //标签点所属表ID
	c.desc = string2C100chars(g.Desc)                 //string  //有关标签点的描述性文字,最长99
	c.unit = string2C20chars(g.Unit)                  //string  //工程单位,最长19
	c.archive = bool2Cbyte(g.IsArchive)               //bool    //是否存档
	c.digits = C.short(g.Digits)                      //int     //数值位数,>=-20、<=10,默认-5;如果为0或正数，表示数值的小数位数，如果为负数，表示数值的有效位数
	c.shutdown = bool2Cbyte(g.IsShutDown)             //bool     //停机状态字,定义该点在停机状态下是否补写停机状态值.1 表示补写；0 表示不补写
	c.lowlimit = C.float(g.LowLimit)                  //float64 //量程下限,缺省0
	c.highlimit = C.float(g.HighLimit)                //float64 //量程上限,缺省100
	c.step = bool2Cbyte(g.IsStep)                     //bool    //是否阶跃.
	c.typical = C.float(g.Typical)                    //float64 //典型值
	c.compress = bool2Cbyte(g.IsCompress)             //bool    //是否压缩,缺省true
	c.compdev = C.float(g.CompDev)                    //float64 //压缩偏差,单位:标签工程单位,缺省:1
	c.compdevpercent = C.float(g.CompDevPercent)      //float64 //压缩偏差百分比
	c.comptimemax = C.int(g.CompTimeMax)              //int     //最大压缩间隔,单位:秒,缺省值:28800
	c.comptimemin = C.int(g.CompTimeMin)              //int     //最短压缩间隔,单位:秒,缺省值:0
	c.excdev = C.float(g.ExcDev)                      //float64 //例外偏差,单位:标签工程单位.缺省0.5
	c.excdevpercent = C.float(g.ExcDevPercent)        //float64 //例外偏差百分比
	c.exctimemax = C.int(g.ExcTimeMax)                //int     //最大例外间隔,单位:秒,缺省值600
	c.exctimemin = C.int(g.ExcTimeMin)                //int     //最短例外间隔,单位:秒,缺省值0
	c.classof = C.uint(g.ClassOf)                     //uint    //标签点类别,基本点(0)、采集点(1)、计算点(2)、采集计算点(3) 、报警点(4)等
	c.changedate = C.int(g.changeDate)                //int     //标签点属性最后一次被修改的时间
	c.changer = string2C20chars(g.changer)            //string  //最后一次修改的用户名
	c.createdate = C.int(g.createDate)                //int     //标签点被创建的时间
	c.creator = string2C20chars(g.creator)            //string  //标签点创建者用户名
	c.mirror = C.uchar(g.Mirror)                      //int     //镜像收发控制:0:关闭;1:既接收,又发送;2:只接受,不发送;3:只发送,不接收
	c.millisecond = C.uchar(g.MilliSecond)            //int     //时间戳精度,默认值:0,秒;1:毫秒;创建后不可更改
	c.scanindex = C.uint(g.scanIndex)                 //uint    //采集点扩展属性集索引
	c.calcindex = C.uint(g.calcIndex)                 //uint    //计算点扩展属性集索引
	c.alarmindex = C.uint(g.alarmIndex)               //uint    //报警点扩展属性集索引
	c.table_dot_tag = string2C160chars(g.TableDotTag) //string  //标签点全名
	c.summary = bool2Cbyte(g.IsSummary)               //bool    //统计加速开关,默认0;用于设定是否生成标签点统计信息，从而加速历史数据统计过程
	c.named_type_id = C.ushort(g.NamedTypeId)
	c.padding = bytes2C5uchar(g.Padding)
	return c
}

/*******************************************************************************
- 功能:C的GOLDEN_SCAN_POINT转换为go GoldenScanPoint
- 输入:
	[GOLDEN_SCAN_POINT] C的GOLDEN_SCAN_POINT
- 输出:
	[GoldenScanPoint] go GoldenScanPoint结构体
- 时间:2020年5月15日
*******************************************************************************/
func cScanPoint2GoScanPoint(c C.GOLDEN_SCAN_POINT) (g GoldenScanPoint) {
	g.Id = int(c.id)                              //int        //
	g.Source = cChars2String(c.source[:])         //string     //数据源,缺省为空
	g.IsScan = cByte2Bool(c.scan)                 //bool       //是否采集
	g.Instrument = cChars2String(c.instrument[:]) //string     //设备标签
	for i, cloc := range c.locations {
		g.Locations[i] = int(cloc) //[5]int     //设备位置
	}
	for i, cuint := range c.userints {
		g.UserInts[i] = int(cuint) //[5]int     //自定义整数
	}
	for i, cur := range c.userreals {
		g.UserReals[i] = float64(cur) //[2]float64 //自定义浮点数
	}
	g.Padding = cUchar2bytes(c.padding[:])
	return g
}

/*******************************************************************************
- 功能:go GoldenScanPoint 转换为 C的GOLDEN_SCAN_POINT
- 输入:
	[GoldenScanPoint] go GoldenScanPoint结构体
- 输出:
	[GOLDEN_SCAN_POINT] C的GOLDEN_SCAN_POINT
- 时间:2020年5月26日
*******************************************************************************/
func goScanPoint2CScanPoint(g GoldenScanPoint) *C.GOLDEN_SCAN_POINT {
	c := new(C.GOLDEN_SCAN_POINT)
	c.id = C.int(g.Id)                           //int        //
	c.source = string2C256chars(g.Source)        //string     //数据源,缺省为空
	c.scan = bool2Cbyte(g.IsScan)                //bool       //是否采集
	c.instrument = string2C50chars(g.Instrument) //string     //设备标签
	for i, cloc := range g.Locations {
		c.locations[i] = C.int(cloc) //[5]int     //设备位置
	}
	for i, cuint := range g.UserInts {
		c.userints[i] = C.int(cuint) //[5]int     //自定义整数
	}
	for i, cur := range g.UserReals {
		c.userreals[i] = C.float(cur) //[2]float64 //自定义浮点数
	}
	c.padding = bytes2C164uchar(g.Padding)
	return c
}

/*******************************************************************************
- 功能:C的GOLDEN_CALC_POINT转换为go GoldenCalcPoint
- 输入:
	[GOLDEN_CALC_POINT] C的GOLDEN_CALC_POINT
- 输出:
	[GoldenCalcPoint] go GoldenCalcPoint结构体
- 时间:2020年5月15日
*******************************************************************************/
func cCalcPoint2GoCalcPoint(c C.GOLDEN_CALC_POINT) (g GoldenCalcPoint) {
	g.Id = int(c.id)                          //int        //
	g.Equation = cChars2String(c.equation[:]) //string //试试方程式，长度不超过2047字节
	g.Trigger = int(c.trigger)                //int    //计算触发机制
	g.TimeCopy = int(c.timecopy)              //int    //计算结果时间戳:0: 表示采用计算时间作为计算结果时间戳； 1: 表示采用输入标签点中的最晚时间作为计算结果时间戳；2: 表示采用输入标签点中的最早时间作为计算结果时间戳。
	g.Period = int(c.period)                  //int    //计算周期,对周期触发的计算点有效,单位:秒
	return g
}

/*******************************************************************************
- 功能:go GoldenCalcPoint 转换为 C的GOLDEN_CALC_POINT
- 输入:
	[GoldenCalcPoint] go GoldenCalcPoint结构体
- 输出:
	[GOLDEN_CALC_POINT] C的GOLDEN_CALC_POINT
- 时间:2020年5月26日
*******************************************************************************/
func goCalcPoint2CCalcPoint(g GoldenCalcPoint) *C.GOLDEN_CALC_POINT {
	c := new(C.GOLDEN_CALC_POINT)
	c.id = C.int(g.Id)                         //int        //
	c.equation = string2C2036chars(g.Equation) //string //试试方程式，长度不超过2047字节
	c.trigger = C.uchar(g.Trigger)             //int    //计算触发机制
	c.timecopy = C.uchar(g.TimeCopy)           //int    //计算结果时间戳:0: 表示采用计算时间作为计算结果时间戳； 1: 表示采用输入标签点中的最晚时间作为计算结果时间戳；2: 表示采用输入标签点中的最早时间作为计算结果时间戳。
	c.period = C.int(g.Period)                 //int    //计算周期,对周期触发的计算点有效,单位:秒
	return c
}

/*******************************************************************************
* 命名:gob_append_point
* 功能:批量增加标签点
* 参数:无
* 输出:[padding]   标签点采集扩展属性中的padding属性
* 备注:数据需要预先存储到结构体中
【【【未测试成功】】】
* 时间:2020年5月27日
*******************************************************************************/
func (p *GoldenPoint) appendPointWithJson(handle int32, pointjson string) error {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	json_str, _ := syscall.BytePtrFromString(pointjson)
	json_str_size := len(pointjson)
	var id int32
	ecode, _, _ := gob_append_point.Call(
		uintptr(handle),
		uintptr(unsafe.Pointer(&json_str)),
		uintptr(unsafe.Pointer(&json_str_size)),
		uintptr(unsafe.Pointer(&id)),
	)
	if ecode > 0 { //如果添加不成功
		return FormatErrMsg(ecode) //返回错误信息
	} else { //添加成功
		p.Base.Id = int(id)
		return p.GetPointProptertyById(handle) //读取添加后的标签点
	}
}

/*******************************************************************************
* 命名:gob_remove_points
* 功能:批量删除标签点
* 输入:需要删除的标签点ids
* 输出:
    [int]  删除成功的标签点数量
    [map[int]error] 各个ID再删除时的错误信息
    [error] 总体的错误信息(所有标签点都无效的时候会有总体错误信息)
* 备注:
*******************************************************************************/
func (s *RTDBService) RemovePointsById(ids ...int) (int, map[int]error, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("%#v", err)
		}
	}()
	errmaps := make(map[int]error)
	var theids []int32
	for _, id := range ids {
		if id > 0 {
			theids = append(theids, int32(id))
		} else {
			errmaps[id] = fmt.Errorf("无效的标签点ID值:%d", id)
		}
	}
	count := int32(len(theids))
	if count > 0 {
		ecodes := make([]int32, count)
		code, _, _ := gob_remove_points.Call(
			uintptr(s.Handle),
			uintptr(0),
			uintptr(unsafe.Pointer(&theids[0])),
			uintptr(unsafe.Pointer(&count)),
			uintptr(unsafe.Pointer(&ecodes[0])),
		)
		count = 0
		for i, id := range theids {
			if ecodes[i] == 0 {
				count++
			}
			errmaps[int(id)] = FormatErrMsg(uintptr(ecodes[i]))
		}
		return int(count), errmaps, FormatErrMsg(code)
	} else {
		return 0, errmaps, fmt.Errorf("没有有效的标签点Id")
	}
}
