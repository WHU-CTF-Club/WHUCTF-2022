## 0x01 - Disassemble
直接用`IDA Pro`打开程序，定位到关键函数
```cpp
unsigned __int64 get_flag()
{
  unsigned int v0; // eax
  int i; // [rsp+4h] [rbp-3Ch]
  int j; // [rsp+8h] [rbp-38h]
  __int64 s; // [rsp+10h] [rbp-30h] BYREF
  char v5; // [rsp+18h] [rbp-28h]
  unsigned __int64 v6; // [rsp+38h] [rbp-8h]

  v6 = __readfsqword(0x28u);
  v0 = time(0LL);
  srand(v0);
  for ( i = 0; i <= 4; ++i )
  {
    switch ( rand() % 200 )
    {
      case 1:
        puts("OK, it's flag:");
        memset(&s, 0, 0x28uLL);
        strcat((char *)&s, f1);
        strcat((char *)&s, &f2);
        printf("%s", (const char *)&s);
        break;
      case 2:
        printf("Solar not like you");
        break;
      case 3:
        printf("Solar want a girlfriend");
        break;
      case 4:
        s = 0x7F666F6067756369LL;
        v5 = 0;
        strcat(&f2, (const char *)&s);
        break;
      case 5:
        for ( j = 0; j <= 7; ++j )
        {
          if ( j % 2 == 1 )
            *(&f2 + j) -= 2;
          else
            --*(&f2 + j);
        }
        break;
      default:
        puts("emmm,you can't find flag 23333");
        break;
    }
  }
  return __readfsqword(0x28u) ^ v6;
}
```

其中`f1 = "GXY{do_not_"`
下面分析`f2`

## 0x02 - Analyse
通过分析我们可以猜到应该先进行case4的初始化再走case5的处理，最后输出结果，因此我们进行手动解密即可，脚本如下：

```python
flag = [0x69, 0x63, 0x75, 0x67, 0x60, 0x6F, 0x66, 0x7F]

for i in range(8):
	if i % 2 == 0:
		flag[i] = flag[i] - 1
	else:
		flag[i] = flag[i] - 2

print(b'GXY{do_not_' + bytes(flag))
```

## 0x03 - Flag
`flag{do_not_hate_me}`
