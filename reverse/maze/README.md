# Description
I'm trapped in a maze! Is there anyone could get me out of here!

# Difficulty
⭐⭐

# Flag
`mayctf{sha256(SDSSDSDDSDDDWDDSSSAAAAAASSDDDDDD)}`
`mayctf{0b166389d580bb3f857b869847a0512667d98e09896153f2afb715ff2a3b3214}`

# Platform
Linux

# WriteUp
静态分析程序发现程序是一个模拟走迷宫程序，直接找到出口即可。
之后根据提示计算输入的`sha256`哈希值得到结果。
