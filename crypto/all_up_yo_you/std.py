from gmpy2 import gcd, invert 
from pwn import * 
 
p = remote('127.0.0.1', 11114, ssl=False) 
p.recvuntil(b'your expr: ') 
p.sendline(b'MSG < (2**512)') 
for i in range(100): 
    p.recvuntil(b'n =') 
    n = int(p.recvline()[:-1], 10) 
    p.recvuntil(b'g =') 
    g = int(p.recvline()[:-1], 10) 
    p.recvuntil(b'a =') 
    a = int(p.recvline()[:-1], 10)  
    p.recvuntil(b'b = ') 
    b = int(p.recvline()[:-1], 10) 
 
    msg =  a * invert(b, n**2) % (n**2) 
    p.recvuntil('msg =') 
    p.sendline(str(msg)) 
 
p.interactive()