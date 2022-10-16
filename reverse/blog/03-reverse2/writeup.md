## 0x00 - Test
直接运行程序，程序提示`input the flag:`

## 0x01 - Disassemble
使用`IDA Pro`打开程序，找到`main`按下`F5`反汇编，使用`Y`键调整`flag`类型为`char[18]`后得到：
```cpp
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int result; // eax
  int stat_loc; // [rsp+4h] [rbp-3Ch] BYREF
  int i; // [rsp+8h] [rbp-38h]
  __pid_t pid; // [rsp+Ch] [rbp-34h]
  char s2[24]; // [rsp+10h] [rbp-30h] BYREF
  unsigned __int64 v8; // [rsp+28h] [rbp-18h]

  v8 = __readfsqword(0x28u);
  pid = fork();
  if ( pid )
  {
    waitpid(pid, &stat_loc, 0);
  }
  else
  {
    for ( i = 0; i <= strlen(flag); ++i )
    {
      if ( flag[i] == 'i' || flag[i] == 'r' )
        flag[i] = '1';
    }
  }
  printf("input the flag:");
  __isoc99_scanf("%20s", s2);
  if ( !strcmp("{hacking_for_fun}", s2) )
    result = puts("this is the right flag!");
  else
    result = puts("wrong flag!");
  return result;
}
```
其中`flag`是字符串`"{hacking_for_fun}"`

## 0x02 - Analyse
程序使用了fork防止最简单的调试，由于逻辑简单我们直接进行静态分析。
分析程序容易得到将`flag`的`i`和`r`全部换成`1`即可。

## 0x03 - Flag
故`flag{hack1ng_fo1_fun}`
