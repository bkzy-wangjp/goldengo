package goldengo

import (
	"C"
	"bytes"
	"fmt"
	"io/ioutil"
	"reflect"

	"unsafe"

	"golang.org/x/text/encoding/simplifiedchinese"
	"golang.org/x/text/transform"
)

/****************************************************
功能:字符串转码,将utf8码转换为gbk码
输入:[s] 原始字符串
输出:转码后的字符串
说明:
时间:2020年6月11日
编辑:wang_jp
****************************************************/
func Utf8ToGbk(s []byte) []byte {
	reader := transform.NewReader(bytes.NewReader(s), simplifiedchinese.GBK.NewEncoder())
	d, e := ioutil.ReadAll(reader)
	if e != nil {
		return nil
	}
	return d
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
- 功能:C的char数组切片转换为go 字符串
- 输入:
	[chars] C语言的char字符数组切片
- 输出:
	[string] go 字符串
- 时间：2020年5月14日
*******************************************************************************/
func cChars2String(chars []C.char) string {
	var bstr []byte
	for _, c := range chars {
		if byte(c) > 0 {
			bstr = append(bstr, byte(c))
		}
	}
	resstr := string(GbkToUtf8(bstr))
	return resstr
}

/*******************************************************************************
- 功能:Go的string转换为c char切片
- 输入:
	[chars] C语言的char字符数组切片
- 输出:
	[string] go 字符串
- 时间：2020年5月14日
*******************************************************************************/
func string2Cchars(bstr string) []C.char {
	gbkstr := Utf8ToGbk([]byte(bstr))
	var chars []C.char
	for _, c := range gbkstr {
		chars = append(chars, C.char(c))
	}
	return chars
}

func string2C20chars(bstr string) [20]C.char {
	gbkstr := Utf8ToGbk([]byte(bstr))
	var chars [20]C.char
	for i, c := range gbkstr {
		if i < len(chars) {
			chars[i] = C.char(c)
		}
	}
	return chars
}
func string2C50chars(bstr string) [50]C.char {
	gbkstr := Utf8ToGbk([]byte(bstr))
	var chars [50]C.char
	for i, c := range gbkstr {
		if i < len(chars) {
			chars[i] = C.char(c)
		}
	}
	return chars
}
func string2C80chars(bstr string) [80]C.char {
	gbkstr := Utf8ToGbk([]byte(bstr))
	var chars [80]C.char
	for i, c := range gbkstr {
		if i < len(chars) {
			chars[i] = C.char(c)
		}
	}
	return chars
}
func string2C100chars(bstr string) [100]C.char {
	gbkstr := Utf8ToGbk([]byte(bstr))
	var chars [100]C.char
	for i, c := range gbkstr {
		if i < len(chars) {
			chars[i] = C.char(c)
		}
	}
	return chars
}
func string2C160chars(bstr string) [160]C.char {
	gbkstr := Utf8ToGbk([]byte(bstr))
	var chars [160]C.char
	for i, c := range gbkstr {
		if i < len(chars) {
			chars[i] = C.char(c)
		}
	}
	return chars
}
func string2C256chars(bstr string) [256]C.char {
	gbkstr := Utf8ToGbk([]byte(bstr))
	var chars [256]C.char
	for i, c := range gbkstr {
		if i < len(chars) {
			chars[i] = C.char(c)
		}
	}
	return chars
}
func string2C2036chars(bstr string) [2036]C.char {
	gbkstr := Utf8ToGbk([]byte(bstr))
	var chars [2036]C.char
	for i, c := range gbkstr {
		if i < len(chars) {
			chars[i] = C.char(c)
		}
	}
	return chars
}

/*******************************************************************************
- 功能:C的byte转换为go bool
- 输入:
	[cbyte] C语言的byte类型变量
- 输出:
	[bool] go bool
- 时间：2020年5月15日
*******************************************************************************/
func cByte2Bool(cbyte C.uchar) bool {
	return cbyte > 0
}

/*******************************************************************************
- 功能:go的bool转换为c byte
- 输入:
	[bool] go语言的bool类型变量
- 输出:
	[c.uchar] c语言的uchar类型变量
- 时间：2020年5月26日
*******************************************************************************/
func bool2Cbyte(gobool bool) C.uchar {
	if gobool {
		return 1
	} else {
		return 0
	}
}

/*******************************************************************************
- 功能:C的 []uchar 转换为go []byte
- 输入:
	[cbyte] C语言的[]uchar 类型变量
- 输出:
	[[]byte] go []byte
- 时间：2020年5月26日
*******************************************************************************/
func cUchar2bytes(cbytes []C.uchar) []byte {
	var gbytes []byte
	for _, uchar := range cbytes {
		if uchar > 0 {
			gbytes = append(gbytes, byte(uchar))
		}
	}
	return gbytes
}

/*******************************************************************************
- 功能:go的 []byte 转换为c []uchar
- 输入:
	[[]byte] go语言的[]byte 类型变量
- 输出:
	[[]uchar] c []uchar
- 时间：2020年5月26日
*******************************************************************************/
func bytes2C5uchar(gbytes []byte) [5]C.uchar {
	var cbytes [5]C.uchar
	for i, bt := range gbytes {
		if i < len(cbytes) {
			cbytes[i] = C.uchar(bt)
		}
	}
	return cbytes
}
func bytes2C164uchar(gbytes []byte) [164]C.uchar {
	var cbytes [164]C.uchar
	for i, bt := range gbytes {
		if i < len(cbytes) {
			cbytes[i] = C.uchar(bt)
		}
	}
	return cbytes
}

/****************************************************
功能：判断元素在数组、Map中是否存在
输入：元素、数组或者Map、Slice
输出：存在输出true，不存在输出false
说明：对于数组、Slice，判断的是值是否存在，对于Map，判断的是Key是否存在
时间：2019年12月15日
编辑：wang_jp
****************************************************/
func IsExistItem(obj interface{}, target interface{}) bool {
	targetValue := reflect.ValueOf(target)
	switch reflect.TypeOf(target).Kind() {
	case reflect.Slice, reflect.Array:
		for i := 0; i < targetValue.Len(); i++ {
			if targetValue.Index(i).Interface() == obj {
				return true
			}
		}
	case reflect.Map:
		if targetValue.MapIndex(reflect.ValueOf(obj)).IsValid() {
			return true
		}
	}
	return false
}
