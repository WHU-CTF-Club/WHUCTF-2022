from re import L
from pwn import *
import hashlib,string,random

io = remote("124.220.41.254","11112")
temp = io.recvline()
print(temp)
temp1 = temp.split(b"==")
print(temp1)
part_proof = bytes.decode(temp1[0].split(b"XXXX")[1])[1:-2]
sha = bytes.decode(temp1[1]).strip()
table = string.ascii_letters + string.digits
while True:
    XXXX = "".join([random.choice(table)for _ in range(4)])
    temp_proof = XXXX + part_proof
    temp_sha = hashlib.sha256(temp_proof.encode()).hexdigest()
    if sha == temp_sha:
        io.recvuntil(b"[+] Give Me XXXX :")
        print(XXXX)
        io.sendline(XXXX.encode())
        break
io.interactive()
