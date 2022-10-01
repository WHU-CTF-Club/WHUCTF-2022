# Description
`secsome` have some secret. And he hide it in this program. Can you find it out?

# Hint
`CFG` stands for `Control Flow Graph`. 

# Difficulty
⭐

# Flag
`MAYCTF{secsome_S3creT_C0nTroL_Flow_GraPh}`

# WriteUp
使用`IDA Pro`打开程序，查看`Graph View`即可得到`MAYCTF{$(AUTHOR)_S3creT_C0nTroL_Flow_GraPh}`，结合`$(AUTHOR) = secsome`得到结果。
