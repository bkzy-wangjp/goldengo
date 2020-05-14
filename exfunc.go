package goldengo

import (
	"C"
	"fmt"
	"strings"
	"unsafe"

	"github.com/axgle/mahonia"
)

func GbkToUtf8(buffer []byte) string {
	enc := mahonia.NewDecoder("GBK")
	_, cdata, _ := enc.Translate(buffer, true)
	return strings.Trim(string(cdata), "\u0000")
}

/*******************************************************************************
-功能：格式化错误码
-参数: [ecode] 错误码,为0时无错误
-返回: [error] 错误信息；ecode为0时返回nil
*******************************************************************************/
func FormatErrMsg(ecode uintptr) error {
	var eMsg error
	if ecode > 0 {
		size := 256
		_message := make([]byte, size)
		_name := make([]byte, size)
		code, _, _ := go_format_message.Call(
			ecode,
			uintptr(unsafe.Pointer(&_message[0])),
			uintptr(unsafe.Pointer(&_name[0])),
			uintptr(size),
		)
		if code == 0 {
			eMsg = fmt.Errorf("ECODE:0x%X, ENAME:%s, DESC:%s",
				ecode, GbkToUtf8(_name),
				GbkToUtf8(_message),
			)
		} else {
			eMsg = fmt.Errorf("ECODE:0x%X", code)
		}
	}
	return eMsg
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

/*******************************************************************************
- 功能:C char数组切片转换为go 字符串
- 输入:
	[chars] C.char字符数组切片
- 输出:
	[string] go 字符串
- 时间：2020年5月14日
*******************************************************************************/
func CChars2String(chars []C.char) string {
	var bstr []byte
	for _, c := range chars {
		if byte(c) > 0 {
			bstr = append(bstr, byte(c))
		}
	}
	return string(bstr)
}
