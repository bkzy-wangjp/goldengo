package goldengo

import (
	"fmt"
	"math"
	"strings"
	"time"

	"github.com/astaxie/beego/logs"
)

//时间序列数据
type RealTimeSeriesData struct {
	Time    int64   //时间,表示距离1970年1月1日08:00:00的毫秒数
	Value   float64 //数值
	Quality int     //质量码(GOOD = 0,NODATA = 1,CREATED = 2,SHUTDOWN = 3,CALCOFF = 4,BAD = 5,DIVBYZERO = 6,REMOVED = 7,OPC = 256,USER = 512)
}

//快照数据
type SnapData struct { //快照基础数据结构
	Id   int                //标签点id
	Rtsd RealTimeSeriesData //时序数据
	Err  string             //错误描述,无错误时为空
}

//历史数据结构
type HisData struct {
	HisRtsd  []RealTimeSeriesData //历史时序数据
	Err      error                //错误信息
	Continue bool                 //快照数据比历史数据的结束点更新
}

/*******************************************************************************
- 功能:创建庚顿实时数据库对象
- 参数:
	[hostname]  字符串，输入，GOLDEN 数据平台服务器的网络地址或机器名
	[user]		用户名,字符串,缺省值 sa
	[password]	密码,字符串,缺省值 golden
	[port]      端口号,整型,缺省值 6327
- 输出:
	[*Golden] 实时数据库对象
- 备注:在调用所有的接口函数之前，必须先调用本函数建立Golden对象。
*******************************************************************************/
func CreateGolden(hostname, username, password string, port ...int) *GoldenConnect {
	rtdb := new(GoldenConnect)
	rtdb.HostName = hostname
	rtdb.UserName = username
	rtdb.Password = password
	rtdb.Port = 6327
	if len(port) > 0 {
		rtdb.Port = port[0]
	}
	return rtdb
}

// func (g *Golden) RunFindPoints(tagfullnames ...string) ([]int, []int, []int, []int, error) {
// 	st := time.Now()
// 	type points struct {
// 		Ids   []int
// 		Types []int
// 		Class []int
// 		Isms  []int
// 		Err   error
// 	}
// 	findpoint := func(p chan points, tags ...string) {
// 		ids, types, classofs, ismss, err := g.FindPoints(tags...)
// 		var pt points
// 		pt.Ids = ids
// 		pt.Types = types
// 		pt.Class = classofs
// 		pt.Isms = ismss
// 		pt.Err = err
// 		p <- pt
// 	}
// 	pts := make(chan points)
// 	defer close(pts)
// 	go func(p chan points, tags ...string) {
// 		pt := make(chan points)
// 		defer close(pt)
// 		go findpoint(pt, tags...)
// 		select {
// 		case re := <-pt:
// 			p <- re
// 		case <-time.After(10 * time.Second):
// 			var re points
// 			re.Err = fmt.Errorf("FindPoints(%v) timeout", tags)
// 			p <- re
// 		}
// 	}(pts, tagfullnames...)
// 	pt := <-pts
// 	fmt.Printf("耗时:%f秒,%+v\n", time.Since(st).Seconds(), pt) //==========================================================
// 	return pt.Ids, pt.Types, pt.Class, pt.Isms, pt.Err
// }

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
func (g *GoldenConnect) GetSnapShotByName(tagfullnames ...string) (map[string]SnapData, error) {
	snaps := make(map[string]SnapData)
	idtagmap := make(map[int]string) //以id为key,以变量名为value的map
	if len(tagfullnames) > 0 {
		ids, dtypes, _, _, err := g.FindPoints(tagfullnames...) //根据变量名读取基本信息
		if err != nil {
			return snaps, err
		}
		var okids []int          //有效的ID变量数组
		for i, id := range ids { //校验ID,不能为0
			var snp SnapData
			if id == 0 {
				snp.Err = fmt.Sprintf("没有在数据库中找到匹配变量名[%s]的变量", tagfullnames[i])
				snaps[tagfullnames[i]] = snp
				//ids = append(ids[:i], ids[i+1:]...) //删除ID为0的元素
				//return snaps, fmt.Errorf("没有在数据库中找到匹配变量名[%s]的变量", tagfullnames[i])
			} else {
				okids = append(okids, id)
				idtagmap[id] = tagfullnames[i]
			}
		}
		if len(okids) > 0 { //有有效的ID
			dtime, dreal, dint, dq, de, err := g.GetSnapshots(okids) //根据Id读取快照
			if err != nil {
				return snaps, err
			}

			for i, id := range okids { //遍历有效的ID
				var snap SnapData
				var rtsd RealTimeSeriesData
				snap.Id = id
				if de[i] != nil {
					snap.Err = de[i].Error()
				}
				rtsd.Time = dtime[i]
				rtsd.Quality = dq[i]

				switch dtypes[i] {
				case 0, 1, 2, 3, 4, 5, 6, 7, 8: //整形等
					rtsd.Value = float64(dint[i])
				case 9, 10, 11: //浮点数
					rtsd.Value = dreal[i]
				default: //其他类型
					rtsd.Value = 0.0
				}
				snap.Rtsd = rtsd
				snaps[idtagmap[id]] = snap
			}
		}
	} else {
		return snaps, fmt.Errorf("没有设置要查询的变量名")
	}
	return snaps, nil
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
func (g *GoldenConnect) GetSnapShotById(ids, dtypes []int) (map[int]SnapData, error) {
	snaps := make(map[int]SnapData)
	if len(ids) != len(dtypes) {
		return snaps, fmt.Errorf("设置的Id数量和变量类型数量不匹配")
	}
	if len(ids) > 0 {
		var okids []int          //有效的ID变量数组
		for i, id := range ids { //校验ID,不能为0
			var snp SnapData
			if id == 0 {
				snaps[ids[i]] = snp
			} else {
				okids = append(okids, id)
			}
		}
		if len(okids) > 0 { //有有效的ID
			dtime, dreal, dint, dq, de, err := g.GetSnapshots(okids) //根据Id读取快照
			if err != nil {
				return snaps, err
			}

			for i, id := range okids { //遍历有效的ID
				var snap SnapData
				var rtsd RealTimeSeriesData
				snap.Id = id
				if de[i] != nil {
					snap.Err = de[i].Error()
				}
				rtsd.Time = dtime[i]
				rtsd.Quality = dq[i]

				switch dtypes[i] {
				case 0, 1, 2, 3, 4, 5, 6, 7, 8: //整形等
					rtsd.Value = float64(dint[i])
				case 9, 10, 11: //浮点数
					rtsd.Value = dreal[i]
				default: //其他类型
					rtsd.Value = 0.0
				}
				snap.Rtsd = rtsd
				snaps[id] = snap
			}
		}
	} else {
		return snaps, fmt.Errorf("没有设置要查询的变量ID")
	}
	return snaps, nil
}

/*******************************************************************************
- 功能: 通过变量全名获取历史数据值
- 参数:
	[bgtime]   整型，输入，表示起始时间UnixNano秒数。如果为 0，表示从存档中最早时间的数据开始读取
    [endtime]  整型，输入，表示结束时间UnixNano秒数。如果为 0，表示读取直至存档中数据的最后时间
	[tagfullnames]  字符串切片，输入. 变量全名格式:tablename.tagname
- 输出:
	[map[string][]RealTimeSeriesData] 快照Map,key为变量全名
	[error] 错误信息
- 备注:
- 时间: 2020年5月15日
*******************************************************************************/
func (g *GoldenConnect) GetHistoryByName(bgtime, endtime int64, tagfullnames ...string) (map[string][]RealTimeSeriesData, error) {
	datas := make(map[string][]RealTimeSeriesData)
	ids, dtypes, _, _, err := g.FindPoints(tagfullnames...) //根据变量名读取基本信息
	if err != nil {
		return datas, err
	}
	for i, id := range ids { //校验ID,不能为0
		if id == 0 {
			return datas, fmt.Errorf("没有在数据库中找到匹配变量名[%s]的变量", tagfullnames[i])
		}
	}
	for j, tag := range tagfullnames { //逐个变量读取历史值
		var rtsds []RealTimeSeriesData
		dtime, dreal, dint, dq, err := g.GetArchivedValues(ids[j], bgtime, endtime) //根据Id读取历史数据
		if err == nil {                                                             //
			for i, dt := range dtime {
				var rtsd RealTimeSeriesData
				rtsd.Time = dt
				rtsd.Quality = int(dq[i])
				switch dtypes[j] {
				case 0, 1, 2, 3, 4, 5, 6, 7, 8: //整形等
					rtsd.Value = float64(dint[i])
				case 9, 10, 11: //浮点数
					rtsd.Value = dreal[i]
				default: //其他类型
					rtsd.Value = 0.0
				}
				rtsds = append(rtsds, rtsd)
			}
		}
		datas[tag] = rtsds
	}
	return datas, nil
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
func (g *GoldenConnect) GetHistorySummaryByName(bgtime, endtime int64, tagfullname string) (int64,
	int64, float64, float64, float64, float64, float64, int, error) {
	ids, _, _, _, err := g.FindPoints(tagfullname) //根据变量名读取基本信息
	if err != nil {
		return 0, 0, 0., 0., 0., 0., 0., 0, err
	}
	tagid := 0
	for _, id := range ids { //校验ID,不能为0
		if id == 0 {
			return 0, 0, 0., 0., 0., 0., 0., 0, fmt.Errorf("variable name [%s] does not exist.[没有在数据库中找到匹配变量名[%s]的变量]",
				tagfullname, tagfullname)
		}
		tagid = id
	}
	if tagid > 0 {
		return g.SummaryEx(tagid, bgtime, endtime)
	} else {
		return 0, 0, 0., 0., 0., 0., 0., 0, fmt.Errorf("variable name [%s] does not exist.[没有在数据库中找到匹配变量名[%s]的变量]",
			tagfullname, tagfullname)
	}
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
func (g *GoldenConnect) GetHistorySingleByName(mode int, datatime int64, tagfullnames ...string) (map[string]RealTimeSeriesData, error) {
	datas := make(map[string]RealTimeSeriesData)
	ids, dtypes, _, _, err := g.FindPoints(tagfullnames...) //根据变量名读取基本信息
	if err != nil {
		return datas, err
	}
	for i, id := range ids { //校验ID,不能为0
		if id == 0 {
			return datas, fmt.Errorf("没有在数据库中找到匹配变量名[%s]的变量", tagfullnames[i])
		}
	}
	for j, tag := range tagfullnames { //逐个变量读取历史值
		dtime, dreal, dint, dq, err := g.GetSingleValue(ids[j], mode, datatime) //根据Id读取历史数据
		var rtsd RealTimeSeriesData
		if err == nil { //
			rtsd.Time = dtime
			rtsd.Quality = int(dq)
			switch dtypes[j] {
			case 0, 1, 2, 3, 4, 5, 6, 7, 8: //整形等
				rtsd.Value = float64(dint)
			case 9, 10, 11: //浮点数
				rtsd.Value = dreal
			default: //其他类型
				rtsd.Value = 0.0
			}
		}
		datas[tag] = rtsd
	}
	return datas, nil
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
func (g *GoldenConnect) GetHisIntervalByName(count int, bgtime, endtime int64, tagfullnames ...string) (map[string][]RealTimeSeriesData, error) {
	datas := make(map[string][]RealTimeSeriesData)
	ids, dtypes, _, _, err := g.FindPoints(tagfullnames...) //根据变量名读取基本信息
	if err != nil {
		return datas, err
	}
	for i, id := range ids { //校验ID,不能为0
		if id == 0 {
			return datas, fmt.Errorf("没有在数据库中找到匹配变量名[%s]的变量", tagfullnames[i])
		}
	}
	for j, tag := range tagfullnames { //逐个变量读取历史值
		var rtsds []RealTimeSeriesData
		dtime, dreal, dint, dq, err := g.GetInterpoValues(ids[j], count, bgtime, endtime) //根据Id读取历史数据
		if err == nil {                                                                   //
			for i, dt := range dtime {
				var rtsd RealTimeSeriesData
				rtsd.Time = dt
				rtsd.Quality = int(dq[i])
				switch dtypes[j] {
				case 0, 1, 2, 3, 4, 5, 6, 7, 8: //整形等
					rtsd.Value = float64(dint[i])
				case 9, 10, 11: //浮点数
					rtsd.Value = dreal[i]
				default: //其他类型
					rtsd.Value = 0.0
				}
				rtsds = append(rtsds, rtsd)
			}
		}
		datas[tag] = rtsds
	}
	return datas, nil
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
func (g *GoldenConnect) GetHistoryDataAlignHeadAndTail(bginTime, endTime int64, Interval int, tagnames ...string) (map[string]HisData, error) {
	defer func() {
		if err := recover(); err != nil {
			logs.Critical("Golden.GetHistoryDataAlignHeadAndTail 中捕获的错误信息:%#v", err)
		}
	}()
	datas := make(map[string][]RealTimeSeriesData)
	errs := make(map[string]error, len(tagnames))
	newdata_afterEnd := make(map[string]bool)
	hismap := make(map[string]HisData)
	if len(tagnames) == 0 {
		return hismap, fmt.Errorf("没有设置有效的变量")
	}
	ids, dtypes, _, _, err := g.FindPoints(tagnames...) //根据变量名读取基本信息
	if err != nil {
		return hismap, fmt.Errorf("通过变量全名[%s]获取变量在实时数据库中的ID失败:[%s]", tagnames, err.Error())
	}
	for i, id := range ids { //校验ID,不能为0
		if id == 0 {
			return hismap, fmt.Errorf("没有在数据库中找到匹配变量名[%s]的变量", tagnames[i])
		}
	}
	snaptimes, _, _, _, _, err := g.GetSnapshots(ids) //根据Id读取快照
	if err != nil {
		return hismap, fmt.Errorf("读取变量[%s]快照值失败:[%s]", tagnames, err.Error())
	}
	for i, tag := range tagnames {
		newdata_afterEnd[tag] = snaptimes[i] > endTime/1e6
		var hisdata []RealTimeSeriesData
		var histime, hisint []int64
		var hisreal []float64
		var hisq []int16
		if Interval <= 0 {
			histime, hisreal, hisint, hisq, err = g.GetArchivedValues(ids[i], bginTime, endTime) //根据Id读取历史数据
			if err != nil {
				errs[tag] = fmt.Errorf("读取变量[%s]从[%s]到[%s]的历史存档数据时错误:[%s]", tag, time.Unix(bginTime/1e9, bginTime%1e9), time.Unix(endTime/1e9, endTime%1e9), err.Error())
			}
		} else {
			count := (endTime-bginTime)/int64(Interval)/1e9 + 1
			histime, hisreal, hisint, hisq, err = g.GetInterpoValues(ids[i], int(count), bginTime, endTime) //根据Id读取历史数据
			if err != nil {
				errs[tag] = fmt.Errorf("读取变量[%s]从[%s]到[%s]的等间隔插值历史存档数据时错误:[%s]", tag, time.Unix(bginTime/1e9, bginTime%1e9), time.Unix(endTime/1e9, endTime%1e9), err.Error())
			}
		}
		//fmt.Printf("直接查询的结果:%v,%v ----------------------\n", histime, hisreal)
		var bghd RealTimeSeriesData                                                //开始时间点之前的一个历史数据
		bgtime, bgreal, bgint, bgq, bgerr := g.GetSingleValue(ids[i], 1, bginTime) //根据Id读取历史时刻单值数据
		if bgerr != nil {
			bgerr = fmt.Errorf("no data was found.读取变量[%s]的时间点[%s]数据失败:[%s]", tag, time.Unix(bginTime/1e9, bginTime%1e9/1e6), bgerr.Error())
		} else {
			if bgtime == 0 {
				bgerr = fmt.Errorf("no data was found.变量[%s]在时间点[%s](含)之前没有数据", tag, time.Unix(bginTime/1e9, bginTime%1e9/1e6))
			}
		}
		if len(histime) > 0 { //读到了历史数据
			//Interval小于0时不补齐开头和结尾
			if Interval >= 0 && histime[0] > bginTime/1e6 { //第一个历史数据时间大于开始时间
				bghd = formatRealTimeSeriesData(dtypes[i], bginTime/1e6, bgreal, bgint, bgq)
				hisdata = append(hisdata, bghd)
			}
			var hd RealTimeSeriesData
			for j, ht := range histime {
				hd = formatRealTimeSeriesData(dtypes[i], ht, hisreal[j], hisint[j], hisq[j])
				hisdata = append(hisdata, hd)
			}

			if Interval >= 0 && hd.Time < endTime/1e6 { //如果读取到的历史数据中的最后一个点的时间小于指定的结束时间
				hd.Time = endTime / 1e6
				hisdata = append(hisdata, hd)
			}
		} else { //没有读到历史数据
			if bgerr != nil {
				errs[tag] = fmt.Errorf("%s;No data was found.变量[%s]没有读取到从[%s]到[%s]的历史数据,最后的快照数据时间是[%s]",
					bgerr.Error(), tag, time.Unix(bginTime/1e9, bginTime%1e9),
					time.Unix(endTime/1e9, endTime%1e9),
					time.Unix(snaptimes[i]/1e3, snaptimes[i]%1e3*1e6))
			} else {
				errs[tag] = fmt.Errorf("no data was found.变量[%s]没有读取到从[%s]到[%s]的历史数据,最后的快照数据时间是[%s]",
					tag, time.Unix(bginTime/1e9, bginTime%1e9),
					time.Unix(endTime/1e9, endTime%1e9),
					time.Unix(snaptimes[i]/1e3, snaptimes[i]%1e3*1e6))
				if Interval >= 0 {
					bghd = formatRealTimeSeriesData(dtypes[i], bginTime/1e6, bgreal, bgint, bgq)
					hisdata = append(hisdata, bghd)
					bghd.Time = endTime / 1e6
					hisdata = append(hisdata, bghd)
				}
			}
		}
		datas[tag] = hisdata
	}
	for tg, his := range datas {
		var hd HisData
		hd.Continue = newdata_afterEnd[tg]
		hd.Err = errs[tg]
		hd.HisRtsd = his
		hismap[tg] = hd
	}
	//fmt.Printf("查询结果:%v,interval=%d ====================\n", hismap, Interval)
	return hismap, nil
}

func formatRealTimeSeriesData(dtype int, datatime int64, realval float64, intval int64, quality int16) RealTimeSeriesData {
	var hisdata RealTimeSeriesData //时间序列数据
	hisdata.Quality = int(quality)
	hisdata.Time = datatime
	switch dtype {
	case 0, 1, 2, 3, 4, 5, 6, 7, 8: //整形等
		hisdata.Value = float64(intval)
	case 9, 10, 11: //浮点数
		hisdata.Value = realval
	default: //其他类型
		hisdata.Value = 0.0
	}
	return hisdata
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
func (g *GoldenConnect) GetTagNameListInTables(tbnames ...string) (map[string][]string, error) {
	tagsmap := make(map[string][]string)
	err := g.GetTables()
	if err != nil {
		return tagsmap, err
	}
	if len(tbnames) > 0 { //存在表名列表
		for _, name := range tbnames { //遍历表名列表
			var tb GoldenTable
			var tags []string
			ids, err := tb.GetPointIds(g.Handle, name) //读取标签点ID
			if err == nil {
				if len(ids) > 0 {
					err := g.GetPointPropterty(ids...) //获取标签点属性
					if err == nil {
						for _, id := range ids {
							tags = append(tags, g.Points[id].Base.TableDotTag)
						}
					}
				}
			}
			tagsmap[name] = tags
		}
	} else {
		err = g.GetTables(true) //获取全部表及表下的tags
		if err != nil {
			return tagsmap, err
		}
		for _, tb := range g.Tables { //遍历每张表
			var tags []string
			for _, id := range tb.PointIds { //遍历每张表下的标签点
				tags = append(tags, g.Points[id].Base.TableDotTag)
			}
			tagsmap[tb.Name] = tags
		}
	}
	return tagsmap, nil
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
func (g *GoldenConnect) GetTagListInTables(tbnames ...string) (map[string][]GoldenPoint, error) {
	tagsmap := make(map[string][]GoldenPoint)
	err := g.GetTables()
	if err != nil {
		return tagsmap, err
	}
	if len(tbnames) > 0 { //存在表名列表
		for _, name := range tbnames { //遍历表名列表
			var tb GoldenTable
			var tags []GoldenPoint
			ids, err := tb.GetPointIds(g.Handle, name) //读取标签点ID
			if err == nil {
				if len(ids) > 0 {
					err := g.GetPointPropterty(ids...) //获取标签点属性
					if err == nil {
						for _, id := range ids {
							tags = append(tags, g.Points[id])
						}
					}
				}
			}
			tagsmap[name] = tags
		}
	} else {
		err = g.GetTables(true) //获取全部表及表下的tags
		if err != nil {
			return tagsmap, err
		}
		for _, tb := range g.Tables { //遍历每张表
			var tags []GoldenPoint
			for _, id := range tb.PointIds { //遍历每张表下的标签点
				tags = append(tags, g.Points[id])
			}
			tagsmap[tb.Name] = tags
		}
	}
	return tagsmap, nil
}

/*******************************************************************************
功能:根据标签点全名获取标签点的配置信息
输入:标签点名列表
输出:标签点Map,Map的key为标签名
说明:
时间:2020年5月16日
编辑:wang_jp
*******************************************************************************/
func (g *GoldenConnect) GetTagPointInfoByName(tagnames ...string) (map[string]GoldenPoint, error) {
	datas := make(map[string]GoldenPoint)
	var nullstring string
	var pids []int
	tagidmap := make(map[int]string)
	for _, fullname := range tagnames { //遍历变量名
		names := strings.Split(fullname, ".") //拆分为表名和tag名
		if len(names) == 2 {                  //拆分出来的结果长度符合要求
			//搜索标签点
			ids, err := g.Search(names[1], names[0], nullstring, nullstring, nullstring, nullstring, 2)
			if err == nil && len(ids) > 0 { //搜索到了结果
				pids = append(pids, ids[0])
				tagidmap[ids[0]] = fullname
			} else { //没有搜索到结果
				return datas, fmt.Errorf("变量名[%s]在实时数据库中不存在", fullname)
			}
		} else { //拆分不成功
			return datas, fmt.Errorf("变量名[%s]格式不正确,应该是[ tablename.tagname ]的形式", fullname)
		}
	}
	err := g.GetPointPropterty(pids...) //读取变量属性信息
	if err != nil {
		return datas, err
	}
	for id, name := range tagidmap {
		datas[name] = g.Points[id]
	}
	return datas, nil
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
func (g *GoldenConnect) SetSnapShot(tagname string, datavalue float64, qualitie int, datatime ...int64) error {
	timestemp := time.Now().UnixNano()
	if len(datatime) > 0 {
		timestemp = datatime[0]
	}
	var dt []int64
	var df []float64
	var dv []int64
	var dq []int16

	ids, dtypes, _, _, err := g.FindPoints(tagname) //根据变量名读取基本信息
	if err != nil || len(ids) == 0 {
		return fmt.Errorf("通过变量全名[%s]获取变量在实时数据库中的ID失败:[%s]", tagname, err.Error())
	}
	if ids[0] == 0 {
		return fmt.Errorf("变量名[%s]在实时数据库中不存在", tagname)
	}
	dt = append(dt, timestemp)
	dq = append(dq, int16(qualitie))
	if dtypes[0] < 9 {
		dv = append(dv, int64(math.Ceil(datavalue)))
		df = append(df, 0)
	} else {
		dv = append(dv, 0)
		df = append(df, datavalue)
	}
	_, err = g.PutSnapshots(ids, dt, df, dv, dq)

	return err
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
func (g *GoldenConnect) SetSnapShotBatch(tagnames []string, datavalues []float64, qualities []int, datatimes []int64) error {
	var df []float64
	var dv []int64
	var dq []int16
	cnt := len(tagnames)
	if cnt != len(datavalues) || cnt != len(qualities) || cnt != len(datatimes) {
		return fmt.Errorf("输入参数数组的长度不一致")
	}
	ids, dtypes, _, _, err := g.FindPoints(tagnames...) //根据变量名读取基本信息
	if err != nil || len(ids) == 0 {
		return fmt.Errorf("通过变量全名[%s]获取变量在实时数据库中的ID失败:[%s]", tagnames, err.Error())
	}
	for i, tag := range tagnames {
		if ids[i] == 0 {
			return fmt.Errorf("变量名[%s]在实时数据库中不存在", tag)
		}
		dq = append(dq, int16(qualities[i]))
		if dtypes[i] < 9 {
			dv = append(dv, int64(math.Ceil(datavalues[i])))
			df = append(df, 0)
		} else {
			dv = append(dv, 0)
			df = append(df, datavalues[i])
		}
	}

	_, err = g.PutSnapshots(ids, datatimes, df, dv, dq)

	return err
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
func (g *GoldenConnect) SetArchivedValue(tagname string, datavalue float64, qualitie int, datatime ...int64) error {
	timestemp := time.Now().UnixNano()
	if len(datatime) > 0 {
		timestemp = datatime[0]
	}
	var dt []int64
	var df []float64
	var dv []int64
	var dq []int16

	ids, dtypes, _, _, err := g.FindPoints(tagname) //根据变量名读取基本信息
	if err != nil || len(ids) == 0 {
		return fmt.Errorf("通过变量全名[%s]获取变量在实时数据库中的ID失败:[%s]", tagname, err.Error())
	}
	if ids[0] == 0 {
		return fmt.Errorf("变量名[%s]在实时数据库中不存在", tagname)
	}
	dt = append(dt, timestemp)
	dq = append(dq, int16(qualitie))
	if dtypes[0] < 9 {
		dv = append(dv, int64(math.Ceil(datavalue)))
		df = append(df, 0)
	} else {
		dv = append(dv, 0)
		df = append(df, datavalue)
	}
	_, err = g.PutArchivedValues(ids, dt, df, dv, dq)

	return err
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
func (g *GoldenConnect) SetArchivedValuesBatch(tagnames []string, datavalues []float64, qualities []int, datatimes []int64) error {
	var df []float64
	var dv []int64
	var dq []int16
	cnt := len(tagnames)
	if cnt != len(datavalues) || cnt != len(qualities) || cnt != len(datatimes) {
		return fmt.Errorf("输入参数数组的长度不一致")
	}
	ids, dtypes, _, _, err := g.FindPoints(tagnames...) //根据变量名读取基本信息
	if err != nil || len(ids) == 0 {
		return fmt.Errorf("通过变量全名[%s]获取变量在实时数据库中的ID失败:[%s]", tagnames, err.Error())
	}
	for i, tag := range tagnames {
		if ids[i] == 0 {
			return fmt.Errorf("变量名[%s]在实时数据库中不存在", tag)
		}
		dq = append(dq, int16(qualities[i]))
		if dtypes[i] < 9 {
			dv = append(dv, int64(math.Ceil(datavalues[i])))
			df = append(df, 0)
		} else {
			dv = append(dv, 0)
			df = append(df, datavalues[i])
		}
	}

	_, err = g.PutArchivedValues(ids, datatimes, df, dv, dq)

	return err
}
