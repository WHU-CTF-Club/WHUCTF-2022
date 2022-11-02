from gmpy2 import gcd, invert
from pwn import *

p = remote('127.0.0.1', 11116, ssl=False)
p.recvuntil('Hello, Give me your expr: ')
p.sendline('MSG < (2**512)')

for i in range(100):
    p.recvuntil('n = ')
    n = int(p.recvline()[:-1], 10)
    p.recvuntil('g = ')
    g = int(p.recvline()[:-1], 10)
    p.recvuntil('a = ')
    a = int(p.recvline()[:-1], 10) 
    p.recvuntil('b = ')
    b = int(p.recvline()[:-1], 10)

    msg =  a * invert(b, n**2) % (n**2)
    p.recvuntil('msg =')
    p.sendline(str(msg))

p.interactive()