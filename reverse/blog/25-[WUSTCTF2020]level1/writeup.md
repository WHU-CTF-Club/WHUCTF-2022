## 0x01 - Disassemble
```cpp
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int i; // [rsp+4h] [rbp-2Ch]
  FILE *stream; // [rsp+8h] [rbp-28h]
  char ptr[24]; // [rsp+10h] [rbp-20h] BYREF
  unsigned __int64 v7; // [rsp+28h] [rbp-8h]

  v7 = __readfsqword(0x28u);
  stream = fopen("flag", "r");
  fread(ptr, 1uLL, 0x14uLL, stream);
  fclose(stream);
  for ( i = 1; i <= 19; ++i )
  {
    if ( (i & 1) != 0 )
      printf("%ld\n", (unsigned int)(ptr[i] << i));
    else
      printf("%ld\n", (unsigned int)(i * ptr[i]));
  }
  return 0;
}
```

## 0x02 - Analyse
题目给了对应的output，参照上面的代码写出解密脚本即可：
```python
src = [0, 198, 232, 816, 200, 1536, 300, 6144, 984, 51200, 570, 92160, 1200, 565248, 756, 1474560, 800, 6291456, 1782, 65536000]
flag = ''
for i in range(1, 20):
	if (i & 1) != 0:
		flag += chr(src[i] >> i)
	else:
		flag += chr(src[i] // i)

print(flag)
```

## 0x03 - Flag
`flag{d9-dE6-20c}`
