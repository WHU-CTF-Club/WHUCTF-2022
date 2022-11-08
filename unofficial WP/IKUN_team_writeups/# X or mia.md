# X or mia

先分析源码

```python
def xor(msg, key):
    o = ''
    for i in range(len(msg)):
        o += chr(ord(msg[i]) ^ ord(key[i % 11]))
    return o
f = open('message', 'r') 
msg = ''.join(f.readlines()).rstrip('\n')
f.close()
k = open('key', 'r')
key = ''.join(k.readlines()).rstrip('\n')
k.close()
assert key.isalnum() and (len(key) == 11)
assert 'mayctf' in msg
d = open('encrypted', 'w')
d.write(xor(msg, key))
```

不难看出通过将明文与key的对应位进行异或得到密文，由于xor可逆，我们只需要对密文再次走一遍加密算法就能够得到明文

```python
assert key.isalnum() and (len(key) == 11)
assert 'mayctf' in msg
```

这一步可以知道明文中有mayctf字段，并且密钥长度为11，那我们可以大胆预测，明文的格式就是mayctf{xxxxxxxx}

通过这个信息结合密文，我们可以还原key的前七位，已知有

```
'mayctf{' xor key[:7] = cipher[:7]
```

很容易得到

```
key[:7] = 'mayctf{' xor cipher[:7]
```

顺利还原前七位，即'i1oveyo'

还记得题目给的信息么？

i 1ove you mia, but maybe xor is better?

i1oveyoumia 正好十一位

放进去解密，得到flag