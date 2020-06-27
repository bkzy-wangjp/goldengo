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
	"time"

	"github.com/bkzy-wangjp/goldengo"
	"github.com/kardianos/service"
	"golang.org/x/text/encoding/simplifiedchinese"
	"golang.org/x/text/transform"
	"gopkg.in/ini.v1"
)

func main() {
	svcConfig := &service.Config{
		Name:        "GoldenSim",
		DisplayName: "GoldenSim",
		Description: "Golden Data Source Simulation",
	}

	prg := &program{}
	s, err := service.New(prg, svcConfig)
	if err != nil {
		fmt.Println("New Sevice Error:[%s]", err.Error())
	}
	if len(os.Args) > 1 {
		if os.Args[1] == "install" {
			err := s.Install()
			if err != nil {
				fmt.Printf("安装服务时遇到错误:[%s]\n", err.Error())
			} else {
				fmt.Println("服务安装成功")
			}
			return
		}

		if os.Args[1] == "remove" {
			err := s.Uninstall()
			if err != nil {
				fmt.Printf("卸载服务时遇到错误:[%s]\n", err.Error())
			} else {
				fmt.Println("服务卸载成功")
			}
			return
		}
	}

	if err = s.Run(); err != nil {
		fmt.Println("运行启动失败")
	}
}
func mainrun() {
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
	gdpool := goldengo.NewGoldenPool(host, username, password, port, 50)
	gd, err := gdpool.GetConnect()
	if err != nil {
		fmt.Printf("连接数据库错误:[%s]\n", err.Error())
	} else {
		fmt.Printf("连接数据库成功\n")
	}
	defer func() {
		gd.DisConnect(gdpool)
		gdpool.RemovePool()
	}()
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
			gd.DisConnect(gdpool)
			gd, _ = gdpool.GetConnect()
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

type program struct{}

func (p *program) Start(s service.Service) error {
	go p.run()
	return nil
}

func (p *program) run() {
	mainrun()
}

func (p *program) Stop(s service.Service) error {
	return nil
}
