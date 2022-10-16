## 0x00 - Test
直接运行程序，随便输入两行`123`后得到一个`flag{this_Is_a_EaSyRe}`，直接丢进去发现就是正确的。
但是我们还是看一下程序的逻辑。

## 0x01 - Disassemble
使用`IDA Pro`打开程序，按下`F5`反汇编得到：
```cpp
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int b; // [rsp+28h] [rbp-8h] BYREF
  int a; // [rsp+2Ch] [rbp-4h] BYREF

  _main();
  scanf("%d%d", &a, &b);
  if ( a == b )
    printf("flag{this_Is_a_EaSyRe}");
  else
    printf("sorry,you can't get flag");
  return 0;
}
```
显然只要我们同时输入两个相等的整数即可。

## 0x02 - Flag
故`flag{this_Is_a_EaSyRe}`
