package goldengo

//"sync"
//"testing"
//"time"

/*
func TestUseNewEncoder(t *testing.T) {
	sour := "Micbox1-2.x1_asl_asl-xc1_MF1_MKⅠ3_MY1-004_sp:1"
	res1 := UseNewEncoder(sour, "utf8", "ascii")
	res2 := UseNewEncoder(res1, "ascii", "utf8")
	t.Log(sour)
	t.Log(res1)
	t.Log(res2)
}

func TestGetSnapShotByName(t *testing.T) {
	tests := []struct {
		names []string
	}{
		{[]string{"sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_pv:1", "sf8kt.x1_zjs_sfc_ps8kt_4-1_100-1_sum:1"}},
		{[]string{"sf8kt.x3_zjs_sfc_ps8kt_4-1_35-4_47-49_run:1"}},
		{[]string{"sf8kt.webinsert_point", "demo.demo1xxx"}},
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
		{time.Now().Add(-20 * time.Minute).UnixNano(), time.Now().Add(-10 * time.Minute).UnixNano(), 0, []string{"sf8kt.webinsert_point", "demo1.demo1"}},
	}
	gd := CreateGolden("127.0.0.1", "sa", "golden")
	err := gd.Connect()
	if err != nil {
		t.Error(err.Error())
	}
	defer gd.DisConnect()
	for i, tt := range tests {
		datas, err := gd.GetHistoryDataAlignHeadAndTail(tt.bgtime, tt.endtime, tt.interver, tt.names...)
		if err != nil {
			t.Error(err.Error())
		} else {
			t.Logf("第%d行--------", i)
			for k, dv := range datas {
				t.Logf("变量名:%s,数据总数:%d,开始时间:%d:%s,结束时间:%d:%s", k, len(dv.HisRtsd), tt.bgtime, time.Unix(tt.bgtime/1e9, tt.bgtime%1e9/1e6), tt.endtime, time.Unix(tt.endtime/1e9, tt.endtime%1e9/1e6))
				for j, v := range dv.HisRtsd {
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
/*
func TestGoldenPool(t *testing.T) {
	pool, err := NewGoldenPool("localhost", "sa", "golden", 6327, 50) //建立庚顿连接池
	if err != nil {
		t.Error(err)
	}
	defer pool.RemovePool()
	//st, _ := time.Parse("2006-01-02 15:04:05", "2020-06-23 01:00:00")
	//et, _ := time.Parse("2006-01-02 15:04:05", "2020-06-23 09:00:00")
	var table_dot_tags []string
	table_dot_tags = append(table_dot_tags, "test.test001")
	table_dot_tags = append(table_dot_tags, "test.test002")
	table_dot_tags = append(table_dot_tags, "test.test003")
	//table_dot_tags = append(table_dot_tags, "Micbox3-m2mk.x1_asl_asl-xc1_MF2_MKⅠ4_MY2-001_sum:1")
	//table_dot_tags = append(table_dot_tags, "Micbox1-2.x1_asl_asl-xc1_MF1_MKⅠ3_MY1-002_sum:1")

	var wg sync.WaitGroup
	len1 := 100
	len2 := 100
	// go func() {
	// 	for {
	// 		fmt.Printf("%s 当前连接数:%d,当前可用句柄数:%d,当前请求数:%d\n",
	// 			time.Now().Format("2006-01-02 15:04:05.000"), len(pool.Worker), len(pool.Handel), len(pool.Req))
	// 		time.Sleep(1 * time.Second)
	// 	}
	// }()
	for k := 0; k < len1; k++ {
		for i := 0; i < len2; i++ {
			go func(k int) {
				wg.Add(1)
				gd, err := pool.GetConnect()
				if err != nil {
					t.Error(err)
				} else {
					//hd, err := gd.GetHistoryDataAlignHeadAndTail(st.UnixNano(), et.UnixNano(), 0, "Micbox1-2.x1_asl_asl-xc1_MF1_MKⅠ3_MY1-002_sum:1", "Micbox3-m2mk.x1_asl_asl-xc1_MF2_MKⅠ4_MY2-001_sum:1")
					ids, _, _, _, err := gd.FindPoints(table_dot_tags...)
					gd.DisConnect(pool)
					t.Logf("%s 第%d个:%+v,Handel:%d,当前连接数:%d,可用句柄数:%d,当前请求数:%d,Error:%v\n",
						time.Now().Format("2006-01-02 15:04:05.000"), k, ids, gd.Handle, len(pool.Worker), len(pool.Handel), len(pool.Req), err)
				}
				wg.Done()
			}(k*len2 + i)
		}
		wg.Wait()
	}
	t.Log("测试结束")
}
*/
