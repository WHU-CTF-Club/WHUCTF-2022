# Description
go? ruby? php? java? or c? maybe more
who can help me to debug!!!

# Difficulty
⭐⭐

# Flag
`mayctf{n0w_1_mas73r_al1_lan8_ma9b3}`

# WriteUp
将所有语言转为某一种语言运行即可
```go
package main

// aes
import (
	"crypto/aes"
	"crypto/cipher"
	"encoding/base64"
	"fmt"
)

func main() {
	key := GetKey()
	// key := "14159265358979323846264338327950"

	encryptCode := GetCode()
	//encryptCode := "I/ozsDx6hIaMfXZWpoUP6MnVuXr2N28bN2bUWaa1h/gmEGhKzJDvY8fZymhBz6GQ"

	decryptCode := AesDecrypt(encryptCode, key)
	fmt.Println("flag：", decryptCode)
}

func GetCode() string {
	chcode := make(chan byte, 100)
	go SinkCode(chcode)
	var code string
	for i := range chcode {
		code += string(i)
	}
	return code
}

func SinkCode(chcode chan byte) {
	code := [...]byte{0o111, 0o57, 0o157, 0o172, 0o163, 0o104,
		0o170, 0o66, 0o150, 0o111, 0o141, 0o115,
		0o146, 0o130, 0o132, 0o127, 0o160, 0o157,
		0o125, 0o120, 0o66, 0o115, 0o156, 0o126,
		0o165, 0o130, 0o162, 0o62, 0o116, 0o62,
		0o70, 0o142, 0o116, 0o62, 0o142, 0o125,
		0o127, 0o141, 0o141, 0o61, 0o150, 0o57,
		0o147, 0o155, 0o105, 0o107, 0o150, 0o113,
		0o172, 0o112, 0o104, 0o166, 0o131, 0o70,
		0o146, 0o132, 0o171, 0o155, 0o150, 0o102,
		0o172, 0o66, 0o107, 0o121}
	for i := range code {
		chcode <- code[i]
	}
	close(chcode)
}

func GetKey() []byte {
	chkey := make(chan byte, 32)
	go Sinkkey(chkey)
	var key []byte
	for i := range chkey {
		key = append(key, i)
	}
	return key
}

func Sinkkey(chkey chan byte) {
	key := [...]byte{0b110001, 0b110100, 0b110001, 0b110101,
		0b111001, 0b110010, 0b110110, 0b110101,
		0b110011, 0b110101, 0b111000, 0b111001,
		0b110111, 0b111001, 0b110011, 0b110010,
		0b110011, 0b111000, 0b110100, 0b110110,
		0b110010, 0b110110, 0b110100, 0b110011,
		0b110011, 0b111000, 0b110011, 0b110010,
		0b110111, 0b111001, 0b110101, 0b110000}
	for i := range key {
		chkey <- key[i]
	}
	close(chkey)
}

func AesDecrypt(cryted string, key []byte) string {
	crytedByte, _ := base64.StdEncoding.DecodeString(cryted)

	block, _ := aes.NewCipher(key)
	blockSize := block.BlockSize()
	blockMode := cipher.NewCBCDecrypter(block, key[:blockSize])
	orig := make([]byte, len(crytedByte))
	blockMode.CryptBlocks(orig, crytedByte)
	orig = PKCS7UnPadding(orig)
	return string(orig)
}

func PKCS7UnPadding(origData []byte) []byte {
	length := len(origData)
	unpadding := int(origData[length-1])
	return origData[:(length - unpadding)]
}

```
