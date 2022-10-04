# Description
Mobile phones not only uses Java, they do call C++ native codes as well!

# Difficulty
⭐⭐

# Flag
`mayctf{S0_This_1S_Android_Native_Cpp!}`

# Platform
Android

# WriteUp
使用`IDA Pro`打开`libnative_android.so`，找到`Java_com_example_native_1android_MainActivity_checkFlagNative`函数，发现是使用按下标异或的`key`进行的标准`TEA`加密，直接解密即可得到结果。
