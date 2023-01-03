package goldengo

import "testing"

func TestGetSnapShotByName(t *testing.T) {
	pool, err := NewGoldenPool("192.168.3.40", "sa", "golden", 6327, 2, 60)
	if err != nil {
		t.Error("连接庚顿数据库错误:", err)
	} else {
		tags := []string{"micbox2-zxs.x3_asl_asl-xc1_sk2_zxs2_s2-017_sd2-012_watt:1",
			"micbox2-zxs.x3_asl_asl-xc1_sk2_zxs2_s2-017_sd2-012_pf:1",
			"micbox2-zxs.x3_asl_asl-xc1_sk2_zxs2_s2-017_sd2-012_st-for:2",
			"micbox2-zxs.x3_asl_asl-xc1_sk2_zxs2_s2-017_sd2-012_fr-no:1",
			"micbox2-zxs.x2_asl_asl-xc1_sk2_zxs2_s2-017_l1238_pv:1",
			"micbox2-zxs.x3_asl_asl-xc1_sk2_zxs2_s2-017_sd2-012_rem-no:1",
		}
		for i := 0; i < len(tags); i++ {
			data, err := pool.GetSnapShotByName(tags[i])
			if err != nil {
				t.Error("读取数据错误:", err)
			} else {
				t.Log(data)
			}
		}
	}
	pool.Close()
}
func TestGetTablesPropertys(t *testing.T) {
	pool, err := NewGoldenPool("192.168.3.40", "sa", "golden", 6327, 2, 60)
	if err != nil {
		t.Error("连接庚顿数据库错误:", err)
	} else {
		tb, err := pool.TablesPropertys("Micbox19-wscl")
		if err != nil {
			t.Error(err)
		} else {
			t.Log(tb)
		}
	}
	pool.Close()
}

func TestGetTagNameListInTables(t *testing.T) {
	pool, err := NewGoldenPool("192.168.3.40", "sa", "golden", 6327, 2, 60)
	if err != nil {
		t.Error("连接庚顿数据库错误:", err)
	} else {
		tbtags, err := pool.GetTagNameListInTables("Micbox19-wscl")
		if err != nil {
			t.Error(err)
		} else {
			for tb, tags := range tbtags {
				t.Log("数据表名为:", tb)
				for _, tag := range tags {
					t.Log(tag)
				}
			}
		}
	}
	pool.Close()
}

func TestTableInsert(t *testing.T) {
	pool, err := NewGoldenPool("192.168.3.40", "sa", "golden", 6327, 2, 60)
	if err != nil {
		t.Error("连接庚顿数据库错误:", err)
	} else {
		id, err := pool.TableInsert("TestTable_1", "测试数据表")
		if err != nil {
			t.Error(err)
		} else {
			t.Log("插入表成功,ID为:", id)
		}
	}
	pool.Close()
}

func TestPointPropterty(t *testing.T) {
	pool, err := NewGoldenPool("192.168.3.40", "sa", "golden", 6327, 2, 60)
	if err != nil {
		t.Error("连接庚顿数据库错误:", err)
	} else {
		gdp, err := pool.PointPropterty("micbox2-zxs.x3_asl_asl-xc1_sk2_zxs2_s2-017_sd2-012_fr-no:1")
		if err != nil {
			t.Error(err)
		} else {
			t.Logf("标签点信息:%+v", gdp)
		}
	}
	pool.Close()
}

func TestDisconnect(t *testing.T) {
	g := new(GoldenConnect)
	g.Handle = 1
	err := g.disConnect()
	if err != nil {
		t.Errorf(err.Error())
	}
}
