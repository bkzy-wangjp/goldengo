// goldentest project main.go
package main

import (
	"fmt"
	"runtime"
	"sync"
	"time"

	"github.com/bkzy-wangjp/goldengo"
)

var wg sync.WaitGroup

func main() {
	pool, err := goldengo.NewGoldenPool("localhost", "sa", "golden", 6327, 50) //建立庚顿连接池
	if err != nil {
		fmt.Println(err)
	}
	defer pool.RemovePool()
	go func() {
		for {
			fmt.Printf("%s 当前连接数:%d,当前可用句柄数:%d,当前请求数:%d,当前Go程数:%d\n",
				time.Now().Format("2006-01-02 15:04:05.000"), len(pool.Worker), len(pool.Handel), len(pool.Req), runtime.NumGoroutine())
			time.Sleep(100 * time.Millisecond)
			if runtime.NumGoroutine() == 2 {
				runtime.Goexit()
			}
		}
	}()
	//st, _ := time.Parse("2006-01-02 15:04:05", "2020-06-23 01:00:00")
	//et, _ := time.Parse("2006-01-02 15:04:05", "2020-06-23 09:00:00")
	var table_dot_tags []string
	table_dot_tags = append(table_dot_tags, "test.test001")
	table_dot_tags = append(table_dot_tags, "test.test002")
	table_dot_tags = append(table_dot_tags, "test.test003")
	table_dot_tags = append(table_dot_tags, "Micbox3-m2mk.x1_asl_asl-xc1_MF2_MKⅠ4_MY2-001_sum:1")
	table_dot_tags = append(table_dot_tags, "Micbox1-2.x1_asl_asl-xc1_MF1_MKⅠ3_MY1-002_sum:1")

	len1 := 100
	len2 := 100

	for k := 0; k < len1; k++ {
		for i := 0; i < len2; i++ {
			wg.Add(1)
			go func(k int, tags []string) {
				gd, err := pool.GetConnect()
				if err != nil {
					fmt.Println(err)
				}
				defer func() {
					gd.DisConnect(pool)
					wg.Done()
				}()
				//hd, err := gd.GetHistoryDataAlignHeadAndTail(st.UnixNano(), et.UnixNano(), 0, "Micbox1-2.x1_asl_asl-xc1_MF1_MKⅠ3_MY1-002_sum:1", "Micbox3-m2mk.x1_asl_asl-xc1_MF2_MKⅠ4_MY2-001_sum:1")
				ids, _, _, _, err := gd.FindPoints(tags...)
				fmt.Printf("%s 第%2d个:%+v,Handel:%2d,当前连接数:%2d,可用句柄数:%2d,当前请求数:%2d,Error:%v\n",
					time.Now().Format("2006-01-02 15:04:05.000"), k, ids, gd.Handle, len(pool.Worker), len(pool.Handel), len(pool.Req), err)
			}(k*len2+i, table_dot_tags)
		}
		wg.Wait()
	}
	//time.Sleep(10 * time.Second)
}
