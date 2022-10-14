# Description
It's kind of complex when you are facing with multiple composed stuffs...

# Difficulty
⭐⭐⭐⭐

# Flag
`mayctf{secsome_d0oest_like_c0mpl3x_prOblem!}`

# Platform
Windows

# WriteUp
题目有多重包装

层1：.NET 输入114514次1919810得到aeskey`S1mpleFirstRound`

层2：python 通过aeskey对`complex_message`进行解密，得到native程序

层3：C++ 一个tik-tak-toe游戏，逻辑上是连赢电脑1000把获得提示，实际上直接逆向得到提示`RC4 secret in PE header...`

层4：通过提示，知道是PE头隐写，使用了base64加密密钥`B64EncodedMeHere`，使用rc4加密flag`mayctf{secsome_d0oest_like_c0mpl3x_prOblem!}`

层5：对.NET层隐写提取得到rc4加密密钥，对native层隐写提取并应用密钥得到flag

```python
# 层2
import imp
verifier = imp.load_compiled('baby_complex_verifier', '__pycache__/baby_complex_verifier.cpython-310.pyc')
f = open('baby_complex_native.exe', 'wb')
f.write(verifier.decode('S1mpleFirstRound'.encode('utf-8')))
f.close()
```
