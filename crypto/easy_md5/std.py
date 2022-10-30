from re import L
from pwn import *
import hashlib,string,random
from Crypto.Cipher import AES

io = remote("124.220.41.254","11111")

io.recvuntil(b"[-] ")
io.sendline(b"1")
io.recvuntil(b"[-] ")
io.sendline(b"may")
k = ?
for i in range(k):
    print(i)
    io.recvuntil(b"[-] ")
    io.sendline(b"1")
    io.recvuntil(b"it: ")
    io.recvline()
    tmp = io.recvline().strip()
    #print(tmp)
    ans = hashlib.md5(tmp).hexdigest().encode()
    io.sendline(ans)
    io.recvuntil(b"[-] ")

io.interactive()
