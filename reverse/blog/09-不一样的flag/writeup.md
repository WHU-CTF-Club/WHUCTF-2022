## 0x01 - Disassemble
```cpp
int __cdecl __noreturn main(int argc, const char **argv, const char **envp)
{
  char MAP[5][5]; // [esp+17h] [ebp-35h] BYREF
  int Y; // [esp+30h] [ebp-1Ch]
  int X; // [esp+34h] [ebp-18h]
  int opt; // [esp+38h] [ebp-14h] BYREF
  int i; // [esp+3Ch] [ebp-10h]
  _BYTE map[12]; // [esp+40h] [ebp-Ch] BYREF

  __main();
  X = 0;
  strcpy((char *)MAP, "*11110100001010000101111#");
  while ( 1 )
  {
    puts("you can choose one action to execute");
    puts("1 up");
    puts("2 down");
    puts("3 left");
    printf("4 right\n:");
    scanf("%d", &opt);
    if ( opt == 2 )
    {
      ++Y;
    }
    else if ( opt > 2 )
    {
      if ( opt == 3 )
      {
        --X;
      }
      else
      {
        if ( opt != 4 )
LABEL_13:
          exit(1);
        ++X;
      }
    }
    else
    {
      if ( opt != 1 )
        goto LABEL_13;
      --Y;
    }
    for ( i = 0; i <= 1; ++i )
    {
      if ( *(&Y + i) < 0 || *(&Y + i) > 4 )
        exit(1);
    }
    if ( map[5 * Y - 0x29 + X] == '1' )
      exit(1);
    if ( map[5 * Y - 41 + X] == '#' )
    {
      puts("\nok, the order you enter is the flag!");
      exit(0);
    }
  }
}
```
反汇编结果有奇怪的地方，下面分析。

## 0x02 - Analyse
IDA反汇编的结果map有一个`-0x29`，结合map本身是`-0xC`，实际偏移应为`-0x35`，即`MAP`，结合5 * Y可以推断`MAP`是一个`char[5][5]`的迷宫数据，我们要走出迷宫。
从`strcpy`得到迷宫数据为
```
*1111
01000
01010
00010
1111#
```

根据
```cpp
puts("1 up");
puts("2 down");
puts("3 left");
printf("4 right\n:");
```
对应得到输入应为`2 2 2 4 4 1 1 4 4 2 2 2`，测试得到`ok, the order you enter is the flag!`

## 0x03 - Flag
`flag{222441144222}`