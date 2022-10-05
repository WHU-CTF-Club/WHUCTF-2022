from pwn import *

p = remote('0.0.0.0', 10001)

p.send(b"\x3F\x35\x1e\x3F")

gdb.attach(p)
p.interactive()
