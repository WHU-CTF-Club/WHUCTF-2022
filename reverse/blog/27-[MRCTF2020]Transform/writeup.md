## 0x01 - Disassemble
```cpp
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char input[104]; // [rsp+20h] [rbp-70h] BYREF
  int j; // [rsp+88h] [rbp-8h]
  int i; // [rsp+8Ch] [rbp-4h]

  init(argc, argv, envp);
  printf("Give me your code:\n");
  scanf("%s", input);
  if ( strlen(input) != 33 )
  {
    printf("Wrong!\n");
    system("pause");
    exit(0);
  }
  for ( i = 0; i <= 32; ++i )
  {
    data_table[i] = input[index_lookup[i]];
    data_table[i] ^= LOBYTE(index_lookup[i]);
  }
  for ( j = 0; j <= 32; ++j )
  {
    if ( answer_table[j] != data_table[j] )
    {
      printf("Wrong!\n");
      system("pause");
      exit(0);
    }
  }
  printf("Right!Good Job!\n");
  printf("Here is your flag: %s\n", input);
  system("pause");
  return 0;
}
```

## 0x02 - Analyse
```python
ans = [ 
	0x67, 0x79, 0x7B, 0x7F, 0x75, 0x2B, 0x3C, 0x52, 0x53, 0x79, 0x57,
	0x5E, 0x5D, 0x42, 0x7B, 0x2D, 0x2A, 0x66, 0x42, 0x7E, 0x4C, 0x57,
	0x79, 0x41, 0x6B, 0x7E, 0x65, 0x3C, 0x5C, 0x45, 0x6F, 0x62, 0x4D,
	0x3F
]

lookup = [
	0x9, 0x0A, 0x0F, 0x17, 0x7, 0x18, 0x0C, 0x6, 0x1, 0x10, 0x3, 0x11, 0x20,
	0x1D, 0x0B, 0x1E, 0x1B, 0x16, 0x4, 0x0D, 0x13, 0x14, 0x15, 0x2, 0x19,
	0x5, 0x1F, 0x8, 0x12, 0x1A, 0x1C, 0x0E, 0x0
]

mapper = {}

for i in range(33):
	mapper[lookup[i]] = i

for i in range(33):
	ans[i] = ans[i] ^ lookup[i]

flag = ''
for i in range(33):
	flag += chr(ans[mapper[i]])

print(flag)
```

## 0x03 - Flag
`flag{Tr4nsp0sltiON_Clph3r_1s_3z}`
