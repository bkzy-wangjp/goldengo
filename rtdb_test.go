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
*/
func TestFindPoints(t *testing.T) {
	tests := []struct {
		tags []string
	}{
		{[]string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1", "sf8kt.x3_zjs_sfc_ps8kt_4-1_35-4_47-49_run:1", "sf8kt.webinsert_point"}},
		{[]string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
		{[]string{"xxxxx", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
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

/*
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

func TestGetTables(t *testing.T) {
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	err = gd.GetTables()
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

func TestGetSinglePointPropterty(t *testing.T) {
	gd := CreateRTDB("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	pot, err := gd.GetSinglePointPropterty(1)
	if err != nil {
		t.Error(err.Error())
	} else {
		t.Logf("变量点属性:%+v", pot)
	}
}
*/
