import base64,string,M1aES
key = "mayctfisthebestoneright?"
c = base64.b64decode("A0kkREd/TSZlQTcXIjVHdR4MCHUeOE0qOUERQDMgY3pSV3o2A2E9NjtTEVt5fE01")
m1aes = M1aES.M1aES(key)
f=""
for i in range(3):
    for j in range(16):
        for k in string.printable:
            s = "x"*i*16+"x"*j+k+"x"*(48-i*16-j-1)
            e = m1aes.encrypt(s)
            check = c[i*16+j+8] == e[i*16+j+8] if j < 8 else c[i*16+j-8] == e[i*16+j-8]
            if check:
                f += k
                break
print f
