from M1aES import M1aES
from flag import FLAG
import base64

key = "mayctfisthebestoneright?"
m1aes = M1aES(key)
cipher = m1aes.encrypt(FLAG)
print base64.b64encode(cipher)
#A0kkREd/TSZlQTcXIjVHdR4MCHUeOE0qOUERQDMgY3pSV3o2A2E9NjtTEVt5fE01
