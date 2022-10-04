# Description
secsome has just invented a super computer on his `Social Computing Methods and Applications` class as it's a class that's not quite interesting. And after he finished this super computer, he felt quite sleepy... 

# Difficulty
⭐⭐⭐

# Flag
`mayctf{I_@m_Sleeeeeepy!I_aM_Always_V3ry_Sl33py!}`

# Platform
Linux

# Hint
How does a computer works?
How does secsome feel now?

# WriteUp
程序是一个简单的虚拟机，逐个分析opcode即可得到
|操作码|格式|C风格代码|
|:-:|:-:|:-:|
|0|VM_EXIT|`return EAX;`|
|1|VM_NOP|*// Do nothing*|
|2|VM_SETREG *REG* *IVAL*|`REG = IVAL;`|
|3|VM_MOVREG *DREG* *SREG*|`DREG = SREG;`|
|4|VM_SHOWSTR *REG*|`printf("%s", REG);`|
|5|VM_TEA *FLAG* *VREG* *KREG* | `if (!FLAG) {encrypt(VREG, KREG);} else {decrypt(VREG, KREG);}` |
|6|VM_PUSH *REG*|`Stack_Push(REG);`|
|7|VM_POP *REG*|`REG = Stack_Pop();`|
|8|VM_ADD *DREG* *SREG*|`DREG += SREG;`|
|9|VM_READSTR *BUFREG* *LENREG*| `scanf("%LENREGs", BUFREG);`|
|***default***|***ILLEGAL***|***Throw Exception***|

再分析程序逻辑，对前24字节调用encrypt, 后24字节调用decrypt。故容易得到结果。密钥即为`shell`显示的内容。
