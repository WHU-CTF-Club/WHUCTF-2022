# Description
**TEA** is a widely used encryption algorithm.
Do you know how to decode it?  

# Difficulty
⭐⭐

# Flag
`mayctf{You_Wanna_Haave_A_Drink?}`

# Platform
Linux

# WriteUp
静态分析程序找到程序使用`Welcome2MAYBECTF`作为密钥进行标准`TEA`加密，直接解密即可。
