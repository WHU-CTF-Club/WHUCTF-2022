## 0x01 - Disassemble
`UPX`脱壳后反编译：
```cpp
int __cdecl main(int argc, const char **argv, const char **envp)
{
  _BYTE answer[12]; // [esp+12h] [ebp-2Eh] BYREF
  char v5[12]; // [esp+1Eh] [ebp-22h]
  _BYTE input[18]; // [esp+2Ah] [ebp-16h] BYREF
  int i; // [esp+3Ch] [ebp-4h]

  __main();
  qmemcpy(answer, "*F'\"N,\"(I?+@", sizeof(answer));
  printf("Please input:");
  scanf("%s", input);
  if ( input[0] != 'A' || input[1] != 'C' || input[2] != 'T' || input[3] != 'F' || input[4] != '{' || input[17] != '}' )
    return 0;
  *(_DWORD *)v5 = *(_DWORD *)&input[5];
  *(_DWORD *)&v5[4] = *(_DWORD *)&input[9];
  *(_DWORD *)&v5[8] = *(_DWORD *)&input[13];
  for ( i = 0; i <= 11; ++i )
  {
    if ( answer[i] != strtable[v5[i] - 1] )
      return 0;
  }
  printf("You are correct!");
  return 0;
}
// strtable: [126 - 33]
```

## 0x02 - Analyse
程序对我们输入的flag做了一个查表的校验，我们可以直接将表的内容反向映射即可
注意到表只是[33, 126]的反向，容易得到解密脚本如下：
需要注意这个表将33与35进行的对调，要额外判断。

```python
ans = '*F\'\"N,\"(I?+@'
flag = ''

for ch in ans:
	if ch == '\x20':
		flag += chr(127 - 0x22)
	elif ch == '\x22':
		flag += chr(127 - 0x20)
	else:
		flag += chr(127 - ord(ch))

print('flag{' + flag + '}')
```

## 0x03 - Flag
`flag{U9X_1S_W6@T?}`
