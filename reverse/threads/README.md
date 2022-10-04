# Description
Multi-thread puzzle!  

# Difficulty
⭐⭐⭐

# Flag
`mayctf{It's_just@A_verrrrrrrry_s1mple_multiThr#ad_stuff_89EC1FBD-14ED-4DF3-93A3-91ED11A36956}`

# Platform
Windows

# WriteUp
`upx -d`先解壳，然后经过分析发现通过多线程对偶数下标调用`rot13`，奇数下标调用`xor_idx`，最后进行`sha256`哈希值对比校验是否正确。
