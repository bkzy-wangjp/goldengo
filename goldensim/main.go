// goldensim project main.go
package main

import (
	"fmt"
	"math/rand"
	"os"
	"time"

	"github.com/bkzy-wangjp/goldengo"
	"gopkg.in/ini.v1"
)

func main() {
	fmt.Println("庚顿实时数据库 数据源模拟器 版本[V1.0]")
	cfg, err := ini.Load("config.ini")
	if err != nil {
		fmt.Printf("读取配置文件失败: %s\n", err.Error())
		fmt.Printf("程序将在20秒后关闭:")
		for i := 20; i > 0; i-- {
			time.Sleep(time.Second)
			fmt.Printf(".")
		}
		os.Exit(1)
	}
	host := cfg.Section("GoldenSim").Key("host").String()
	port, err := cfg.Section("GoldenSim").Key("port").Int()
	if err != nil {
		port = 6327
	}
	username := cfg.Section("GoldenSim").Key("user").String()
	password := cfg.Section("GoldenSim").Key("password").String()
	period, err := cfg.Section("GoldenSim").Key("period").Int64()
	if err != nil {
		period = 10
	}
	count, err := cfg.Section("GoldenSim").Key("point").Int()
	if err != nil {
		count = 100
	}
	fmt.Printf("数据库地址:[%s:%d]\n用户名:[%s],密码:[%s]\n模拟更新周期:[%d]秒,每批次最多更新数量:[%d]\n",
		host, port, username, password, period, count)
	gd := goldengo.CreateGolden(host, username, password, port)

	err = gd.Connect()
	if err != nil {
		fmt.Printf("连接数据库错误:[%s]\n", err.Error())
	} else {
		fmt.Printf("连接数据库成功\n")
	}
	defer gd.DisConnect()
	v, err := gd.HostTime()
	if err != nil {
		fmt.Printf("获取时间时错误:[%s]\n", err.Error())
	}
	fmt.Printf("数据库时间:[%s]\n", time.Unix(v, 0))

	for {
		sttime := time.Now()
		err = gd.GetTables(true)
		if err != nil {
			fmt.Printf("获取数据库信息失败:[%s]", err.Error())
			gd.Connect()
		} else {
			bufcnt := 0
			ids := make([]int, count)
			valf := make([]float64, count)
			vali := make([]int64, count)
			dqus := make([]int16, count)
			dtimes := make([]int64, count)
			for _, point := range gd.Points {
				ids[bufcnt] = point.Base.Id
				valf[bufcnt], vali[bufcnt] = GetSimValue(point.Base)
				dqus[bufcnt] = 0
				dtimes[bufcnt] = time.Now().UnixNano()
				bufcnt++
				if bufcnt == count {
					go gd.PutSnapshots(ids, dtimes, valf, vali, dqus)
					bufcnt = 0
				}
			}
			if bufcnt > 0 {
				go gd.PutSnapshots(ids[:bufcnt], dtimes[:bufcnt], valf[:bufcnt], vali[:bufcnt], dqus[:bufcnt])
				bufcnt = 0
			}
			fmt.Printf("[%s]:更新标签点总数:[%d],耗时[%f]秒\n", time.Now().Format("2006-01-02 15:04:05"), len(gd.Points), time.Since(sttime).Seconds())
		}
		time.Sleep(time.Duration(period) * time.Second)
	}
}

func GetSimValue(point goldengo.GoldenBasePoint) (valf float64, vali int64) {
	rand.Seed(time.Now().UnixNano())
	max := point.HighLimit
	min := point.LowLimit
	drange := max - min
	if drange == 0.0 {
		drange = 100.00
	}
	if drange > 1e10 {
		drange = 1e10
	}
	valf = 0.0
	vali = 0
	switch point.DataType {
	case 0:
		vali = rand.Int63() % 2
	case 9, 10, 11:
		valf = rand.Float64() * drange
	default:
		vali = rand.Int63() * int64(drange)
	}

	return valf, vali

}
