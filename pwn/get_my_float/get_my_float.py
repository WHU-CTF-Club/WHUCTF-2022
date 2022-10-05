from pwn import *

p = remote('0.0.0.0', 10001)

p.send(b"\x2d\xb2\x9d\xef\xa7\xc6\xe3\x3f")
#3FE3C6A7EF9DB22D

p.interactive()
