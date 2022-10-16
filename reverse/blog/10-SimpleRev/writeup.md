## 0x01 - Disassemble
直接运行程序抱了Segmentation fault，直接用IDA逆向逻辑。

```cpp
int __cdecl __noreturn main(int argc, const char **argv, const char **envp)
{
  int chr; // eax
  char input; // [rsp+Fh] [rbp-1h]

  while ( 1 )
  {
    while ( 1 )
    {
      printf("Welcome to CTF game!\nPlease input d/D to start or input q/Q to quit this program: ");
      input = getchar();
      if ( input != 'd' && input != 'D' )
        break;
      Decry();
    }
    if ( input == 'q' || input == 'Q' )
      Exit("Welcome to CTF game!\nPlease input d/D to start or input q/Q to quit this program: ", argv);
    puts("Input fault format!");
    chr = getchar();
    putchar(chr);
  }
}
```

直接看`Decry`：
```cpp
void __fastcall Decry()
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  v10 = __readfsqword(0x28u);
  *(_QWORD *)src = 'SLCDN';
  v6 = 0LL;
  v7 = 0;
  v8[0] = 'wodah';
  v8[1] = 0LL;
  v9 = 0;
  text = join(key3, (const char *)v8);
  strcpy(key, key1);
  strcat(key, src);
  v1 = 0;
  v2 = 0;
  getchar();
  v4 = strlen(key);
  for ( i = 0; i < v4; ++i )
  {
    if ( key[v2 % v4] > '@' && key[v2 % v4] <= 'Z' )
      key[i] = key[v2 % v4] + ' ';
    ++v2;
  }
  printf("Please input your flag:");
  while ( 1 )
  {
    v0 = getchar();
    if ( v0 == '\n' )
      break;
    if ( v0 == ' ' )
    {
      ++v1;
    }
    else
    {
      if ( v0 <= '`' || v0 > 'z' )
      {
        if ( v0 > '@' && v0 <= 'Z' )
        {
          str2[v1] = (v0 - '\'' - key[v2 % v4] + 'a') % 26 + 'a';
          ++v2;
        }
      }
      else
      {
        str2[v1] = (v0 - '\'' - key[v2 % v4] + 'a') % 26 + 'a';
        ++v2;
      }
      if ( !(v2 % v4) )
        putchar(' ');
      ++v1;
    }
  }
  if ( !strcmp(text, str2) )
    puts("Congratulation!\n");
  else
    puts("Try again!\n");
}
```

## 0x02 - Analyse
首先分析`text`，其是`join(key3, "hadow")`的结果，而`key3 = "kills"`，即`text = "killshadow"`
同理`key = "ADSFKNDCLS"`
接下来的循环里面将`key`全部转换为小写，即实际上`key = adsfkndcls`
再分析后面的转换即可，解题脚本如下：
实际上由于原公式不可逆，直接跑了一个暴力）

```python
import string

key = b'adsfkndcls'
text = b'killshadow'
ans = ''

for i in range(len(key)):
  for ch in list(string.ascii_uppercase):
    if (ord(ch) - 39 - key[i] + 97) % 26 + 97 == text[i]:
      ans += ch
      break

print(ans)
```

## 0x03 - Flag
`flag{KLDQCUDFZO}`
