## 0x01 - Disassemble
关键部分代码如下：
其中MD5SUM与SHASUM_1均可以从MSDN中通过查找`CryptCreateHash`函数对应的参数得到。
```cpp
int __cdecl main_0(int argc, const char **argv, const char **envp)
{
  DWORD input1len; // eax
  DWORD v4; // eax
  char input2[260]; // [esp+4Ch] [ebp-310h] BYREF
  int v7; // [esp+150h] [ebp-20Ch]
  char buffer[260]; // [esp+154h] [ebp-208h] BYREF
  char input1[260]; // [esp+258h] [ebp-104h] BYREF

  memset(input1, 0, sizeof(input1));
  memset(buffer, 0, sizeof(buffer));
  v7 = 0;
  printf("pls input the first passwd(1): ");
  scanf("%s", input1);
  if ( strlen(input1) != 6 )
  {
    printf("Must be 6 characters!\n");
    ExitProcess(0);
  }
  v7 = atoi(input1);
  if ( v7 < 100000 )
    ExitProcess(0);
  strcat(input1, "@DBApp");
  input1len = strlen(input1);
  SHASUM_1(input1, input1len, buffer);
  if ( !_strcmpi(buffer, "6E32D0943418C2C33385BC35A1470250DD8923A9") )
  {
    printf("continue...\n\n");
    printf("pls input the first passwd(2): ");
    memset(input2, 0, sizeof(input2));
    scanf("%s", input2);
    if ( strlen(input2) != 6 )
    {
      printf("Must be 6 characters!\n");
      ExitProcess(0);
    }
    strcat(input2, input1);
    memset(buffer, 0, sizeof(buffer));
    v4 = strlen(input2);
    MD5SUM(input2, v4, buffer);
    if ( !_strcmpi("27019e688a4e62a649fd99cadaafdb4e", buffer) )
    {
      if ( !Generate_File(input2) )
      {
        printf("Error!!\n");
        ExitProcess(0);
      }
      printf("bye ~~\n");
    }
  }
  return 0;
}

void __cdecl xordecode(const char *key, char *data, int datalen)
{
  unsigned int i; // [esp+4Ch] [ebp-Ch]
  unsigned int kLen; // [esp+54h] [ebp-4h]

  kLen = lstrlenA(key);
  for ( i = 0; i < datalen; ++i )
    data[i] ^= key[i % kLen];
}

bool __cdecl Generate_File_Impl(const char *input2)
{
  void *buffer; // [esp+50h] [ebp-1Ch]
  DWORD NumberOfBytesWritten; // [esp+58h] [ebp-14h] BYREF
  DWORD bufsize; // [esp+5Ch] [ebp-10h]
  HGLOBAL hResData; // [esp+60h] [ebp-Ch]
  HRSRC hResInfo; // [esp+64h] [ebp-8h]
  HANDLE hFile; // [esp+68h] [ebp-4h]

  hFile = 0;
  hResData = 0;
  bufsize = 0;
  NumberOfBytesWritten = 0;
  hResInfo = FindResourceA(0, 0x65, "AAA");
  if ( !hResInfo )
    return 0;
  bufsize = SizeofResource(0, hResInfo);
  hResData = LoadResource(0, hResInfo);
  if ( !hResData )
    return 0;
  buffer = LockResource(hResData);
  xor_decode(input2, buffer, bufsize);
  hFile = CreateFileA("dbapp.rtf", 0x10000000u, 0, 0, 2u, 0x80u, 0);
  if ( hFile == -1 )
    return 0;
  if ( !WriteFile(hFile, buffer, bufsize, &NumberOfBytesWritten, 0) )
    return 0;
  CloseHandle(hFile);
  return 1;
}
```

## 0x02 - Analyse
input1与input2都要是6位字符串，且要满足
`SHA1SUM {input1}@DBApp = 6E32D0943418C2C33385BC35A1470250DD8923A9`
`MD5SUM {input2}{input1}@DBApp = 27019e688a4e62a649fd99cadaafdb4e`
考虑到均只有6位，可以考虑直接枚举爆破。

```python
# bruteforce

import hashlib
import string
import itertools

def generate_strings(length, chars):
	for item in itertools.product(chars, repeat = length):
		yield "".join(item)

input1 = ''
input2 = ''
for s in generate_strings(6, string.digits):
	if hashlib.sha1(s.encode('utf-8') + b'@DBApp').hexdigest() == '6e32d0943418c2c33385bc35a1470250dd8923a9':
		input1 = s
		break

suffix = input1.encode('utf-8') + b'@DBApp'
for s in generate_strings(6, string.printable):
	if hashlib.md5(s.encode('utf-8') + suffix).hexdigest() == '27019e688a4e62a649fd99cadaafdb4e':
		input2 = s
		break

print(input1, input2)
```
睡一觉起来就可以得到`123321 ~!3a@0`
再运行程序，输入这两个字符串即可。
打开生成的`dbapp.rtf`，即可看见`Flag{N0_M0re_Free_Bugs}`.

## 0x03 - Optimize
input2需要枚举95^6=735091890625次，耗时仍然很长，考虑优化的方案：

发现后面有一个`xor_decode`，由于我们应该得到一个rtf文件，而其文件头的前六个字节应为`{\rtf1`，利用`Resource Hacker`查看加密的数据前6个字节为`05 7D 41 15 26 01`，故可以得到`input2`：
```python
src = [0x05, 0x7D, 0x41, 0x15, 0x26, 0x01]
dst = list('{\\rtf1')

input2 = ''
for i in range(6):
	input2 += chr(src[i] ^ ord(dst[i]))

print(input2)
```
即可得到`input2 = ~!3a@0`

## 0x03 - Flag
`flag{N0_M0re_Free_Bugs}`
