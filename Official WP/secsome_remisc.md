# Reverse Engineering Writeup by secsome

## 前言
要哭了，怎么就是没人做reverse，明明都很简单的（
所有求解的代码都尝试用python写了（
对了我python也学得很烂，属于是能用就行的级别，大家看看就行（

## 个人赛

怎么这么少人玩RE！！！！！！！！！！！！！！
按照分数顺序讲了。

### hello_net
这题其实是我的问题，本来是打算让大家搜索后找到dnSpy这个工具来反编译的，结果忘了对字符串进行处理，导致直接用文本编辑器打开这个题目就能得到flag了。

不过其实难度差别没多大？

附源代码：
```cs
using System;

Console.WriteLine("Welcome to .NET world! Feel free to input something!");

if (Console.ReadLine() == "Hello .NET")
	Console.WriteLine("Your flag is mayctf{I_Think_NET_1S_S1mpler_Than_NATIVE!}");
else
	Console.WriteLine("Try again!");

Console.WriteLine("Press any key to exit the program!");
Console.ReadKey(true);

```

### maze
从现在开始就没几个人做RE了，难受（

首先试图用IDA打开程序，发现打不开，但是根据我写在提示中的内容可以发现是`UPX`加壳（
因此`upx -d`去壳后打开程序，结合题目名字发现用`WASD`走迷宫即可。

提示：IDA反汇编界面对数字按R可以转换成字符显示

附源代码：
```cpp
#include <iostream>
#include <string>

int main()
{
	std::cout << "I'm trapped! Can you help me to get out of here?" << std::endl;
	std::string input;
	std::cin >> input;

	if (input.length() != 32)
	{
		std::cout << "You don't know how to do reverse, do you?" << std::endl;
		return 0;
	}

	char maze[10][11]
	{
		"*#########",
		"**########",
		"#*########",
		"***#######",
		"*#***##***",
		"**##****#*",
		"#**######*",
		"#*#*******",
		"**#*######",
		"###*******",
	};

	int pos_x = 0, pos_y = 0;

	for (const auto& opt : input)
	{
		switch (opt)
		{
			case 'W':
				--pos_y;
				break;
			case 'A':
				--pos_x;
				break;
			case 'S':
				++pos_y;
				break;
			case 'D':
				++pos_x;
				break;
			default:
				std::cout << "What are you doing?" << std::endl;
				return 0;
		}

		if (pos_x < 0 || pos_x > 9 || pos_y < 0 || pos_y > 9)
		{
			std::cout << "Oooooh! My head is hurt!" << std::endl;
			return 0;
		}
	}

	if (pos_x == 9 && pos_y == 9)
		std::cout << "Congratulations! Your flag is mayctf{sha256(input)}." << std::endl;
	else
		std::cout << "Oops, I'm still in the maaaaaze!" << std::endl;

	return 0;
}
```
附解题代码：
```python
import hashlib

maze = ["*#########",
		"**########",
		"#*########",
		"***#######",
		"*#***##***",
		"**##****#*",
		"#**######*",
		"#*#*******",
		"**#*######",
		"###*******"]

vis = [ [ 0 for j in range(10) ] for i in range(10) ]

def check(x, y):
	if x >= 0 and y >= 0 and x < 10 and y < 10 and maze[x][y] == '*' and vis[x][y] == False:
		return True
	else:
		return False

path = ['0' for i in range(100)]

def extend(x, y, depth, dir):
	path[depth] = dir
	return solve(x, y, depth + 1)

def solve(x, y, depth):
	if x == 9 and y == 9:
		vis[x][y] = 1
		return True

	if check(x, y) == True:
		vis[x][y] = True
		if extend(x - 1, y, depth, 'W') == True:
			return True
		if extend(x, y - 1, depth, 'A') == True:
			return True
		if extend(x + 1, y, depth, 'S') == True:
			return True
		if extend(x, y + 1, depth, 'D') == True:
			return True

		vis[x][y] = False
		return False

def result():
	ans = ''
	for ch in path:
		if ch == '0':
			return ans
		else:
			ans = ans + ch

solve(0, 0, 0)
print('mayctf{' + hashlib.sha256(result().encode('utf-8')).hexdigest() + '}')
```

### mixture
这题不是我出的其实，但是是一道比较典型的代码审计题目，发现主体代码是Go后把其它语言的垃圾代码删掉统一用Go再编译就行了）

```go
package main

// aes
import (
	"bytes"
	"crypto/aes"
	"crypto/cipher"
	"encoding/base64"
	"fmt"
)

func main() {
	orig := "mayctf{n0w_1_mas73r_al1_lan8_ma9b3}"
	key := "14159265358979323846264338327950"
	fmt.Println("原文：", orig)

	encryptCode := AesEncrypt(orig, key)
	//  I/ozsDx6hIaMfXZWpoUP6MnVuXr2N28bN2bUWaa1h/gmEGhKzJDvY8fZymhBz6GQ
	fmt.Println("密文：", encryptCode)

	decryptCode := AesDecrypt(encryptCode, key)
	fmt.Println("解密结果：", decryptCode)
}

func AesEncrypt(orig string, key string) string {
	// 转成字节数组
	origData := []byte(orig)
	k := []byte(key)

	// 分组秘钥
	block, _ := aes.NewCipher(k)
	// 获取秘钥块的长度
	blockSize := block.BlockSize()
	// 补全码
	origData = PKCS7Padding(origData, blockSize)
	// 加密模式
	blockMode := cipher.NewCBCEncrypter(block, k[:blockSize])
	// 创建数组
	cryted := make([]byte, len(origData))
	// 加密
	blockMode.CryptBlocks(cryted, origData)

	return base64.StdEncoding.EncodeToString(cryted)

}

func AesDecrypt(cryted string, key string) string {
	// 转成字节数组
	crytedByte, _ := base64.StdEncoding.DecodeString(cryted)
	k := []byte(key)

	// 分组秘钥
	block, _ := aes.NewCipher(k)
	// 获取秘钥块的长度
	blockSize := block.BlockSize()
	// 加密模式
	blockMode := cipher.NewCBCDecrypter(block, k[:blockSize])
	// 创建数组
	orig := make([]byte, len(crytedByte))
	// 解密
	blockMode.CryptBlocks(orig, crytedByte)
	// 去补全码
	orig = PKCS7UnPadding(orig)
	return string(orig)
}

// 补码
func PKCS7Padding(ciphertext []byte, blocksize int) []byte {
	padding := blocksize - len(ciphertext)%blocksize
	padtext := bytes.Repeat([]byte{byte(padding)}, padding)
	return append(ciphertext, padtext...)
}

// 去码
func PKCS7UnPadding(origData []byte) []byte {
	length := len(origData)
	unpadding := int(origData[length-1])
	return origData[:(length - unpadding)]
}

```

### dynamic_reverse
我是真没想到这道题只有5个解）
直接上源代码：
```cpp
#include <iostream>

void message()
{
	// mayctf{Reverse_It_Dynamically_IS_S1mple!}
	unsigned char buffer[] = 
	{
		0x1f, 0x13, 0x0b, 0x11, 0x06, 0x14, 0x09,
		0x20, 0x17, 0x04, 0x17, 0x00, 0x01, 0x17,
		0x2d, 0x3b, 0x06, 0x2d, 0x36, 0x0b, 0x1c,
		0x13, 0x1f, 0x1b, 0x11, 0x13, 0x1e, 0x1e,
		0x0b, 0x2d, 0x3b, 0x21, 0x2d, 0x21, 0x43,
		0x1f, 0x02, 0x1e, 0x17, 0x53, 0x0f, 0x72,
	};

	for (auto& ch : buffer)
		ch ^= 114;

	// std::cout << buffer << std::endl;
}

int main()
{
	std::cout << "Do you know how to get a dynamic flag?" << std::endl;

	message();

	return 0;
}
```
其实就是注释掉了输出，反编译打开`message`函数发现里面有乱七八糟的赋值，但是实际上IDA只是识别的有点问题，手动将`__int64 v2[5]`改成`char [42]`即可正常识别，而IDA反编译识别的不是很正常是因为编译器的优化，使用64位一组来进行了初始化。再异或解密输出即可。

```python
code = [
	0x1f, 0x13, 0x0b, 0x11, 0x06, 0x14, 0x09,
	0x20, 0x17, 0x04, 0x17, 0x00, 0x01, 0x17,
	0x2d, 0x3b, 0x06, 0x2d, 0x36, 0x0b, 0x1c,
	0x13, 0x1f, 0x1b, 0x11, 0x13, 0x1e, 0x1e,
	0x0b, 0x2d, 0x3b, 0x21, 0x2d, 0x21, 0x43,
	0x1f, 0x02, 0x1e, 0x17, 0x53, 0x0f, 0x72
]

ans = ''
for ch in code:
	ans += chr(ch ^ 114)
print(ans)

```

### native_android
发现调用了一个native的方法，直接用IDA打开lib文件找到对应的函数，发现实际上就是TEA算法。
```c
#include <stdio.h>

void decrypt(unsigned int* v, const unsigned int* k) 
{
	unsigned int v0 = v[0], v1 = v[1], sum = 0xc6ef3720, i;
	unsigned int delta = 0x9e3779b9;
	unsigned int k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
	for (i = 0; i < 32; i++)
	{
		v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
		v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		sum -= delta;                                   
	}
    v[0] = v0; v[1] = v1;
}

int main()
{
	unsigned char code[] = 
	{
		0xf0, 0x2e, 0xd2, 0x73, 0x04, 0xb6, 0x1a, 0xd3,
		0x59, 0xb2, 0xe3, 0x27, 0xa0, 0xda, 0x90, 0xd6,
		0xd2, 0x8c, 0x1c, 0x24, 0x00, 0xcb, 0x7e, 0x80,
		0x70, 0xf7, 0x35, 0xc2, 0x9d, 0x30, 0x3a, 0x3f,
		0x53, 0xb6, 0xf7, 0xbc, 0x29, 0x53, 0x5d, 0xec,
	};

	unsigned char key[] = 
	{
		0x40, 0x40, 0x6C, 0x67, 0x76, 0x6A, 0x6F, 0x63,
		0x57, 0x47, 0x6B, 0x7F, 0x3D, 0x7B, 0x6B, 0x2E
	};

	for (int i = 0; i < 16; ++i)
		key[i] ^= i;

	for (int i = 0; i < 40; i += 8)
		decrypt((unsigned int*)(code + i), (const unsigned int*)key);

	puts(code);

	return 0;
}
```

### hello_exception
`C++`的异常处理机制模板题，如果你把这道题做了那么团队赛的那道应该不会有什么问题（
手动将异常发生出改成jmp指令到对应的jmp块即可。
引发异常的地方用了一个初学者常见的问题，就是字符串只有39的长度，但是仍然访问了下标39，所以越界抛出异常）
然后真实的代码是一个简单的rot13旋转，rot13回来就行了。
源代码：
```cpp
#include <iostream>
#include <string>
#include <exception>

#include <cstring>

int main()
{
	std::string input;

	std::cin >> input;

	if (input.length() != 39)
	{
		std::cout << "Nonono!" << std::endl;
		return 1;
	}

	try
	{
		if (input.at(6) != '{' || input.at(39) != '}')
		{
			std::cout << "Nononono!" << std::endl;
			return 1;
		}

		for (auto& ch : input)
		{
			if (ch >= 'a' && ch <= 'z')
				ch = ch - 'a' + 'A';
			else if (ch >= 'A' && ch <= 'Z')
				ch = ch - 'A' + 'a';
		}

		if (input == "MAYCTF{A_rEaLlY_fAA@@@aaakkkkk_FLAG!!!}")
		{
			std::cout << "It's quite simple! isn't it?" << std::endl;
			return 2;
		}
	}
	catch (...)
	{
		if (!memcmp(input.c_str(), "mayctf{", 7) && input[38] == '}')
		{
			input = input.substr(7, 31);
			for (auto& ch : input)
			{
				if (ch >= 'a' && ch <= 'z')
					ch = (ch - 'a' + 13) % 26 + 'a';
				else if (ch >= 'A' && ch <= 'Z')
					ch = (ch - 'A' + 13) % 26 + 'A';
			}

			unsigned char secret[] =
			{
				0x4C, 0x31, 0x6A, 0x66, 0x5B, 0x56, 0x70, 0x62,
				0x6E, 0x6E, 0x55, 0x59, 0x67, 0x7D, 0x3D, 0x6C,
				0x77, 0x20, 0x70, 0x72, 0x4B, 0x5B, 0x77, 0x79,
				0x61, 0x75, 0x7C, 0x69, 0x3D, 0x3C, 0x3F
			};

			for (int i = 0; i < 31; ++i)
				secret[i] ^= i;

			// Correct
			if (input == (const char*)secret)
			{
				putchar('C');
				putchar('o');
				putchar('n');
				putchar('g');
				putchar('r');
				putchar('a');
				putchar('t');
				putchar('u');
				putchar('l');
				putchar('a');
				putchar('t');
				putchar('i');
				putchar('o');
				putchar('n');
				putchar('s');
				putchar('!');
				putchar('\n');
				return 0;
			}
		}
	}

	std::cout << "Nono!" << std::endl;
	return 1;
}
```
求解代码：
```python
secrets = list(b'L1jf[VpbnnUYg}=lw prK[wyau|i=<?')

for i in range(len(secrets)):
	secrets[i] ^= i

def rot13(ch):
	if ch >= ord('A') and ch <= ord('Z'):
		return (ch - ord('A') + 13) % 26 + ord('A')
	elif ch >= ord('a') and ch <= ord('z'):
		return (ch - ord('a') + 13) % 26 + ord('a')
	else:
		return ch

ans = ''
for ch in secrets:
	ans += chr(rot13(ch))

print('mayctf{' + ans + '}')
```

### threads
先上源码：
```cpp
#include <Windows.h>

#include <iostream>

#include "sha256.h"

HANDLE hMutex;
HANDLE hThread1, hThread2;
std::string Input;
int DecodeCounter = 92;

// mayctf{It's_just@A_verrrrrrrry_s1mple_multiThr#ad_stuff_89EC1FBD-14ED-4DF3-93A3-91ED11A36956}
void Do_Input()
{
	Input.reserve(100);
	std::cout << "Please input your flag:" << std::endl;
	std::cin >> Input;
}

void rot13(char& ch)
{
	if (ch >= 'a' && ch <= 'z')
		ch = (ch - 'a' + 13) % 26 + 'a';
	else if (ch >= 'A' && ch <= 'Z')
		ch = (ch - 'A' + 13) % 26 + 'A';
}

void xor_idx(char& ch)
{
	ch ^= DecodeCounter;
}

DWORD WINAPI Thread1Proc(LPVOID lpThreadParameter)
{
	while (true)
	{
		WaitForSingleObject(hMutex, -1);
		if (DecodeCounter > -1)
		{
			rot13(Input[DecodeCounter]);
			--DecodeCounter;
			Sleep(100);
		}
		ReleaseMutex(hMutex);
	}
}

DWORD WINAPI Thread2Proc(LPVOID lpThreadParameter)
{
	while (true)
	{
		WaitForSingleObject(hMutex, -1);
		if (DecodeCounter > -1)
		{
			xor_idx(Input[DecodeCounter]);
			--DecodeCounter;
			Sleep(100);
		}
		ReleaseMutex(::hMutex);
	}
}

std::string Get_SHA256(const std::string& str)
{
	SHA256 engine;
	engine.update(str);
	auto ptr = engine.digest();
	auto ret = engine.toString(ptr);
	delete[] ptr;
	return ret;
}

bool Verify_SHA256(const std::string& str, const char* sha)
{
	return Get_SHA256(str) == sha;
}

void Do_Validation()
{
	unsigned char answer_buffer[] =
	{
		0x7A, 0x60, 0x6C, 0x60, 0x67, 0x63, 0x7B, 0x4E,
		0x67, 0x2E, 0x66, 0x54, 0x77, 0x78, 0x66, 0x7B, 
		0x40, 0x50, 0x5F, 0x65, 0x72, 0x67, 0x65, 0x65, 
		0x65, 0x6B, 0x65, 0x69, 0x65, 0x64, 0x5F, 0x6C,
		0x31, 0x4C, 0x63, 0x4F, 0x72, 0x7A, 0x7A, 0x52, 
		0x79, 0x5D, 0x76, 0x7F, 0x75, 0x5F, 0x23, 0x4E,
		0x71, 0x6E, 0x66, 0x47, 0x68, 0x53, 0x73, 0x68,
		0x38, 0x00, 0x52, 0x78, 0x31, 0x7B, 0x4F, 0x7B, 
		0x2D, 0x70, 0x34, 0x06, 0x51, 0x68, 0x34, 0x03, 
		0x53, 0x7A, 0x2D, 0x72, 0x33, 0x0C, 0x33, 0x62,
		0x39, 0x60, 0x52, 0x17, 0x31, 0x64, 0x4E, 0x64, 
		0x36, 0x60, 0x35, 0x6D, 0x7D,
	};

	std::string s1;
	s1.resize(93);
	memcpy(&s1[0], answer_buffer, 93);

	if (Get_SHA256(s1) == Get_SHA256(Input))
		std::cout << "You really understand multi thread!" << std::endl;
	else
		std::cout << "Seems you cannot understand the multithread processing yet..." << std::endl;
}

int main()
{
	Do_Input();

	__try
	{
		// fake
		if (Input.length() == 93 && Verify_SHA256(Input, "2d63e6d0cb4305c91eac80e666c5f6a4b3a8ff8d08e555228ec74e10245b12c8"))
			printf("You have passed the verification!\n");
		else
		{
			char ch = Input.front();
			ch ^= ch;
			ch /= ch;
			for (auto& t : Input)
				t ^= ch;
			printf("You haven't pass the verification!\n");
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		hMutex = CreateMutex(nullptr, NULL, TEXT("secsome's lovely mutex"));
		if (NULL == hMutex)
		{
			printf("Failed to set-up the mutex!\n");
			return 1;
		}

		hThread1 = CreateThread(nullptr, NULL, Thread1Proc, nullptr, NULL, NULL);
		if (NULL == hThread1)
		{
			printf("Failed to start Thread1Proc!\n");
			return 1;
		}

		hThread2 = CreateThread(nullptr, NULL, Thread2Proc, nullptr, NULL, NULL);
		if (NULL == hThread2)
		{
			printf("Failed to start Thread2Proc!\n");
			return 1;
		}

		CloseHandle(hThread1);
		CloseHandle(hThread2);

		while (DecodeCounter != -1)
			;

		CloseHandle(hMutex);

		Do_Validation();
	}
	return 0;
}

```
跟上道题一样，首先套了一个异常的壳子，但是这次用的是除0异常，配合Windows的SEH异常处理。
同样修成一个jmp指令到except块即可。

来到实际逻辑，程序创建了两个线程，并且通过一个互斥体使其交替进行。故最终奇数和偶数下标分别跑异或和rot13操作，分别解密即可。最终的验证用了`sha256`的结果进行比对，实际上作用就是一个`strcmp`，只是用来干扰分析罢了。可以通过算法的初始化特征值看出）

附求解代码：
```python
code = [0x7A, 0x60, 0x6C, 0x60, 0x67, 0x63, 0x7B, 0x4E,
		0x67, 0x2E, 0x66, 0x54, 0x77, 0x78, 0x66, 0x7B, 
		0x40, 0x50, 0x5F, 0x65, 0x72, 0x67, 0x65, 0x65, 
		0x65, 0x6B, 0x65, 0x69, 0x65, 0x64, 0x5F, 0x6C,
		0x31, 0x4C, 0x63, 0x4F, 0x72, 0x7A, 0x7A, 0x52, 
		0x79, 0x5D, 0x76, 0x7F, 0x75, 0x5F, 0x23, 0x4E,
		0x71, 0x6E, 0x66, 0x47, 0x68, 0x53, 0x73, 0x68,
		0x38, 0x00, 0x52, 0x78, 0x31, 0x7B, 0x4F, 0x7B, 
		0x2D, 0x70, 0x34, 0x06, 0x51, 0x68, 0x34, 0x03, 
		0x53, 0x7A, 0x2D, 0x72, 0x33, 0x0C, 0x33, 0x62,
		0x39, 0x60, 0x52, 0x17, 0x31, 0x64, 0x4E, 0x64, 
		0x36, 0x60, 0x35, 0x6D, 0x7D]

ans = ''

for i in range(len(code)):
	if i % 2 == 1:
		ans += chr(code[i] ^ i)
	else:
		ch = code[i]
		if ch >= ord('a') and ch <= ord('z'):
			ans += chr((ch - ord('a') + 13) % 26 + ord('a'))
		elif ch >= ord('A') and ch <= ord('Z'):
			ans += chr((ch - ord('A') + 13) % 26 + ord('A'))
		else:
			ans += chr(ch)

print(ans)

```

### bocchi_the_rock!
这道题是我当时看了**孤独摇滚！**第四集后当场去出的题，因为发现自己把个人赛当成只有五天了赶紧去补的题目）

这道题用了imgui框架，担心大家被无用的框架代码干扰我直接就把debug和release版本的二进制文件都上传了其实。

结合`Some secret is hidden in the color changes...`与10轮base64解码的结果`The flag is hidden in the colors`与题目提示，我们其实可以猜到这道题跟背景色的变化有关，查看相关代码发现有一个
```cpp
g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
```
的操作，这个API的作用其实在微软的文档是查得到的，就是用指定的颜色去填充这个view，对`clear_color_with_alpha`按X找交叉引用找到赋值的地方，跟踪到一个数组：
```cpp
    static ImVec4 colors[6] = 
    {
        { 0.384314, 0.435294, 0.388235, 0.388235 },
        { 0.407843, 0.411765, 0.372549, 0.388235 },
        { 0.407843, 0.380392, 0.431373, 0.372549 },
        { 0.411765, 0.450980, 0.372549, 0.450980 },
        { 0.435294, 0.372549, 0.419608, 0.380392 },
        { 0.466667, 0.380392, 0.411765, 0.411765 }
    };
```
`ImVec4`实际上就是`float[4]`，我们因此结合提示，这些颜色分量其实应该都是[0, 255]映射过来的，还原即可。

求解代码如下：
```c
#include <stdio.h>

int main()
{
	float colors[6][4] = 
    {
        { 0.384314, 0.435294, 0.388235, 0.388235 },
        { 0.407843, 0.411765, 0.372549, 0.388235 },
        { 0.407843, 0.380392, 0.431373, 0.372549 },
        { 0.411765, 0.450980, 0.372549, 0.450980 },
        { 0.435294, 0.372549, 0.419608, 0.380392 },
        { 0.466667, 0.380392, 0.411765, 0.411765 }
    };

	printf("mayctf{");
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 4; ++j)
			printf("%c", (char)(colors[i][j] * 255 + 0.5));
	}
	printf("}\n");

	return 0;
}

```
把拿到的flag丢尽程序发现能正确通过第一步的验证，提交就行。

## 团队赛

乐，加起来一共就一道题有一个解。
按照上题顺序讲了。

### baby_nvidia
这道题是我预想的零解题目，事实上真的零解了。
要跑程序首先你要有一个支持`CUDA`的GPU。

先看源码：
```cpp
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <cstdio>
#include <cstdlib>  // exit
#include <cstring>  // memcmp
#include <cstdint>  // uint32_t
#include <string>   // std::string
#include <iostream> // std::cout

#define NV_FAILED(status) (status != cudaSuccess)
#define NV_SHOWERR(status) std::cout << "Possible reason: " << cudaGetErrorString(status) << std::endl

#ifdef _MSC_VER
#define NV_INLINE __forceinline
#else
#define NV_INLINE inline
#endif

__global__ void encrypt(uint32_t* v, uint32_t* k) 
{
    v += threadIdx.x * 2;
    uint32_t v0 = v[0], v1 = v[1], sum = 0, i;
    uint32_t delta = 0x9e3779b9;
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 18; i++) {
        sum += delta;
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    }
    v[0] = v0; v[1] = v1;
}

uint32_t* g_v = nullptr;
uint32_t* g_k = nullptr;

NV_INLINE void deallocMemory()
{
    if (g_k)
        cudaFree(g_k);
    if (g_v)
        cudaFree(g_v);
}
NV_INLINE void myExit(int exitCode)
{
    deallocMemory();
    exit(exitCode);
}
NV_INLINE void initDevice()
{
    cudaError_t status;
    
    int cudaDeviceCount;
    status = cudaGetDeviceCount(&cudaDeviceCount);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to get GPU count!" << std::endl;
        NV_SHOWERR(status);
        myExit(1);
    }

    if (cudaDeviceCount < 1)
    {
        std::cout << "Failed to find an available GPU! This program requires at least one GPU support CUDA!" << std::endl;
        NV_SHOWERR(status);
        myExit(1);
    }

    const int deviceId = cudaDeviceCount - 1;

    status = cudaSetDevice(deviceId);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to select a GPU!" << std::endl;
        NV_SHOWERR(status);
        myExit(1);
    }

    cudaDeviceProp prop;
    status = cudaGetDeviceProperties(&prop, deviceId);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to get GPU property!" << std::endl;
        NV_SHOWERR(status);
        myExit(1);
    }
    std::cout << "Successfully select GPU: " << prop.name << std::endl;
}
NV_INLINE bool checkFormat(std::string& s)
{
    if (s.length() != 32)
        return false;

    if (0 != memcmp("MAYCTF{", s.c_str(), 7))
        return false;

    if (s.back() != '}')
        return false;

    return true;
}
NV_INLINE void initMemory(const char* flag)
{
    cudaError_t status;

    status = cudaMalloc(&g_v, 32);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to malloc memory for g_v!" << std::endl;
        NV_SHOWERR(status);
        myExit(2);
    }
    
    status = cudaMalloc(&g_k, 16);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to malloc memory for g_k!" << std::endl;
        NV_SHOWERR(status);
        myExit(2);
    }

    status = cudaMemcpy(g_v, flag, 32, cudaMemcpyHostToDevice);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to copy data to g_v!" << std::endl;
        NV_SHOWERR(status);
        myExit(2);
    }

    constexpr char key[] = "MAYCTF_REV_CUDA!";
    status = cudaMemcpy(g_k, key, 16, cudaMemcpyHostToDevice);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to copy data to g_k!" << std::endl;
        NV_SHOWERR(status);
        myExit(2);
    }
}
NV_INLINE void executeEncrypt(unsigned char sn[])
{
    cudaError_t status;

    encrypt<<<1, 4>>>(g_v, g_k);
    status = cudaGetLastError();
    if (NV_FAILED(status))
    {
        std::cout << "Failed to verify data!" << std::endl;
        NV_SHOWERR(status);
        myExit(3);
    }

    status = cudaDeviceSynchronize();
    if (NV_FAILED(status))
    {
        std::cout << "Failed to call cudaDeviceSynchronize!" << std::endl;
        NV_SHOWERR(status);
        myExit(3);
    }
    
    status = cudaMemcpy(sn, g_v, 32, cudaMemcpyDeviceToHost);
    if (NV_FAILED(status))
    {
        std::cout << "Failed to copy data back to host!" << std::endl;
        NV_SHOWERR(status);
        myExit(3);
    }
}
NV_INLINE bool checkAnswer(unsigned char sn[])
{
    unsigned char ans[32] =
    {
        0xef, 0x6e, 0xec, 0x60, 0xeb, 0x84, 0x92, 0x00,
        0x42, 0x2f, 0x1a, 0x22, 0x20, 0xb2, 0xb4, 0x83,
        0xa1, 0xe8, 0x61, 0x06, 0xb3, 0x76, 0xaf, 0x8d,
        0xc4, 0x8f, 0x55, 0x8c, 0xc8, 0x71, 0x9b, 0x86,
    };

    return 0 == memcmp(sn, ans, 32);
}

// modified TEA-Encrypt which only has 18 rounds
// key = MAYCTF_REV_CUDA!
// flag = MAYCTF{NviDiA_CuDA_GPU_ProGrAm!}
int main()
{
    std::cout << "Initializing device..." << std::endl;
    initDevice();
    
    std::cout << "Please input your flag:" << std::endl;
    std::string flag;
    std::cin >> flag;
    if (!checkFormat(flag))
    {
        std::cout << "You don't understand Reverse of course!" << std::endl;
        myExit(114514);
    }

    std::cout << "Hold on! I'm verifying your flag...";
    initMemory(flag.c_str());

    unsigned char sn[32] = { 0 };
    executeEncrypt(sn);
    std::cout << " Done.\n" << std::endl;

    if (checkAnswer(sn))
        std::cout << "You are really good at cuda reverse!" << std::endl;
    else
        std::cout << "Seems you cannot fully understand what cuda had done!" << std::endl;

#ifdef _MSC_VER
    system("pause");
#endif

    myExit(0);
}
```

嗯，实际上真的就是一个套了壳子的魔改tea算法。

难点在于如何解析英伟达的那套opcode，实际上我们有`nvdisasm`工具，可以得到ptx文件，再结合ptx文件与其中的左移右移就能发现是tea，注意要找到只有18轮（

求解代码：
```c
#include <stdio.h>

void decrypt(unsigned int* v, const unsigned int* k) 
{
    unsigned int v0 = v[0], v1 = v[1], sum = 0x1fe68f02, i;
    unsigned int delta = 0x9e3779b9;
    unsigned int k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 18; i++)
	{
		v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
		v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		sum -= delta;                                   
    }
    v[0] = v0; v[1] = v1;
}

int main()
{
	unsigned char code[] = 
	{
		0xef, 0x6e, 0xec, 0x60, 0xeb, 0x84, 0x92, 0x00,
        0x42, 0x2f, 0x1a, 0x22, 0x20, 0xb2, 0xb4, 0x83,
        0xa1, 0xe8, 0x61, 0x06, 0xb3, 0x76, 0xaf, 0x8d,
        0xc4, 0x8f, 0x55, 0x8c, 0xc8, 0x71, 0x9b, 0x86,
	};

	for (int i = 0; i < 32; i += 8)
		decrypt((unsigned int*)(code + i), (const unsigned int*)"MAYCTF_REV_CUDA!");

	puts(code);

	return 0;
}
```

### baby_smoke

这道题是我预想的整活题，结果成了烂活了这下。

源代码：
```cpp
#include <Windows.h>
#include <bcrypt.h>
#include <iostream>

// https://learn.microsoft.com/zh-cn/windows/win32/seccng/creating-a-hash-with-cng
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define NT_FAILED(Status) (!NT_SUCCESS(Status))
#define STATUS_UNSUCCESSFUL ((NTSTATUS)0xC0000001L)
#pragma comment(lib, "Bcrypt.lib")

std::string CalculateHash(const std::string& src, LPCWSTR mode)
{
	BCRYPT_ALG_HANDLE       hAlg            = NULL;
    BCRYPT_HASH_HANDLE      hHash           = NULL;
    NTSTATUS                status          = STATUS_UNSUCCESSFUL;
    DWORD                   cbData          = 0,
                            cbHash          = 0,
                            cbHashObject    = 0;
    PBYTE                   pbHashObject    = NULL;
    PBYTE                   pbHash          = NULL;

	//open an algorithm handle
    status = BCryptOpenAlgorithmProvider(&hAlg, mode, NULL, NULL);
	if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", status);
        goto Cleanup;
    }

    //calculate the size of the buffer to hold the hash object
	status = BCryptGetProperty(hAlg, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbHashObject, sizeof(DWORD), &cbData, NULL);
    if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
        goto Cleanup;
    }

    //allocate the hash object on the heap
    pbHashObject = (PBYTE)HeapAlloc(GetProcessHeap(), NULL, cbHashObject);
    if (NULL == pbHashObject)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;
    }

    //calculate the length of the hash
    status = BCryptGetProperty(hAlg, BCRYPT_HASH_LENGTH, (PBYTE)&cbHash, sizeof(DWORD), &cbData, 0);
	if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
        goto Cleanup;
    }

    //allocate the hash buffer on the heap
    pbHash = (PBYTE)HeapAlloc(GetProcessHeap(), NULL, cbHash);
    if (NULL == pbHash)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;
    }

    //create a hash
	status = BCryptCreateHash(hAlg, &hHash, pbHashObject, cbHashObject, NULL, NULL, NULL);
    if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptCreateHash\n", status);
        goto Cleanup;
    }

    //hash some data
	status = BCryptHashData(hHash, (PBYTE)src.c_str(), src.length(), NULL);
    if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptHashData\n", status);
        goto Cleanup;
    }
    
    //close the hash
	status = BCryptFinishHash(hHash, pbHash, cbHash, NULL);
    if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptFinishHash\n", status);
        goto Cleanup;
    }

Cleanup:
	std::string result;
	if (pbHash)
	{
		result.resize(cbHash * 2);
		for (size_t i = 0; i < cbHash; ++i)
			sprintf(&result[i * 2], "%02x", pbHash[i]);
		HeapFree(GetProcessHeap(), 0, pbHash);
	}
    if (hAlg)
        BCryptCloseAlgorithmProvider(hAlg, 0);
    if (hHash)    
        BCryptDestroyHash(hHash);
    if (pbHashObject)
        HeapFree(GetProcessHeap(), 0, pbHashObject);

	return result;
}

std::string DecodeData(LPVOID lpData, DWORD dwSize, const std::string& key)
{
	std::string result;
	result.resize(dwSize);
	auto pData = reinterpret_cast<char*>(lpData);	
	
	for (DWORD i = 0; i < dwSize; ++i)
		result[i] = pData[i] ^ key[i % key.length()];
	
	return result;
}

bool GenerateRTFFile(const std::string& key)
{
	HRSRC hResInfo = FindResourceA(NULL, MAKEINTRESOURCEA(1919), MAKEINTRESOURCEA(810));
	if (NULL == hResInfo)
		return false;

	DWORD dwSize = SizeofResource(NULL, hResInfo);
	if (NULL == dwSize)
		return false;

	HGLOBAL hResData = LoadResource(NULL, hResInfo);
	if (NULL == hResData)
		return false;

	LPVOID lpData = LockResource(hResData);
	if (nullptr == lpData)
		return false;

	const auto data = DecodeData(lpData, dwSize, key);

	DeleteFileA("litang.rtf");
	HANDLE hFile = CreateFileA("litang.rtf", GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return false;

	if (FALSE == WriteFile(hFile, data.c_str(), dwSize, nullptr, nullptr))
		return false;

	CloseHandle(hFile);
	return true;
}

int main()
{
	std::string passwd1, passwd2;

	std::cout << "Please input password 1:" << std::endl;
	std::cin >> passwd1;
	if (passwd1.length() != 6)
	{
		std::cout << "Must be 6 characters!" << std::endl;
		return 0;
	}
	for (const auto& ch : passwd1)
	{
		if (ch >= 'a' && ch <= 'z')
			continue;
		std::cout << "Wrong!" << std::endl;
		return 0;
	}

	if (CalculateHash(passwd1 + "@LiTang-DingZhen", BCRYPT_SHA256_ALGORITHM) != "b9abee92a7fbd5e305615890183e90b9126be0040065f96dc2daa1b579f4c278")
		return 0;

	std::cout << "Please input password 2:" << std::endl;
	std::cin >> passwd2;
	if (passwd2.length() != 6)
	{
		std::cout << "Must be 6 characters!" << std::endl;
		return 0;
	}

	if (CalculateHash(passwd2 + passwd1 + "@LiTang-DingZhen", BCRYPT_MD5_ALGORITHM) != "fa81569f626defaa5fe6ab52e8fa2361")
		return 0;

	std::cout << passwd2 + passwd1 + "@LiTang-DingZhen" << std::endl;
	if (GenerateRTFFile(passwd2 + passwd1 + "@LiTang-DingZhen"))
		std::cout << "Done!" << std::endl;
	else
		std::cout << "Something is wrong!" << std::endl;

	return 0;
}

```

首先IDA打开，发现程序要用到两个6位的password，而第一个password由于强制了纯小写字母，直接暴力枚举就行，比对到SHA256校验通过即可。
对了这道题的哈希函数都是用的`WINAPI`提供的函数，直接在`MSDN`上面可以找到详细信息。
对于第二个密码我们暴力破解也能做出，但是时间成本较高。实际上结合生成的文件是rtf，与哈希解密中的操作，而rtf文件的前六位是确定的，直接反过来异或就能得到结果，

输入两个密码后程序会生成一个rtf文件。
其中隐藏了三段颜色被我专门调成背景色的文字，直接改一下颜色就行：
```
Flag starts with MAYCTF
flag part 1:{Cheese_Snow_Leop@rd,
Flag part 2:My_Animal_Fie3nds!}
```

### baby_vm

这道题如描述所说，是我上**社会计算**课闲得实在无聊出的。
如题目所说，这道题就是一个虚拟机，我手写的。

直接分析那个switch，把对应的每一步搞清楚在干啥即可。发现最后又双叒是一个TEA，乐了。
```cpp
// vm.hpp
#ifndef _MAYCTF_BABYVM_VM_HPP
#define _MAYCTF_BABYVM_VM_HPP

#include <string_view>

using UInt32 = unsigned int;
using Register32 = UInt32;
using Address = UInt32;

enum VMOpcode : UInt32
{
	VM_EXIT,
	VM_NOP,
	VM_SETREG,
	VM_MOVREG,
	VM_SHOWSTR,
	VM_TEA,
	VM_TEA_ENCRYPT = 0,
	VM_TEA_DECRYPT = 1,
	VM_PUSH = VM_TEA + 1,
	VM_POP,
	VM_ADD,
	VM_READSTR,
	VM_INSTCOUNT
};

enum RegisterID : UInt32
{
	REG_EAX = 0,
	REG_EBX,
	REG_ECX,
	REG_EDX,
	REG_ESI,
	REG_EDI,
	REG_EBP,
	REG_ESP,
	REG_EIP,
	REG_COUNT
};

struct Registers
{
	Register32 EAX;
	Register32 EBX;
	Register32 ECX;
	Register32 EDX;
	Register32 ESI;
	Register32 EDI;
	Register32 EBP;
	Register32 ESP;
	Register32 EIP;
};

class VirtualMachine final
{
public:
	explicit VirtualMachine(UInt32* codedata, UInt32 eip) noexcept;
	virtual ~VirtualMachine();

	int run();

private:
	template<typename T = UInt32>
	T next_data()
	{
		return static_cast<T>(CodeDatas[RegisterDatas.Single.EIP++]);
	}

	RegisterID next_register_id();
	Register32& next_register();

	void push(UInt32 x);
	UInt32 pop();
	
	void throw_exception(const std::string_view sv);

	static constexpr UInt32 StackBufferSize = 0x20000;
	unsigned char StackBuffer[StackBufferSize];

	union
	{
		Registers Single;
		Register32 Array[REG_COUNT];
	} RegisterDatas;

	UInt32* CodeDatas;
};

static_assert(sizeof(UInt32) == 4, "sizeof UInt32 must to be 4!");
static_assert(sizeof(size_t) == 4, "This program need to be compiled under x86 mode!");

#endif // _MAYCTF_BABYVM_VM_HPP
```

```cpp
// vm.cpp
#include "vm.hpp"

#include <iostream>
#include <string>
#include <cstring>

VirtualMachine::VirtualMachine(UInt32* codedata, UInt32 eip) noexcept
	: StackBuffer{ 0 }
{
	CodeDatas = codedata;
	RegisterDatas.Single.ESP = RegisterDatas.Single.EBP = StackBufferSize / 2;
	RegisterDatas.Single.EAX = RegisterDatas.Single.EBX =
	RegisterDatas.Single.ECX = RegisterDatas.Single.EDX =
	RegisterDatas.Single.ESI = RegisterDatas.Single.EDI = 0;
	RegisterDatas.Single.EIP = eip;
}

VirtualMachine::~VirtualMachine()
{	
}

RegisterID VirtualMachine::next_register_id()
{
	return next_data<RegisterID>();
}

Register32& VirtualMachine::next_register()
{
	return RegisterDatas.Array[next_register_id()];
}

void VirtualMachine::push(UInt32 x)
{
	*reinterpret_cast<UInt32*>(StackBuffer + RegisterDatas.Single.ESP) = x;
	RegisterDatas.Single.ESP += sizeof(UInt32);
}

UInt32 VirtualMachine::pop()
{
	RegisterDatas.Single.ESP -= sizeof(UInt32);
	return *reinterpret_cast<UInt32*>(StackBuffer + RegisterDatas.Single.ESP);
}

void VirtualMachine::throw_exception(const std::string_view sv)
{
	std::cout << sv;
}

int VirtualMachine::run()
{
	do 
	{
		switch(next_data())
		{
			case VM_EXIT:
			{
				return RegisterDatas.Single.EAX;
			}
			case VM_NOP:
			{
				continue;
			}
			case VM_SETREG:
			{
				auto& reg = next_register();
				reg = next_data();
				continue;
			}
			case VM_MOVREG:
			{
				auto& dst = next_register();
				auto& src = next_register();
				dst = src;
				continue;
			}
			case VM_SHOWSTR:
			{
				std::cout << reinterpret_cast<char*>(next_register());
				continue;
			}
			case VM_TEA:
			{
				bool is_decrypt = next_data<bool>();
				UInt32* v = reinterpret_cast<UInt32*>(next_register());
				UInt32* k = reinterpret_cast<UInt32*>(next_register());

				auto encrypt = [](UInt32* v, UInt32* k) {
    				UInt32 v0=v[0], v1=v[1], sum=0, i;           /* set up */
    				UInt32 delta=0x9e3779b9;                     /* a key schedule constant */
    				UInt32 k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    				for (i=0; i < 32; i++) {                       /* basic cycle start */
    				    sum += delta;
    				    v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
    				    v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
    				}                                              /* end cycle */
    				v[0]=v0; v[1]=v1;
				};

				auto decrypt = [](UInt32* v, UInt32* k) {
				    UInt32 v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up */
				    UInt32 delta=0x9e3779b9;                     /* a key schedule constant */
				    UInt32 k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
				    for (i=0; i<32; i++) {                         /* basic cycle start */
				        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
				        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
				        sum -= delta;                                   
				    }                                              /* end cycle */
				    v[0]=v0; v[1]=v1;
				};

				if (is_decrypt) 
					decrypt(v, k);
				else
					encrypt(v, k);

				continue;
			}
			case VM_PUSH:
			{
				push(next_register());
				continue;
			}
			case VM_POP:
			{
				next_register() = pop();
				continue;
			}
			case VM_ADD:
			{
				auto& dst = next_register();
				auto& delta = next_register();
				dst += delta;
				continue;
			}
			case VM_READSTR:
			{
				char* buffer = reinterpret_cast<char*>(next_register());
				std::string tmp; 
				std::cin >> tmp; 
				tmp.resize(next_register());
				memcpy(buffer, tmp.c_str(), tmp.size());
				continue;
			}

			default:
			{
				throw_exception("secsome's super PC cannot recognize this byte code!\n");
				return 1;
			}
		}
	} while(true);
}

```

```cpp
// baby_vm.cpp
#include "vm.hpp"

#include <iostream>
#include <memory>

#include <cstring>

template<typename T>
constexpr UInt32 To_Inst(T&& x)
{
	return UInt32(x);
}

const char* key1 = "It's 07:55 a.m.!\n";
const char* key2 = "Almost 23:55 now\n";

const char* welcome_msg = "Welcome to secsome's super computer!\n";

char data1[25] = {0};
char data2[25] = {0};

UInt32 VMCodeDatas[] =
{
	VM_NOP,
	
	// showstr(welcome_msg)
	VM_SETREG, REG_EAX, To_Inst(welcome_msg),
	VM_SHOWSTR, REG_EAX,

	// mov edi, key1
	// push key2
	VM_SETREG, REG_EAX, To_Inst(key1),
	VM_SETREG, REG_EBX, To_Inst(key2),
	VM_PUSH, REG_EAX,
	VM_PUSH, REG_EBX,
	VM_POP, REG_ESI,
	VM_POP, REG_EDI,
	VM_PUSH, REG_ESI,
	
	// mov ecx, data1
	// mov edx, data2
	// push data2
	VM_SETREG, REG_ECX, To_Inst(data1),
	VM_SETREG, REG_EDX, To_Inst(data2),
	VM_PUSH, REG_EDX,

	// showstr(key1)
	VM_SHOWSTR, REG_EDI,

	// readstr(data1, 24)
	VM_SETREG, REG_EAX, 24,
	VM_READSTR, REG_ECX, REG_EAX,

	// tea_encrypt(data1, key1)
	// tea_encrypt(data1 + 8, key1)
	// tea_encrypt(data1 + 16, key1)
	VM_TEA, VM_TEA_ENCRYPT, REG_ECX, REG_EDI,
	VM_SETREG, REG_ESI, 8,
	VM_ADD, REG_ECX, REG_ESI,
	VM_TEA, VM_TEA_ENCRYPT, REG_ECX, REG_EDI,
	VM_ADD, REG_ECX, REG_ESI,
	VM_TEA, VM_TEA_ENCRYPT, REG_ECX, REG_EDI,

	// eax : data2
	// ebx : key2
	VM_POP, REG_EAX,
	VM_POP, REG_EBX,

	// showstr(key2)
	VM_SHOWSTR, REG_EBX,

	// readstr(data2, 24)
	VM_SETREG, REG_EDX, 24,
	VM_READSTR, REG_EAX, REG_EDX,

	// tea_decrypt(data2, key2)
	// tea_decrypt(data2 + 8, key2)
	// tea_decrypt(data2 + 16, key2)
	VM_TEA, VM_TEA_DECRYPT, REG_EAX, REG_EBX,  
	VM_SETREG, REG_ECX, 8,
	VM_ADD, REG_EAX, REG_ECX,
	VM_TEA, VM_TEA_DECRYPT, REG_EAX, REG_EBX,
	VM_ADD, REG_EAX, REG_ECX,
	VM_TEA, VM_TEA_DECRYPT, REG_EAX, REG_EBX,
	
	// return 0
	VM_SETREG, REG_EAX, 0,
	VM_EXIT,
};

int main()
{
	int result = std::make_unique<VirtualMachine>(VMCodeDatas, 0)->run();

	if (result) {
		std::cout << "Do not modify my super computer!" << std::endl;
		return 0;
	}

	// mayctf{I_@m_Sleeeeeepy!I_aM_Always_V3ry_Sl33py!}
	// first 24 bytes decoded by "It's 07:55 a.m.!"
	// later 24 bytes encoded by "Almost 23:55 now"

	unsigned char ans1[] = 
	{
		0xd1, 0x77, 0xdc, 0xfb, 0xe9, 0xd5, 0xce, 0xfd,
		0x02, 0x1a, 0xbc, 0xc7, 0x86, 0x00, 0x01, 0x6b,
		0x5d, 0xad, 0xc0, 0x4a, 0x57, 0xa8, 0xf2, 0x2e,
	};

	unsigned char ans2[] = 
	{
		0xd4, 0xef, 0xa1, 0xa1, 0x45, 0x1f, 0x6e, 0xa0,
		0xe5, 0xf5, 0xc6, 0xe7, 0x89, 0x66, 0x8c, 0xdd,
		0xaf, 0xf2, 0x73, 0x59, 0x3f, 0x79, 0x8c, 0x82,
	};

	if (!memcmp(ans1, data1, sizeof(ans1)) && !memcmp(ans2, data2, sizeof(ans2)))
		std::cout << "Congratulations!" << std::endl;
	else
		std::cout << "It's not too simple... Be patient!" << std::endl;

	return 0;
}
```

代码写的挺烂的，别骂我（
附求解代码：
```c
#include <stdio.h>

const char* key1 = "It's 07:55 a.m.!";
const char* key2 = "Almost 23:55 now";

unsigned char ans1[] = 
{
	0xd1, 0x77, 0xdc, 0xfb, 0xe9, 0xd5, 0xce, 0xfd,
	0x02, 0x1a, 0xbc, 0xc7, 0x86, 0x00, 0x01, 0x6b,
	0x5d, 0xad, 0xc0, 0x4a, 0x57, 0xa8, 0xf2, 0x2e,
	0
};

unsigned char ans2[] = 
{
	0xd4, 0xef, 0xa1, 0xa1, 0x45, 0x1f, 0x6e, 0xa0,
	0xe5, 0xf5, 0xc6, 0xe7, 0x89, 0x66, 0x8c, 0xdd,
	0xaf, 0xf2, 0x73, 0x59, 0x3f, 0x79, 0x8c, 0x82,
	0
};

void encrypt(unsigned int* v, const unsigned int* k) 
{
    unsigned int v0 = v[0], v1 = v[1], sum = 0, i;
    unsigned int delta = 0x9e3779b9;
    unsigned int k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 32; i++)
	{
		sum += delta;  
		v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);                                 
    }
    v[0] = v0; v[1] = v1;
}

void decrypt(unsigned int* v, const unsigned int* k) 
{
    unsigned int v0 = v[0], v1 = v[1], sum = 0xc6ef3720, i;
    unsigned int delta = 0x9e3779b9;
    unsigned int k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 32; i++)
	{
		v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
		v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		sum -= delta;                                   
    }
    v[0] = v0; v[1] = v1;
}

int main()
{
	for (int i = 0; i < 24; i += 8)
		decrypt((unsigned int*)(ans1 + i), (const unsigned int*)key1);
	for (int i = 0; i < 24; i += 8)
		encrypt((unsigned int*)(ans2 + i), (const unsigned int*)key2);

	printf("%s%s\n", ans1, ans2);

	return 0;
}
```

### baby_exception

唯一有解的题目，泪目了
与个人赛的那道题类似，只不过加密用的是换表base64罢了。

直接上源代码：
```cpp
#include <iostream>
#include <string>
#include <exception>

#include <cstring>
#include <cstdlib>

std::string b64encode(const std::string& src)
{
	constexpr auto _encoder = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	constexpr auto _pad = '=';
	constexpr auto PacketChars = 4;
	union PacketType
	{
		struct
		{
			unsigned char C3;
			unsigned char C2;
			unsigned char C1;
			unsigned char pad;
		} Char;
		struct
		{
			unsigned O4 : 6;
			unsigned O3 : 6;
			unsigned O2 : 6;
			unsigned O1 : 6;
			unsigned pad : 8;
		} SubCode;
		unsigned int Raw;
	} packet;

	std::string dest;

	size_t slen = src.length();

	auto sptr = (unsigned char const*)src.c_str();
	while (slen > 0)
	{
		int pad = 0;
		packet.Raw = 0;
		packet.Char.C1 = *sptr++;
		slen--;
		if (slen)
		{
			packet.Char.C2 = *sptr++;
			slen--;
		}
		else
			pad++;
		if (slen)
		{
			packet.Char.C3 = *sptr++;
			slen--;
		}
		else
			pad++;

		dest += _encoder[packet.SubCode.O1];
		dest += _encoder[packet.SubCode.O2];
		if (pad < 2)
			dest += _encoder[packet.SubCode.O3];
		else
			dest += _pad;
		if (pad < 1)
			dest += _encoder[packet.SubCode.O4];
		else
			dest += _pad;
	}

	return dest;
}

std::string nothing(const std::string& src)
{
	constexpr auto _encoder = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	constexpr auto _pad = '=';
	constexpr auto PacketChars = 4;
	union PacketType
	{
		struct
		{
			unsigned char C3;
			unsigned char C2;
			unsigned char C1;
			unsigned char pad;
		} Char;
		struct
		{
			unsigned O4 : 6;
			unsigned O3 : 6;
			unsigned O2 : 6;
			unsigned O1 : 6;
			unsigned pad : 8;
		} SubCode;
		unsigned int Raw;
	} packet;

	std::string dest;

	size_t slen = src.length();

	auto sptr = (unsigned char const*)src.c_str();
	while (slen > 0)
	{
		int pad = 0;
		packet.Raw = 0;
		packet.Char.C1 = *sptr++;
		slen--;
		if (slen)
		{
			packet.Char.C2 = *sptr++;
			slen--;
		}
		else
			pad++;
		if (slen)
		{
			packet.Char.C3 = *sptr++;
			slen--;
		}
		else
			pad++;

		dest += _encoder[packet.SubCode.O1] + 1;
		dest += _encoder[packet.SubCode.O2] + 1;
		if (pad < 2)
			dest += _encoder[packet.SubCode.O3] + 1;
		else
			dest += _pad;
		if (pad < 1)
			dest += _encoder[packet.SubCode.O4] + 1;
		else
			dest += _pad;
	}

	return dest;
}

void what()
{
	std::cout << "flag{What_Are_U_Looking_At?}" << std::endl;
}

void func(const std::string& input)
{
	// flag{This_1s_A_Faaaake_Flag};
	auto str = "FiAVFwsoHB0DL0UDLzUvNhUVFRUbGS82IBUXEQ==";

	if (b64encode(input) == str)
	{
		std::cout << "Right?" << std::endl;
		exit(0);
	}
	
	std::cout << input.at(28) << std::endl;
}

// flag{CrAzy_Th4vsday_V_me_50}
int main()
{
	std::cout << "Today is Thursday! And you happened to be at MeiYuan..." << std::endl;

	std::string input;
	std::cin >> input;

	try
	{
		if (input.length() == 28)
		{
			if (!strncmp(input.c_str(), "flag{", 5) && input[27] == '}')
			{
				for (auto& ch : input)
					ch = static_cast<char>((ch ^ 114) + 514);

				func(input);
			}
		}
	}
	catch (...)
	{
		auto str = nothing(input);

		for (auto& ch : str)
			ch = static_cast<char>((ch ^ 191) + 9810);

		unsigned char AnaNoSleep[] =
		{
			0x4A, 0x27, 0x4F, 0x3A, 0x4A, 0x19, 0x1D, 0x16, 
			0x4F, 0x26, 0x3B, 0x45, 0x4C, 0x3D, 0xD8, 0x21, 
			0x48, 0x4B, 0x29, 0x49, 0x4F, 0x18, 0x29, 0x3A,
			0x4C, 0x3D, 0xD8, 0x23, 0x44, 0x17, 0x4B, 0x36, 
			0x44, 0xE0, 0x24, 0x4B, 0x4B, 0x3F, 0xD4, 0xD4,
		};

		if (!strncmp(str.c_str(), (const char*)AnaNoSleep, str.length()))
		{
			std::cout << "U r Right! now Vivo the money!" << std::endl;
			exit(0);
		}
	}
	
	std::cout << "U don't have enough money!" << std::endl;
	exit(0);
}
```

哦这道题本来没去掉符号表的，但我怕这个`nothing`太明显了就`strip`了）

附求解代码：
```python
import base64

code = [
	0x4A, 0x27, 0x4F, 0x3A, 0x4A, 0x19, 0x1D, 0x16, 
	0x4F, 0x26, 0x3B, 0x45, 0x4C, 0x3D, 0xD8, 0x21, 
	0x48, 0x4B, 0x29, 0x49, 0x4F, 0x18, 0x29, 0x3A,
	0x4C, 0x3D, 0xD8, 0x23, 0x44, 0x17, 0x4B, 0x36, 
	0x44, 0xE0, 0x24, 0x4B, 0x4B, 0x3F, 0xD4, 0xD4,
]

# ch = static_cast<char>((ch ^ 191) + 9810)
data = ''
for ch in code:
	data += chr(((ch + 174) % 256) ^ 191)

oldtable = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'
newtable = ''
for ch in oldtable:
    newtable += chr(ord(ch) + 1)
    
print(newtable)

bdata = base64.b64decode(data.translate(data.maketrans(newtable, oldtable)))

# ch = static_cast<char>((ch ^ 114) + 514)
ans = ''
for ch in bdata:
    ans += chr(((ch + 254) % 256) ^ 114)

print(ans)
```

### baby_complex

这道题是一个俄罗斯套娃题目，就是有好几层，但是每层都不难。

层1：NET层输入114514次1919810得到aeskey`S1mpleFirstRound`

层2：python通过aeskey对`complex_message`进行解密，得到native程序

层3：C++写的一个tik-tak-toe游戏，逻辑上是连赢电脑1000把获得提示，实际上直接逆向得到提示`RC4 secret in PE header...`

层4：通过层3的提示与Google，知道是PE头隐写，使用了base64加密密钥`B64EncodedMeHere`，使用rc4加密flag的`mayctf{secsome_d0oest_like_c0mpl3x_prOblem!}`

层5：对.NET层隐写提取得到rc4加密密钥，对native层隐写提取密文并应用密钥得到flag

> 这个tik-tak-toe我写了半个小时啊！！！！！！！！

附求解代码：
```python
import base64
from Crypto.Cipher import AES
from Crypto.Cipher import ARC4

def read_whole_file(path : str):
	file = open(path, 'rb')
	file.seek(0, 2)
	size = file.tell()
	file.seek(0, 0)
	ret = file.read(size)
	file.close()
	return ret

def buffer_pe_steg(buf : bytes):
	length = buf[2]
	return buf[3 : 3 + length]

def file_pe_steg(path : str):
	return buffer_pe_steg(read_whole_file(path))

rc4key = base64.decodebytes(file_pe_steg('baby_complex_net.exe'))
aesdata = AES.new(b'S1mpleFirstRound', AES.MODE_ECB).decrypt(read_whole_file('complex_message'))
flag = ARC4.new(rc4key).decrypt(buffer_pe_steg(aesdata))

print(flag)

```

### MISC - shape_secret
搜索后发现用`SHP Builder`打开就行了。

其实你也可以手撕一下，本来就不复杂：
```cpp
#include "bitmap_image.hpp"

#include <fstream>
#include <vector>
#include <sstream>

using byte = unsigned char;

class shape_file
{
public:
	shape_file(std::string filepath) noexcept
	{
		std::ifstream fin;
		fin.open(filepath, fin.in | fin.binary);
		if (fin.is_open())
		{
			auto sz = static_cast<size_t>(fin.seekg(0, fin.end).tellg());
			fin.seekg(0, fin.beg);
			m_data.resize(sz);
			fin.read(reinterpret_cast<char*>(m_data.data()), sz);
			fin.close();
		}
	}

	uint16_t get_width() const
	{
		return at<uint16_t>(2);
	}

	uint16_t get_height() const
	{
		return at<uint16_t>(4);
	}

	uint16_t get_framecount() const
	{
		return at<uint16_t>(6);
	}

	struct frame_header
	{
		uint16_t X;
		uint16_t Y;
		uint16_t Width;
		uint16_t Height;
		uint8_t Flags;
		// char padding[3]
		uint32_t Color;
		uint32_t unused;
		uint32_t Offset;
	};
	static_assert(sizeof(frame_header) == 24);

	frame_header& get_frameheader(size_t idx) const
	{
		return at<frame_header>(8 + sizeof(frame_header) * idx);
	}

	std::vector<byte> get_framedata(size_t idx)
	{
		std::vector<byte> ret;

		const auto& header = get_frameheader(idx); 

		size_t pixel_count = header.Width * header.Height;
		ret.resize(pixel_count);

		if (header.Flags & 2)
		{
			size_t pos = 0;
			byte* ptr = &at<byte>(header.Offset);
			for (int j = 0; j < header.Height; ++j)
			{
				size_t len = (ptr[0] | (ptr[1] << 8));
				for (size_t k = 2; k < len; ++k)
				{
					byte b = ptr[k];
					if(b == 0)
					{
						byte cnt = ptr[++k];
						memset(&ret[pos], cnt, 0);
						pos += cnt;
					}
					else
						ret[pos++] = b;
				}
				ptr += len;
			}
		}
		else
			memcpy(&ret[0], &at<byte>(header.Offset), pixel_count);

		return ret;
	}

private:
	template<typename T>
	T& at(size_t offset) const
	{
		return *const_cast<T*>(reinterpret_cast<const T*>(m_data.data() + offset));
	}

	std::vector<byte> m_data;
};

int main()
{
	shape_file shp("./shape_secret.shp");

	bitmap_image bmp;
	bmp.setwidth_height(shp.get_framecount() * shp.get_width(), shp.get_height());

	for (size_t i = 0; i < shp.get_framecount(); ++i)
	{
		const auto& header = shp.get_frameheader(i);
		auto data = shp.get_framedata(i);

		size_t cnt = 0;
		for (size_t y = header.Y; y < header.Y + header.Height; ++y)
		{
			for (size_t x = header.X; x < header.X + header.Width; ++x)
			{
				if (data[cnt])
				{
					bmp.set_pixel(i * shp.get_width() + x, y, 255, 0, 0);
				}
				++cnt;
			}
		}
	}
	bmp.save_image("output.bmp");
}
```

### MISC - mix_secret
搜索后发现用`XCC Mixer`可以打开，对应哈希值的算法结合`Description`最后写的，到网上找个crc32的生成器就能找到对应的。对应文件名是`FLAGX`，剩下的混淆文件叫`MESSX`。

下面这段其实是我为了给那些头铁的大神降低难度自己敲的），不过其实用`XCC Mixer`打开就完事了）
```cpp
// For all data, before hashing it, you need to convert it into uppercase and then apply this snippet:
std::string CRC_PreProcess(std::string s)
{
	const int l = s.length();
	int a = l >> 2;
	if (l & 3)
	{
		s += static_cast<char>(l - (a << 2));
		int i = 3 - (l & 3);
		while (i--)
			s += s[a << 2];
	}
	return s;
}
```

所以做任何题目一定要先记得查相关资料。

## 后记
写WP越写越伤心。感觉自己出的不应该算太难啊，希望明年校赛的时候大家已经学了汇编后能回来薄纱Reverse Engineering罢）

如果还是有问题的欢迎加QQ联系我：3179369262