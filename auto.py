from re import L
from pwn import *
import hashlib,string,random
import math
import gmpy2
'''
def fastExpMod(b, e, m):
    result = 1
    while e != 0:
        if e == 1:
            # ei = 1, then mul
            result = (result * b) % m
        e -= 1
        # b, b^2, b^4, b^8, ... , b^(2^n)
        b = (b*b) % m
    return result
'''


io = remote("1.13.191.241","2333")
temp = io.recvline()
print(temp)
temp1 = temp.split(b"mod")
print(temp1)

part_proof = int(bytes.decode(temp1[0].split(b"POW: ")[1])[5:-2])
print(part_proof)
sha = int(bytes.decode(temp1[1])[:-5].strip())
print(sha)
print(len(str(sha)))
print(gmpy2.is_prime(sha))
print(pow(2,part_proof))
ans = str(gmpy2.powmod(2,pow(2,part_proof)%sha,sha))

print(ans.encode())
io.sendline(ans.encode())

io.interactive()
