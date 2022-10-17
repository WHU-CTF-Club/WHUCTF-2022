## 0x01 - Decompile
[反编译pyc文件](https://tool.lu/pyc/)得到：
```python
#!/usr/bin/env python
# visit https://tool.lu/pyc/ for more information
# Version: Python 2.7

print 'Welcome to Re World!'
print 'Your input1 is your flag~'
l = len(input1)
for i in range(l):
    num = ((input1[i] + i) % 128 + 128) % 128
    code += num

for i in range(l - 1):
    code[i] = code[i] ^ code[i + 1]

print code
code = [
    '%1f',
    '%12',
    '%1d',
    '(',
    '0',
    '4',
    '%01',
    '%06',
    '%14',
    '4',
    ',',
    '%1b',
    'U',
    '?',
    'o',
    '6',
    '*',
    ':',
    '%01',
    'D',
    ';',
    '%',
    '%13']
```
由此写出解密脚本即可

## 0x02 - Analyse
```python
code = ['\x1f','\x12','\x1d','(','0','4','\x01','\x06','\x14','4',',','\x1b','U','?','o','6','*',':','\x01','D',';','%','\x13']

for i in range (len(code) - 2, -1, -1):
    code[i] = chr(ord(code[i]) ^ ord(code[i + 1]))

for i in range (len(code)):
    code[i] = (ord(code[i]) - i) % 128

print(bytes(code))
```

## 0x03 - Flag
`flag{Just_Re_1s_Ha66y!}`
