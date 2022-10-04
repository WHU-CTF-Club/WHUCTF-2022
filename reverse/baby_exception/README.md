# Description
An exception has occured: `NullKFCException!`

# Difficulty
⭐⭐⭐

# Flag
`flag{CrAzy_Th4vsday_V_me_50}`

# Platform
Linux

# Hint
`std::out_of_range`

# WriteUp
首先找到被异常包裹的实际代码段，然后分析发现是码表的ASCII码全部+1的魔改版base64加密，解密即可得到结果。
