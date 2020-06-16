package goldengo

import (
	//"math/rand"
	"testing"
	//"time"
)

/*
func TestGetVersion(t *testing.T) {
	gd := new(RTDBService)
	version, _ := gd.GetAPIVersion()
	t.Logf("Golden API Vsersion:%s", version)
}

func TestConnect(t *testing.T) {
	tests := []struct {
		host string
		user string
		pswd string
		port int
	}{
		{"127.0.0.1", "sa", "golden", 6327},
	}

	for _, tt := range tests {
		gd := new(RTDBService)
		gd.HostName = tt.host
		gd.UserName = tt.user
		gd.Password = tt.pswd
		gd.Port = tt.port
		err := gd.Connect()
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("Handle:%d,Priv:%d", gd.Handle, gd.Priv)
			stm, _ := gd.HostTime()
			t.Logf("服务器时间:%d", stm)
			t.Log(gd.DisConnect())
		}

	}
}

func TestSearch(t *testing.T) {
	tests := []struct {
		tagmask    string
		tablemask  string
		source     string
		unit       string
		desc       string
		instrument string
		mode       int
	}{
		{"*", "*", "", "", "", "", 2},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for _, tt := range tests {
		ids, err := gd.Search(tt.tagmask, tt.tablemask, tt.source, tt.unit, tt.desc, tt.instrument, tt.mode)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("查询到的结果数量:%d", len(ids))
			for i, id := range ids {
				t.Logf("第%d行:%d", i, id)
			}
		}
	}
}

func TestFormatErrorMessage(t *testing.T) {
	tests := []struct {
		ecode uintptr
	}{
		{0xffff0008},
		{0xffff0028},
		{0xffffff28},
		{0},
	}

	for _, tt := range tests {
		err := FormatErrMsg(tt.ecode)
		if err != nil {
			t.Log(err.Error())
		} else {
			t.Log("无错误")
		}
	}
}


func TestGetSnapshots(t *testing.T) {
	tests := []struct {
		tags []int
	}{
		{[]int{1, 2, 3, 4, 5}},
		{[]int{1, 2, 3, 4}},
		{[]int{1, 3, 2, 6}},
		{[]int{6}},
		{[]int{2}},
		{[]int{1}},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for _, tt := range tests {
		times, values, states, qualitys, errs, _ := gd.GetSnapshots(tt.tags)
		t.Logf("查询到的结果数量:%d", len(times))
		for i, tm := range times {
			t.Logf("第%d行:time=%d,float=%f,int=%d,Q=%d,E=%v", i, tm, values[i], states[i], qualitys[i], errs[i])
		}
	}
}

func TestPutSnapshots(t *testing.T) {
	rand.Seed(time.Now().UnixNano()) //设定随机数种子
	tests := []struct {
		tags    []int
		dtimes  []int64
		dvalues []float64
		dints   []int64
		dqs     []int16
	}{
		{
			[]int{1, 2, 3, 4, 5},
			[]int64{time.Now().Add(-1 * time.Minute).UnixNano(), time.Now().Add(-2 * time.Minute).UnixNano(), time.Now().Add(-3 * time.Minute).UnixNano(), time.Now().Add(-4 * time.Minute).UnixNano(), time.Now().Add(-5 * time.Minute).UnixNano()},
			[]float64{rand.Float64() * 10, rand.Float64() * 10, rand.Float64() * 10, rand.Float64() * 10, rand.Float64() * 10},
			[]int64{1, 1, 1, 1, 1},
			[]int16{0, 0, 0, 0, 0},
		},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for _, tt := range tests {
		errs, _ := gd.PutSnapshots(tt.tags, tt.dtimes, tt.dvalues, tt.dints, tt.dqs)
		for i, err := range errs {
			t.Logf("第%d行:%v", i, err)
		}
	}
}

func TestArchivedValuesCount(t *testing.T) {
	tests := []struct {
		tags    int
		bgtime  int64
		endtime int64
	}{
		{1, time.Now().Add(-8 * time.Hour).UnixNano(), time.Now().UnixNano()},
		{1, time.Now().UnixNano(), time.Now().Add(-8 * time.Hour).UnixNano()},
		{1, 0, 0},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		count, _ := gd.ArchivedValuesCount(tt.tags, tt.bgtime, tt.endtime)
		t.Logf("第%d行:记录数:%d", i, count)
	}
}

func TestGetArchivedValues(t *testing.T) {
	tests := []struct {
		tags    int
		bgtime  int64
		endtime int64
	}{
		{1, time.Now().Add(-8 * time.Minute).UnixNano(), time.Now().UnixNano()},
		{1, time.Now().UnixNano(), time.Now().Add(-8 * time.Minute).UnixNano()},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		times, vs, ints, qs, _ := gd.GetArchivedValues(tt.tags, tt.bgtime, tt.endtime)
		t.Logf("第%d行:-----------", i)
		for j, tm := range times {
			t.Logf("time:%s,v:%f,n:%d,q:%d", time.Unix(tm/1e3, tm%1e3*1e6), vs[j], ints[j], qs[j])
		}
	}
}

func TestGetInterpoValues(t *testing.T) {
	tests := []struct {
		tags    int
		count   int
		bgtime  int64
		endtime int64
	}{
		{1, 10, time.Now().Add(-8 * time.Minute).UnixNano(), time.Now().UnixNano()},
		{1, 8, time.Now().UnixNano(), time.Now().Add(-8 * time.Minute).UnixNano()},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		times, vs, ints, qs, _ := gd.GetInterpoValues(tt.tags, tt.count, tt.bgtime, tt.endtime)
		t.Logf("第%d行:-----------", i)
		for j, tm := range times {
			t.Logf("time:%s,v:%f,n:%d,q:%d", time.Unix(tm/1e3, tm%1e3*1e6), vs[j], ints[j], qs[j])
		}
	}
}

func TestGetSingleValue(t *testing.T) {
	tests := []struct {
		tags     int
		mode     int
		datatime int64
	}{
		{1, 0, time.Now().UnixNano()}, ///0:GOLDEN_NEXT 寻找下一个最近的数据；
		{1, 1, time.Now().UnixNano()}, ///1:GOLDEN_PREVIOUS 寻找上一个最近的数据；
		{1, 2, time.Now().UnixNano()}, ///2:GOLDEN_EXACT 取指定时间的数据，如果没有则返回错误 GoE_DATA_NOT_FOUND；
		{1, 3, time.Now().UnixNano()}, ///3:GOLDEN_INTER 取指定时间的内插值数据。
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		tm, vs, ints, qs, err := gd.GetSingleValue(tt.tags, tt.mode, tt.datatime)
		t.Logf("第%d行:-----------", i)
		t.Logf("time:%s,v:%f,n:%d,q:%d,e:%v", time.Unix(tm/1e3, tm%1e3*1e6), vs, ints, qs, err)
	}
}

func TestSummaryEx(t *testing.T) {
	tests := []struct {
		tags    int
		bgtime  int64
		endtime int64
	}{
		{1, time.Now().Add(-8 * time.Hour).UnixNano(), time.Now().UnixNano()},
		{1, time.Now().UnixNano(), time.Now().Add(-8 * time.Hour).UnixNano()},
		{1, 0, 0},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		maxt, mint, maxv, minv, tv, cav, pav, cnt, _ := gd.SummaryEx(tt.tags, tt.bgtime, tt.endtime)
		t.Logf("第%d行:数据数:%d", i, cnt)
		t.Logf("maxt:%s,mint:%s,maxv:%f,minv:%f,tv:%f,cav:%f,pav:%f",
			time.Unix(maxt/1e3, maxt%1e3*1e6),
			time.Unix(mint/1e3, mint%1e3*1e6),
			maxv, minv, tv, cav, pav,
		)
	}
}

func TestGetPlotValues(t *testing.T) {
	tests := []struct {
		tags     int
		interval int
		bgtime   int64
		endtime  int64
	}{
		{1, 10, time.Now().Add(-8 * time.Hour).UnixNano(), time.Now().UnixNano()},
		{1, 10, time.Now().UnixNano(), time.Now().Add(-8 * time.Hour).UnixNano()},
		//{1, 10, 0, 0},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		tms, vs, ints, qs, _ := gd.GetPlotValues(tt.tags, tt.interval, tt.bgtime, tt.endtime)
		t.Logf("第%d行:数据数:%d", i, len(tms))
		for j, tm := range tms {
			t.Logf("time:%s,v:%f,n:%d,q:%d",
				time.Unix(tm/1e3, tm%1e3*1e6),
				vs[j], ints[j], qs[j],
			)
		}
	}
}

func TestPutSingleValue(t *testing.T) {
	rand.Seed(time.Now().UnixNano()) //设定随机数种子
	tests := []struct {
		tags   int
		dtime  int64
		dvalue float64
		dint   int64
		dq     int16
	}{
		{1, time.Now().Add(-10 * time.Minute).UnixNano(), rand.Float64() * 10, rand.Int63() % 2, 0},
		{2, time.Now().Add(-10 * time.Minute).UnixNano(), rand.Float64() * 10, rand.Int63() % 2, 0},
		{3, time.Now().Add(-10 * time.Minute).UnixNano(), rand.Float64() * 10, rand.Int63() % 2, 0},
		{4, time.Now().Add(-10 * time.Minute).UnixNano(), rand.Float64() * 10, rand.Int63() % 2, 0},
		{5, time.Now().Add(-10 * time.Minute).UnixNano(), rand.Float64() * 10, rand.Int63() % 2, 0},
		{6, time.Now().Add(-10 * time.Minute).UnixNano(), rand.Float64() * 10, rand.Int63() % 2, 0},
		{7, time.Now().Add(-10 * time.Minute).UnixNano(), rand.Float64() * 10, rand.Int63() % 2, 0},
		{8, time.Now().Add(-10 * time.Minute).UnixNano(), rand.Float64() * 10, rand.Int63() % 2, 0},
		{9, time.Now().Add(-10 * time.Minute).UnixNano(), rand.Float64() * 10, rand.Int63() % 2, 0},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		err := gd.PutSingleValue(tt.tags, tt.dtime, tt.dvalue, tt.dint, tt.dq)
		t.Logf("第%d行:%v", i, err)
	}
}

func TestPutArchivedValues(t *testing.T) {
	rand.Seed(time.Now().UnixNano()) //设定随机数种子
	tests := []struct {
		tags    []int
		dtimes  []int64
		dvalues []float64
		dints   []int64
		dqs     []int16
	}{
		{
			[]int{1, 2, 3, 4, 5, 6},
			[]int64{time.Now().Add(-3 * time.Minute).UnixNano(), time.Now().Add(-4 * time.Minute).UnixNano(), time.Now().Add(-5 * time.Minute).UnixNano(), time.Now().Add(-6 * time.Minute).UnixNano(), time.Now().Add(-7 * time.Minute).UnixNano(), time.Now().Add(-7 * time.Minute).UnixNano()},
			[]float64{rand.Float64() * 100, rand.Float64() * 100, rand.Float64() * 100, rand.Float64() * 100, rand.Float64() * 100, rand.Float64() * 100},
			[]int64{1, 1, 1, 1, 1, 1},
			[]int16{0, 0, 0, 0, 0, 0},
		},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for _, tt := range tests {
		errs, _ := gd.PutArchivedValues(tt.tags, tt.dtimes, tt.dvalues, tt.dints, tt.dqs)
		for i, err := range errs {
			t.Logf("第%d行:%v", i, err)
		}
	}
}


func TestGetSinglePointPropterty(t *testing.T) {
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	pot, err := gd.GetSinglePointPropterty(4370)
	if err != nil {
		t.Error(err.Error())
	} else {
		t.Logf("变量点属性:%+v", pot)
		// pot.Base.Desc = pot.Base.Desc + "你好"
		// err := pot.UpdatePointById(gd.Handle)
		// if err != nil {
		// 	t.Error(err.Error())
		// }
	}
}

func TestFindPoints(t *testing.T) {
	tests := []struct {
		tags []string
	}{
		{[]string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1", "sf8kt.x3_zjs_sfc_ps8kt_4-1_35-4_47-49_run:1", "sf8kt.webinsert_point"}},
		{[]string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1", "Micbox1-2.x1_asl_asl-xc1_MF1_MKⅠ3_MY1-004_sp:1"}},
		{[]string{"Micbox1-2.x1_asl_asl-xc1_MF1_MKⅠ3_MY1-004_sp:1", "Micbox1-2.x1_asl_asl-xc1_MF1_MKⅡ3_MY1-043_sp:1"}},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for _, tt := range tests {
		ids, types, class, ms, err := gd.FindPoints(tt.tags...)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("查询到的结果数量:%d", len(ids))
			for i, id := range ids {
				t.Logf("第%d行:id=%d,type=%d,class=%d,isms=%d", i, id, types[i], class[i], ms[i])
			}
		}
	}
}

func TestGetTables(t *testing.T) {
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	err = gd.GetTables(true)
	if err != nil {
		t.Error(err.Error())
	} else {
		t.Logf("标签点表数:%d", gd.TableCounts)
		for i, tb := range gd.Tables {
			t.Logf("第%d个表的属性=%+v", i, tb)
		}
		for i, p := range gd.Points {
			t.Logf("变量点id=%d,变量点属性:%+v", i, p)
		}
	}
}

func TestGetPointPropterty(t *testing.T) {
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	err = gd.GetPointPropterty(1, 2, 3, 4)
	if err != nil {
		t.Error(err.Error())
	} else {
		for i, p := range gd.Points {
			t.Logf("变量点id=%d,变量描述:%s", i, p.Base.Desc)
			p.PlatEx.Id = int64(i)
			p.PlatEx.HHv = 123.456
			p.PlatEx.Hv = 345.678
			p.PlatEx.Lv = 123.643
			p.PlatEx.LLv = 789.123
			p.Base.Desc = "测试信号"
			if e := p.UpdatePointById(gd.Handle); e != nil {
				t.Error(e.Error())
			}
		}
	}
}

func TestCondeTrans(t *testing.T) {
	tests := []struct {
		utf8 string
	}{
		{"ABCDEFG"},
		{"测试信号"},
		{"MF1_MKⅡ3_M1"},
	}
	for _, tt := range tests {
		gbk := Utf8ToGb2312([]byte(tt.utf8))
		utf8 := Gb2312ToUtf8(gbk)
		t.Log(tt.utf8, gbk, string(utf8))
	}
}

//测试未通过
//func TestAppendPointWithJson(t *testing.T) {
//	tests := []struct {
//		pointjson string
//	}{
//		{`{"tag":"demo_001","type":10,"table":3,"desc":"浮点型自动创建1"}`},
//		{`{"tag":"demo_002","type":7,"table":3,"desc":"int型自动创建2"}`},
//		{`{"tag":"demo_003","type":0,"table":3,"desc":"bool型自动创建3"}`},
//	}
//	gd := CreateRTDB("127.0.0.1", "sa", "golden")
//	err := gd.Connect()
//	if err != nil {
//		t.Error(err.Error())
//	}
//	defer gd.DisConnect()
//	for _, tt := range tests {
//		point := new(GoldenPoint)
//		err := point.appendPointWithJson(gd.Handle, tt.pointjson)
//		if err != nil {
//			t.Error(err.Error())
//		} else {
//			t.Logf("新创建的点信息:%+v", point)
//		}
//	}
//}

func TestRemovePointsByIds(t *testing.T) {
	tests := []struct {
		ids []int
	}{
		{[]int{0}},
		{[]int{1255, 0, 1256, 1257, 1258, 1259}},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		t.Logf("=======[%d]======", i)
		num, emaps, err := gd.RemovePointsById(tt.ids...)
		if err != nil {
			t.Error(err.Error())
			for id, e := range emaps {
				if e != nil {
					t.Logf("id=%d,错误:%s", id, e.Error())
				}
			}
		} else {
			t.Logf("共删除了%d个标签点", num)
			for id, e := range emaps {
				if e != nil {
					t.Logf("id=%d,错误:%s", id, e.Error())
				}
			}
		}
	}
}

func TestRemovePointById(t *testing.T) {
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	err = gd.GetPointPropterty(1260, 1261, 1262, 1263)
	if err != nil {
		t.Error(err.Error())
	} else {
		for _, p := range gd.Points {
			if e := p.RemovePointById(gd.Handle); e != nil {
				t.Error(e.Error())
			}
		}
	}
}

func TestRemoveTableById(t *testing.T) {
	tests := []struct {
		id int
	}{
		{3},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		t.Logf("=======[%d]======", i)
		gdt := new(GoldenTable)
		gdt.Id = tt.id
		err := gdt.RemoveTableById(gd.Handle)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Log("删除表成功")
		}
	}
}

func TestInsertPoint(t *testing.T) {
	tests := []struct {
		point GoldenBasePoint
	}{
		{GoldenBasePoint{Tag: "demo_test_0011", TableId: 3, DataType: 0, Desc: "汉语描述信息", Unit: "V"}},
		{GoldenBasePoint{Tag: "demo_test_0010", TableId: 3, DataType: 0, Desc: "我是测试点", Unit: "L"}},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		t.Logf("=======[%d]======", i)
		gdp := new(GoldenPoint)
		gdp.Base = tt.point
		err := gdp.InsertPoint(gd.Handle)
		if err != nil {
			t.Error(err.Error())
		}
	}
}


func TestInsertTable(t *testing.T) {
	tests := []struct {
		name string
		desc string
	}{
		{"demo1", "测试"},
		{"demo2", "demo2"},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		t.Logf("=======[%d]======", i)
		gdt := new(GoldenTable)
		gdt.Name = tt.name
		gdt.Desc = tt.desc
		err := gdt.AppendTable(gd.Handle)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("新建表%s成功,表id是:%d", gdt.Name, gdt.Id)
		}
	}
}

func TestUpdateTableNameById(t *testing.T) {
	tests := []struct {
		id      int
		newname string
	}{
		{3, "demo3"},
		{21, "demo4"},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		t.Logf("=======[%d]======", i)
		gdt := new(GoldenTable)
		gdt.Id = tt.id
		gdt.Name = tt.newname
		err = gdt.UpdateTableNameById(gd.Handle)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("修改表%d名称成功,表新名称是:%s", gdt.Id, gdt.Name)
		}
	}
}


func TestUpdateTableNameByOldName(t *testing.T) {
	tests := []struct {
		oldname string
		newname string
	}{
		{"demo3", "demo5"},
		{"demo4", "demo6"},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		t.Logf("=======[%d]======", i)
		gdt := new(GoldenTable)
		gdt.Name = tt.oldname
		err = gdt.UpdateTableNameByOldName(gd.Handle, tt.newname)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("修改表%s名称成功,表新名称是:%s", tt.oldname, gdt.Name)
		}
	}
}


func TestUpdateTableDescByName(t *testing.T) {
	tests := []struct {
		name string
		desc string
	}{
		{"demo1", "测试1"},
		{"demo2", "测试2"},
	}
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		t.Logf("=======[%d]======", i)
		gdt := new(GoldenTable)
		gdt.Name = tt.name
		gdt.GetTablePropertyByName(gd.Handle)
		t.Logf("原始描述:[%s]", gdt.Desc)
		gdt.Desc = tt.desc
		err = gdt.updateTableDescByName(gd.Handle)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("修改表%s描述成功,表新描述是:%s", tt.name, gdt.Desc)
		}
	}
}
*/
