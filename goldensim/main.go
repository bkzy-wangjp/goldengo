// goldensim project main.go
package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"math/rand"
	"os"
	"os/exec"
	"strings"
	"sync"
	"time"

	"github.com/bkzy-wangjp/goldengo"
	"github.com/bkzy-wangjp/miclog"
	"golang.org/x/text/encoding/simplifiedchinese"
	"golang.org/x/text/transform"
	"gopkg.in/ini.v1"
)

var Log *miclog.MicLog

func main() {
	defer func() {
		if err := recover(); err != nil {
			Log.WriteLog(fmt.Sprintf("发生错误:[%v]", err), true)
		}
	}()
	Log = new(miclog.MicLog)

	fmt.Println("庚顿实时数据库 数据源模拟器 版本[V1.0]")
	//WriteLog("Msg", "庚顿实时数据库 数据源模拟器 版本[V1.0]", false)
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
	//每批次更新点数
	count, err := cfg.Section("GoldenSim").Key("point").Int()
	if err != nil {
		count = 100
	}
	Log.WriteLog(fmt.Sprintf("数据库地址:[%s:%d]\n用户名:[%s],密码:[%s]\n模拟更新周期:[%d]秒,每批次最多更新数量:[%d]",
		host, port, username, password, period, count), true)
	gdpool, err := goldengo.NewGoldenPool(host, username, password, port, 50)
	if err != nil {
		Log.WriteLog(fmt.Sprintf("创建庚顿连接池错误:[%s]", err.Error()), true)
	} else {
		Log.WriteLog(fmt.Sprintf("创建庚顿连接池成功"), true)
	}
	gd, err := gdpool.GetConnect()
	if err != nil {
		Log.WriteLog(fmt.Sprintf("获取庚顿连接句柄错误:[%s]", err.Error()), true)
	} else {
		Log.WriteLog(fmt.Sprintf("获取庚顿连接句柄成功"), true)
	}
	defer func() {
		gd.DisConnect(gdpool)
		gdpool.RemovePool()
	}()
	v, err := gd.HostTime()
	if err != nil {
		Log.WriteLog(fmt.Sprintf("获取时间时错误:[%s]", err.Error()), true)
	}
	Log.WriteLog(fmt.Sprintf("数据库时间:[%s]", time.Unix(v, 0)), true)
	var wg sync.WaitGroup
	for {
		sttime := time.Now()
		err = gd.GetTables(true)
		if err != nil {
			Log.WriteLog(fmt.Sprintf("获取数据库信息失败:[%s]", err.Error()), true)
			gd.DisConnect(gdpool)
			gd, err = gdpool.GetConnect()
			if err != nil {
				Log.WriteLog(fmt.Sprintf("重新获取庚顿连接句柄失败:[%s]", err.Error()), true)
			}
		} else {
			bufcnt := 0                //点数计数器
			totalcnt := 0              //总点数计
			pointLen := len(gd.Points) //总点数
			var ids []int              //id切片
			var valf []float64         //浮点数值切片
			var vali []int64           //整数切片
			var dqus []int16           //质量码
			var dtimes []int64         //时间
			//pcntchan := make(chan int, pointLen/count)
			for _, point := range gd.Points {
				ids = append(ids, point.Base.Id)
				fv, iv := GetSimValue(point.Base)
				valf = append(valf, fv)
				vali = append(vali, iv)
				dqus = append(dqus, 0)
				dtimes = append(dtimes, time.Now().UnixNano())
				bufcnt++
				totalcnt++
				if bufcnt == count || totalcnt == pointLen {
					wg.Add(1)
					go func(id []int, dtime []int64, vf []float64, vi []int64, qlt []int16) {
						defer func() {
							wg.Done()
							if err := recover(); err != nil {
								Log.WriteLog(fmt.Sprintf("发生错误:[%v]", err), true)
							}
						}()
						golden := new(goldengo.Golden)
						err := golden.GetConnect(gdpool)
						if err == nil {
							perr, err := golden.PutSnapshots(id, dtime, vf, vi, qlt)
							golden.DisConnect(gdpool)
							if err != nil {
								Log.WriteLog(fmt.Sprintf("写快照遇到错误:[]%s", err.Error()), true)
							} else {
								for i, e := range perr {
									if e != nil {
										Log.WriteLog(fmt.Sprintf("写标签点[%d]快照遇到错误:[%s]", id[i], e.Error()), true)
									}
								}
							}
						} else {
							Log.WriteLog(fmt.Sprintf("获取连接句柄错误:[]%s", err.Error()), true)
						}
					}(ids, dtimes, valf, vali, dqus)
					bufcnt = 0
					ids = make([]int, 0)      //id切片
					valf = make([]float64, 0) //浮点数值切片
					vali = make([]int64, 0)   //整数切片
					dqus = make([]int16, 0)   //质量码
					dtimes = make([]int64, 0) //时间
				}
			}
			wg.Wait()
			msg := fmt.Sprintf("标签点总数:[%d],更新耗时[%f]秒", totalcnt, time.Since(sttime).Seconds())
			Log.WriteLog(msg, true)
		}
		time.Sleep(time.Duration(period) * time.Second)
	}
}
func mainrun() {

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

/****************************************************
功能:字符串转码,将bgk码转换为utf8码
输入:[s] 原始字符串
输出:转码后的字符串
说明:
时间:2020年6月11日
编辑:wang_jp
****************************************************/
func GbkToUtf8(s []byte) []byte {
	reader := transform.NewReader(bytes.NewReader(s), simplifiedchinese.GBK.NewDecoder())
	d, e := ioutil.ReadAll(reader)
	if e != nil {
		return nil
	}
	var bstr []byte
	for _, c := range d {
		if c > 0 {
			bstr = append(bstr, c)
		}
	}
	return bstr
}

/****************************************************
功能:判断进程中是否有指定的应用程序
输入:应用程序名称
输出:存在输出true，不存在输出false
说明:
时间:2020年6月11日
编辑:wang_jp
****************************************************/
func IsExeRuning(strExeName string) bool {
	cmd := exec.Command("tasklist") //列出所有任务列表
	var out bytes.Buffer
	var stderr bytes.Buffer
	cmd.Stdout = &out
	cmd.Stderr = &stderr
	err := cmd.Run()
	if err != nil {
		return false
	}
	outstr := string(GbkToUtf8(out.Bytes()))
	if strings.Contains(strings.ToLower(outstr), strings.ToLower(strExeName)) {
		return true
	} else {
		return false
	}
}

/****************************************************
功能:判断服务是否存在
输入:[serviceName] 服务的名称
	[state] 查找的服务的状态,active:运行着的服务;inactive:停止的服务;all:所有的服务
输出:存在输出true，不存在输出false
说明:
时间:2020年6月11日
编辑:wang_jp
****************************************************/
func IsSeviceExist(serviceName string, state string) bool {
	cmd := new(exec.Cmd)
	switch state {
	case "inactive":
		cmd = exec.Command("sc", "query", "type=service", "state=inactive") //列出所有停止的任务列表
	case "all":
		cmd = exec.Command("sc", "query", "type=service", "state=all") //列出所有的任务列表
	default:
		cmd = exec.Command("sc", "query", "type=service") //列出所有运行的任务列表
	}

	var out bytes.Buffer
	var stderr bytes.Buffer
	cmd.Stdout = &out
	cmd.Stderr = &stderr
	err := cmd.Run()
	if err != nil {
		return false
	}
	outstr := string(GbkToUtf8(out.Bytes()))
	fmt.Println(outstr)
	if strings.Contains(strings.ToLower(outstr), strings.ToLower(serviceName)) {
		return true
	} else {
		return false
	}
}
