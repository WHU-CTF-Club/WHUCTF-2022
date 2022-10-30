from re import L
from pwn import *
import hashlib,string,random
from Crypto.Cipher import AES

io = remote("node4.buuoj.cn","27370")
temp = io.recvline()
# print(temp)
temp1 = temp.split(b"==")
# print(temp1)
part_proof = bytes.decode(temp1[0].split(b"XXXX")[1])[1:-2]
sha = bytes.decode(temp1[1]).strip()
table = string.ascii_letters + string.digits
while True:
    XXXX = "".join([random.choice(table)for _ in range(4)])
    temp_proof = XXXX + part_proof
    temp_sha = hashlib.sha256(temp_proof.encode()).hexdigest()
    if sha == temp_sha:
        io.recvuntil(b"[+] Give Me XXXX :")
        io.sendline(XXXX.encode())
        break
io.recvuntil(b"[-] ")
io.sendline(b"1")
io.sendline(b"1" * 16)
io.recvuntil(b'Miao~ ')
iv = io.recvuntil(b"\n")[:-1]
# print(iv)
io.recvuntil(b'[-]')
io.sendline(b'1')
io.recvuntil(b'Permission:')
cat_permission = io.recvline()[:-1]
# print(cat_permission)
io.recvuntil(b"[-]")
io.sendline(b'2')
io.recvuntil(b"Looks like you want to know something. Give me your permission:")

m2 = b"a_cat_permission"
m1 = b'1' * 16 # your name,直接16字节，不会进行pad()函数，如果那样的话，m1也会成为一个未知量
need_m2 = b"Princepermission"
need_m1 = m1
c1 = cat_permission[:16]
c2 = cat_permission[16:]
fake_c1 = xor(xor(c1,m2),need_m2)

io.sendline(fake_c1)
io.recvuntil(b"Miao~ ")
io.sendline(iv)
io.recvuntil(b"The message is ")
m = io.recvuntil(b"\n")[:-1]
# print(plain)
io.recvuntil(b"[-]")
io.sendline(b'3')
io.recvuntil(b"Give me your permission:")

fake_permission = fake_c1 + c2
fake_iv = xor(xor(m,m1),iv)

io.sendline(fake_permission)
io.recvuntil(b"What's the cat tell you?")
io.sendline(fake_iv)
io.interactive()
