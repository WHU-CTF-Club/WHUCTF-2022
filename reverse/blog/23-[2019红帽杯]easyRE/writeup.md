## 0x01 - Disassemble
定位到`main`函数`sub_4009C6`：
```cpp
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int result; // eax
  int i; // [rsp+Ch] [rbp-114h]
  __int64 v5; // [rsp+10h] [rbp-110h]
  __int64 v6; // [rsp+18h] [rbp-108h]
  __int64 v7; // [rsp+20h] [rbp-100h]
  __int64 v8; // [rsp+28h] [rbp-F8h]
  __int64 v9; // [rsp+30h] [rbp-F0h]
  __int64 v10; // [rsp+38h] [rbp-E8h]
  __int64 v11; // [rsp+40h] [rbp-E0h]
  __int64 v12; // [rsp+48h] [rbp-D8h]
  __int64 v13; // [rsp+50h] [rbp-D0h]
  __int64 v14; // [rsp+58h] [rbp-C8h]
  char v15[13]; // [rsp+60h] [rbp-C0h] BYREF
  char v16[4]; // [rsp+6Dh] [rbp-B3h] BYREF
  char v17[19]; // [rsp+71h] [rbp-AFh] BYREF
  char v18[32]; // [rsp+90h] [rbp-90h] BYREF
  int v19; // [rsp+B0h] [rbp-70h]
  char v20; // [rsp+B4h] [rbp-6Ch]
  char v21[72]; // [rsp+C0h] [rbp-60h] BYREF
  unsigned __int64 v22; // [rsp+108h] [rbp-18h]

  v22 = __readfsqword(0x28u);
  qmemcpy(v15, "Iodl>Qnb(ocy", 12);
  v15[12] = 127;
  qmemcpy(v16, "y.i", 3);
  v16[3] = 127;
  qmemcpy(v17, "d`3w}wek9{iy=~yL@EC", sizeof(v17));
  memset(v18, 0, sizeof(v18));
  v19 = 0;
  v20 = 0;
  sub_4406E0(0LL, v18, 37LL);
  v20 = 0;
  if ( sub_424BA0(v18) == 36 )
  {
    for ( i = 0; i < (unsigned __int64)sub_424BA0(v18); ++i )
    {
      if ( (unsigned __int8)(v18[i] ^ i) != v15[i] )
      {
        result = -2;
        goto LABEL_13;
      }
    }
    sub_410CC0("continue!");
    memset(v21, 0, 0x40uLL);
    v21[64] = 0;
    sub_4406E0(0LL, v21, 64LL);
    v21[39] = 0;
    if ( sub_424BA0(v21) == 39 )
    {
      v5 = sub_400E44(v21);
      v6 = sub_400E44(v5);
      v7 = sub_400E44(v6);
      v8 = sub_400E44(v7);
      v9 = sub_400E44(v8);
      v10 = sub_400E44(v9);
      v11 = sub_400E44(v10);
      v12 = sub_400E44(v11);
      v13 = sub_400E44(v12);
      v14 = sub_400E44(v13);
      if ( !(unsigned int)sub_400360(v14, off_6CC090) )
      {
        sub_410CC0("You found me!!!");
        sub_410CC0("bye bye~");
      }
      result = 0;
    }
    else
    {
      result = -3;
    }
  }
  else
  {
    result = -1;
  }
LABEL_13:
  if ( __readfsqword(0x28u) != v22 )
    sub_444020();
  return result;
}
```

## 0x02 - Analyse
经判断知道
`sub_410CC0 = puts`
`sub_400E44 = b64encode`
`sub_4406E0 = read_str`
`sub_400360 = strcmp`
`sub_424BA0 = strlen`
然后就对着进行10轮`b64decode`：
```python
import base64

t = b'Vm0wd2VHUXhTWGhpUm1SWVYwZDRWVll3Wkc5WFJsbDNXa1pPVlUxV2NIcFhhMk0xVmpKS1NHVkdXbFpOYmtKVVZtcEtTMUl5VGtsaVJtUk9ZV3hhZVZadGVHdFRNVTVYVW01T2FGSnRVbGhhVjNoaFZWWmtWMXBFVWxSTmJFcElWbTAxVDJGV1NuTlhia0pXWWxob1dGUnJXbXRXTVZaeVdrWm9hVlpyV1hwV1IzaGhXVmRHVjFOdVVsWmlhMHBZV1ZSR1lWZEdVbFZTYlhSWFRWWndNRlZ0TVc5VWJGcFZWbXR3VjJKSFVYZFdha1pXWlZaT2NtRkhhRk5pVjJoWVYxZDBhMVV3TlhOalJscFlZbGhTY1ZsclduZGxiR1J5VmxSR1ZXSlZjRWhaTUZKaFZqSktWVkZZYUZkV1JWcFlWV3BHYTFkWFRrZFRiV3hvVFVoQ1dsWXhaRFJpTWtsM1RVaG9hbEpYYUhOVmJUVkRZekZhY1ZKcmRGTk5Wa3A2VjJ0U1ExWlhTbFpqUldoYVRVWndkbFpxUmtwbGJVWklZVVprYUdFeGNHOVhXSEJIWkRGS2RGSnJhR2hTYXpWdlZGVm9RMlJzV25STldHUlZUVlpXTlZadE5VOVdiVXBJVld4c1dtSllUWGhXTUZwell6RmFkRkpzVWxOaVNFSktWa1phVTFFeFduUlRhMlJxVWxad1YxWnRlRXRXTVZaSFVsUnNVVlZVTURrPQ=='

for i in range(10):
	t = base64.decodebytes(t)

print(t)
```
得到一个网址：`https://bbs.pediy.com/thread-254172.htm`
打开发现是讲主动防御了，属于是把做题人骗着玩了。
> 所谓“让对手不要走正确的破解之路”
> 讲人话 就是“把对手往沟里带” 

这道题其实是魔改的程序退出的析构函数`sub_400D35`中，具体求解脚本如下：
```python
key = [0x40, 0x35, 0x20, 0x56]

for i in range(4):
	key[i] = ord('flag'[i]) ^ key[i]

code = [0x40, 0x35, 0x20, 0x56, 0x5D, 0x18, 0x22, 0x45, 0x17, 0x2F, 0x24, 0x6E, 0x62, 0x3C, 0x27, 0x54, 0x48, 0x6C, 0x24, 0x6E, 0x72, 0x3C, 0x32, 0x45, 0x5B]

flag = ''
for i in range(len(code)):
	flag += chr(code[i] ^ key[i % 4])

print(flag)
```

至于魔改这一点应该很早就能发现，文件大小有800多K，并且也没有链接到系统的libc，这一点就比较明显了。

## 0x03 - Flag
`flag{Act1ve_Defen5e_Test}`
