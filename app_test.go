package goldengo

/*
import (
	"testing"
	"time"
)

func TestGetSnapShotByName(t *testing.T) {
	tests := []struct {
		names []string
	}{
		{[]string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
		{[]string{"sf8kt.x3_zjs_sfc_ps8kt_4-1_35-4_47-49_run:1"}},
		{[]string{"sf8kt.webinsert_point", "demo.demo1"}},
	}
	gd := CreateGolden("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for _, tt := range tests {
		snaps, err := gd.GetSnapShotByName(tt.names...)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("查询到的结果数量:%d", len(snaps))
			for i, id := range snaps {
				t.Logf("%s:%+v", i, id)
			}
		}
	}
}

func TestGetHistoryByName(t *testing.T) {
	tests := []struct {
		bgtime  int64
		endtime int64
		names   []string
	}{
		{time.Now().Add(-10 * time.Minute).UnixNano(), time.Now().UnixNano(), []string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
		{time.Now().Add(-10 * time.Minute).UnixNano(), time.Now().UnixNano(), []string{"sf8kt.x3_zjs_sfc_ps8kt_4-1_35-4_47-49_run:1"}},
		{time.Now().Add(-10 * time.Minute).UnixNano(), time.Now().UnixNano(), []string{"sf8kt.webinsert_point", "demo.demo1"}},
	}
	gd := CreateGolden("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		datas, err := gd.GetHistoryByName(tt.bgtime, tt.endtime, tt.names...)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("第%d行,变量数:%d", i, len(datas))
			for k, vs := range datas {
				t.Logf("变量名:%s,数据总数:%d-------------", k, len(vs))
				for _, v := range vs {
					t.Logf("%+v", v)
				}
			}
		}
	}
}

func TestGetHisIntervalByName(t *testing.T) {
	tests := []struct {
		count   int
		bgtime  int64
		endtime int64
		names   []string
	}{
		{10, time.Now().Add(-10 * time.Minute).UnixNano(), time.Now().UnixNano(), []string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
		{10, time.Now().Add(-10 * time.Minute).UnixNano(), time.Now().UnixNano(), []string{"sf8kt.x3_zjs_sfc_ps8kt_4-1_35-4_47-49_run:1"}},
		{10, time.Now().Add(-10 * time.Minute).UnixNano(), time.Now().UnixNano(), []string{"sf8kt.webinsert_point", "demo.demo1"}},
	}
	gd := CreateGolden("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		datas, err := gd.GetHisIntervalByName(tt.count, tt.bgtime, tt.endtime, tt.names...)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("第%d行,变量数:%d", i, len(datas))
			for k, vs := range datas {
				t.Logf("变量名:%s,数据总数:%d-------------", k, len(vs))
				for _, v := range vs {
					t.Logf("%+v", v)
				}
			}
		}
	}
}

func TestGetHistorySingleByName(t *testing.T) {
	tests := []struct {
		mode     int
		datatime int64
		names    []string
	}{
		{0, time.Now().Add(-10 * time.Minute).UnixNano(), []string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
		{1, time.Now().Add(-10 * time.Minute).UnixNano(), []string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
		{2, time.Now().Add(-10 * time.Minute).UnixNano(), []string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
		{3, time.Now().Add(-10 * time.Minute).UnixNano(), []string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
	}
	gd := CreateGolden("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		datas, err := gd.GetHistorySingleByName(tt.mode, tt.datatime, tt.names...)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("第%d行,变量数:%d", i, len(datas))
			for k, vs := range datas {
				t.Logf("变量名:%s,%s,数据:%+v", k, time.Unix(vs.Time/1e3, vs.Time%1e3*1e6), vs)
			}
		}
	}
}

func TestGetHistoryDataAlignHeadAndTail(t *testing.T) {
	tests := []struct {
		bgtime   int64
		endtime  int64
		interver int
		names    []string
	}{
		{time.Now().Add(-10 * time.Minute).UnixNano(), time.Now().UnixNano(), 60, []string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1"}},
		{time.Now().Add(-10 * time.Minute).UnixNano(), time.Now().UnixNano(), 0, []string{"sf8kt.x3_zjs_sfc_ps8kt_4-1_35-4_47-49_run:1"}},
		//{time.Now().Add(-10 * time.Minute).UnixNano(), time.Now().UnixNano(), 0, []string{"sf8kt.webinsert_point", "demo.demo1"}},
	}
	gd := CreateGolden("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		datas, errs, err := gd.GetHistoryDataAlignHeadAndTail(tt.bgtime, tt.endtime, tt.interver, tt.names...)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("第%d行,变量数:%d;E=%s", i, len(datas), errs)
			for k, dv := range datas {
				t.Logf("变量名:%s,数据总数:%d,开始时间:%d:%s,结束时间:%d:%s", k, len(dv), tt.bgtime, time.Unix(tt.bgtime/1e9, tt.bgtime%1e9/1e6), tt.endtime, time.Unix(tt.endtime/1e9, tt.endtime%1e9/1e6))
				for j, v := range dv {
					t.Logf("%d:%s:%+v", j, time.Unix(v.Time/1e3, v.Time%1e3*1e6), v)
				}
			}
		}
	}
}

func TestGetTagListInTables(t *testing.T) {
	tests := []struct {
		names []string
	}{
		{[]string{"sf8kt", "demo", "dkjg"}},
		{[]string{}},
	}
	gd := CreateGolden("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for _, tt := range tests {
		datas, err := gd.GetTagListInTables(tt.names...)
		t.Log("----------------------------")
		if err != nil {
			t.Error(err.Error())
		} else {
			for k, dv := range datas {
				t.Logf("表:%s,数据总数:%d", k, len(dv))
				for _, v := range dv {
					t.Logf("%+v", v)
				}
			}
		}
	}
}

func TestGetTagPointInfoByName(t *testing.T) {
	tests := []struct {
		names []string
	}{
		{[]string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
		{[]string{}},
	}
	gd := CreateGolden("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for _, tt := range tests {
		datas, err := gd.GetTagPointInfoByName(tt.names...)
		t.Log("----------------------------")
		if err != nil {
			t.Error(err.Error())
		} else {
			for k, dv := range datas {
				t.Logf("tag:%s,数据:%+v", k, dv)
			}
		}
	}
}

*/
