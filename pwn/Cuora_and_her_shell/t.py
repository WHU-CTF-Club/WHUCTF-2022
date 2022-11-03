from pwn import *

context.arch = 'amd64'
shell_code = asm(shellcraft.sh())

for i in shell_code:
    print(hex(i))

