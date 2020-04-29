package goldengo

import (
	"strings"

	"github.com/axgle/mahonia"
)

func GbkToUtf8(buffer []byte) string {
	enc := mahonia.NewDecoder("GBK")
	_, cdata, _ := enc.Translate(buffer, true)
	return strings.Trim(string(cdata), "\u0000")
}

/*******************************************************************************
- 功能:拆分Unix纳秒为Unix秒和毫秒
- 输入:
	[nanosec] UnixNano时间戳
- 输出:
	[sec] UnixSec时间戳
	[ms]  剩余的毫秒数
*******************************************************************************/
func splitUnixNanoSec(nanosec int64) (int32, int16) {
	return int32(nanosec / 1e9), int16((nanosec / 1e6) % 1000)
}
