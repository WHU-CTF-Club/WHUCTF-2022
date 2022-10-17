## 0x00 ???
这道题按道理不应该放到`Crypto`吗？

## 0x01 - Solve
通过公钥得到e和n再分解出p和q从而解密文件

```python
import gmpy2
import rsa

e = 65537
n = 86934482296048119190666062003494800588905656017203025617216654058378322103517
p = 285960468890451637935629440372639283459
q = 304008741604601924494328155975272418463

phin = (q - 1) * (p - 1)
d = gmpy2.invert(e, phin)

key = rsa.PrivateKey(n, e, int(d), p, q)

f = open('flag.enc', 'rb')
data = f.read()
print(rsa.decrypt(data, key))
```
