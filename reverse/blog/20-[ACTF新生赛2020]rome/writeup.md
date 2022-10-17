## 0x01 - Disassemble
```cpp
int func()
{
  int result; // eax
  char flag[16]; // [esp+14h] [ebp-44h]
  char input[23]; // [esp+24h] [ebp-34h] BYREF
  char answer[17]; // [esp+3Bh] [ebp-1Dh] BYREF
  int i; // [esp+4Ch] [ebp-Ch]

  strcpy(answer, "Qsw3sj_lz4_Ujw@l");
  printf("Please input:");
  scanf("%s", input);
  result = (unsigned __int8)input[0];
  if ( input[0] == 'A' )
  {
    result = (unsigned __int8)input[1];
    if ( input[1] == 'C' )
    {
      result = (unsigned __int8)input[2];
      if ( input[2] == 'T' )
      {
        result = (unsigned __int8)input[3];
        if ( input[3] == 'F' )
        {
          result = (unsigned __int8)input[4];
          if ( input[4] == '{' )
          {
            result = (unsigned __int8)input[21];
            if ( input[21] == '}' )
            {
              *(_DWORD *)flag = *(_DWORD *)&input[5];
              *(_DWORD *)&flag[4] = *(_DWORD *)&input[9];
              *(_DWORD *)&flag[8] = *(_DWORD *)&input[13];
              *(_DWORD *)&flag[12] = *(_DWORD *)&input[17];
              for ( i = 0; i <= 15; ++i )
              {
                if ( flag[i] > '@' && flag[i] <= 'Z' )
                  flag[i] = (flag[i] - 51) % 26 + 'A';
                if ( flag[i] > '`' && flag[i] <= 'z' )
                  flag[i] = (flag[i] - 79) % 26 + 'a';
              }
              for ( i = 0; i <= 15; ++i )
              {
                result = (unsigned __int8)answer[i];
                if ( flag[i] != (_BYTE)result )
                  return result;
              }
              result = printf("You are correct!");
            }
          }
        }
      }
    }
  }
  return result;
}
```

## 0x02 - Analyse
凯撒密码，直接一一映射解密即可。
```python
import string

src = 'Qsw3sj_lz4_Ujw@l'

intable = ''
outtable = ''

for i in range(ord('A'), ord('Z') + 1):
	intable += chr(i)
	outtable += chr((i - 51) % 26 + ord('A'))

for i in range(ord('a'), ord('z') + 1):
	intable += chr(i)
	outtable += chr((i - 79) % 26 + ord('a'))

print('flag{' + src.translate(str.maketrans(outtable, intable)) + '}')
```

## 0x03 - Flag
`flag{Cae3ar_th4_Gre@t}`
