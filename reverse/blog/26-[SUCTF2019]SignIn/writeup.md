## 0x01 - Disassemble
```cpp
__int64 __fastcall main(int a1, char **a2, char **a3)
{
  char v4[16]; // [rsp+0h] [rbp-4A0h] BYREF
  char v5[16]; // [rsp+10h] [rbp-490h] BYREF
  char v6[16]; // [rsp+20h] [rbp-480h] BYREF
  char v7[16]; // [rsp+30h] [rbp-470h] BYREF
  char v8[112]; // [rsp+40h] [rbp-460h] BYREF
  char v9[1000]; // [rsp+B0h] [rbp-3F0h] BYREF
  unsigned __int64 v10; // [rsp+498h] [rbp-8h]

  v10 = __readfsqword(0x28u);
  puts("[sign in]");
  printf("[input your flag]: ");
  __isoc99_scanf("%99s", v8);
  sub_96A(v8, v9);
  __gmpz_init_set_str(v7, "ad939ff59f6e70bcbfad406f2494993757eee98b91bc244184a377520d06fc35", 16LL);
  __gmpz_init_set_str(v6, v9, 16LL);
  __gmpz_init_set_str(v4, "103461035900816914121390101299049044413950405173712170434161686539878160984549", 10LL);
  __gmpz_init_set_str(v5, "65537", 10LL);
  __gmpz_powm(v6, v6, v5, v4);
  if ( (unsigned int)__gmpz_cmp(v6, v7) )
    puts("GG!");
  else
    puts("TTTTTTTTTTql!");
  return 0LL;
}

size_t __fastcall sub_96A(const char *a1, char *a2)
{
  size_t result; // rax
  int v3; // [rsp+18h] [rbp-18h]
  int i; // [rsp+1Ch] [rbp-14h]

  v3 = 0;
  for ( i = 0; ; i += 2 )
  {
    result = strlen(a1);
    if ( v3 >= result )
      break;
    a2[i] = byte_202010[a1[v3] >> 4];
    a2[i + 1] = byte_202010[a1[v3++] & 0xF];
  }
  return result;
}

_BYTE byte_202010[16] = {30h, 31h, 32h, 33h, 34h, 35h, 36h, 37h, 38h, 39h, 61h, 62h, 63h, 64h, 65h, 66h}
```

## 0x02 - Analyse
先搜索`__gmpz_init_set_str`，发现是`GNU`的高精度库，结合`65537`等特征数字与其它运算发现应该是rsa加密。
拿yafu分解一下再随便找个rsa脚本抄一下就行了*或者直接丢给你的`Crypto`队友*。

```python
import gmpy2

n = 103461035900816914121390101299049044413950405173712170434161686539878160984549
p = 282164587459512124844245113950593348271
q = 366669102002966856876605669837014229419
e = 65537
c = 0xad939ff59f6e70bcbfad406f2494993757eee98b91bc244184a377520d06fc35

d = gmpy2.invert(e, (p - 1) * (q - 1))
m = gmpy2.powmod(c, d, n)

print(bytes.fromhex(hex(m)[2:]))
```

## 0x03 - Flag
`suctf{Pwn_@_hundred_years}`
