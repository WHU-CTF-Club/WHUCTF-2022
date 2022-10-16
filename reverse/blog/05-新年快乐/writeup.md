## 0x00 - Check
发现有UPX壳，直接`upx.exe -d`解开即可。

## 0x01 - Disassemble
脱壳后用`IDA Pro`打开程序反汇编得到：
```cpp
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int result; // eax
  char Str2[14]; // [esp+12h] [ebp-3Ah] BYREF
  __int16 Str1; // [esp+20h] [ebp-2Ch] BYREF
  _BYTE v6[30]; // [esp+22h] [ebp-2Ah] BYREF

  __main();
  strcpy(Str2, "HappyNewYear!");
  Str1 = 0;
  memset(v6, 0, sizeof(v6));
  printf("please input the true flag:");
  scanf("%s", &Str1);
  if ( !strncmp((const char *)&Str1, Str2, strlen(Str2)) )
    result = puts("this is true flag!");
  else
    result = puts("wrong!");
  return result;
}
```

## 0x02 - Flag
显然就是`flag{HappyNewYear!}`