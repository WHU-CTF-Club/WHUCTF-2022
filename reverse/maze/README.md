# Description
I'm trapped in a maze! Is there anyone could get me out of here!

# Difficulty
⭐⭐

# Flag
`mayctf{sha256(SDSSDSDDSDDDWDDSSSAAAAAASSDDDDDD)}`
`mayctf{50690e67edf14e48e80c95d38276c77610555e99567641ca41e6c24f67c9a83e}`

# Platform
Linux

# WriteUp
静态分析程序发现程序是一个模拟走迷宫程序，直接找到出口即可。
之后根据提示计算输入的`sha256`哈希值得到结果。
