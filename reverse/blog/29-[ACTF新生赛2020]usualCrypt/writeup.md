## 0x01 - Disassemble
```cpp
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v3; // esi
  int result; // eax
  char buffer[16]; // [esp+8h] [ebp-74h] BYREF
  char input[100]; // [esp+18h] [ebp-64h] BYREF

  printf(asc_40E140);
  scanf("%s", input);
  *(_DWORD *)buffer = 0;
  *(_DWORD *)&buffer[4] = 0;
  *(_DWORD *)&buffer[8] = 0;
  *(_WORD *)&buffer[12] = 0;
  buffer[14] = 0;
  b64encode(input, strlen(input), buffer);
  v3 = 0;
  while ( buffer[v3] == answer[v3] )
  {
    if ( ++v3 > strlen(buffer) )
      goto LABEL_6;
  }
  printf(aError);
LABEL_6:
  if ( v3 - 1 == strlen(answer) )
    result = printf(aAreYouHappyYes);
  else
    result = printf(aAreYouHappyNo);
  return result;
}

void __stdcall update_b64table()
{
  int i; // eax
  char v1; // cl

  for ( i = 6; i < 15; ++i )
  {
    v1 = b64table[i + 10];
    b64table[i + 10] = b64table[i];
    b64table[i] = v1;
  }
}

int __cdecl result_case_switch(const char *a1)
{
  __int64 v1; // rax
  char v2; // al

  v1 = 0i64;
  if ( strlen(a1) )
  {
    do
    {
      v2 = a1[HIDWORD(v1)];
      if ( v2 < 'a' || v2 > 'z' )
      {
        if ( v2 < 'A' || v2 > 'Z' )
          goto LABEL_9;
        LOBYTE(v1) = v2 + 32;
      }
      else
      {
        LOBYTE(v1) = v2 - 32;
      }
      a1[HIDWORD(v1)] = v1;
LABEL_9:
      LODWORD(v1) = 0;
      ++HIDWORD(v1);
    }
    while ( HIDWORD(v1) < strlen(a1) );
  }
  return v1;
}
```

## 0x02 - Analyse
发现是一个换表的base64加密，并将结果大小写转换，解密即可。
```python
import base64

src = 'zMXHz3TIgnxLxJhFAdtZn2fFk3lYCrtPC2l9'
data = ''
for ch in src:
	if ord(ch) >= ord('A') and ord(ch) <= ord('Z'):
		data += chr(ord(ch) - ord('A') + ord('a'))
	elif ord(ch) >= ord('a') and ord(ch) <= ord('z'):
		data += chr(ord(ch) - ord('a') + ord('A'))
	else:
		data += ch

oldtable = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'
newtable = oldtable[0 : 6] + oldtable[16 : 25] + oldtable[15] + oldtable[6 : 15] + oldtable[25 : 64]
print(base64.b64decode(data.translate(data.maketrans(newtable, oldtable))))
```

## 0x03 - Flag
`flag{bAse64_h2s_a_Surprise}`
