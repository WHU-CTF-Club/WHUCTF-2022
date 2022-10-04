# Description
I am sleepy.?

# Difficulty
⭐⭐⭐

# Flag
`mayctf{I_@m_Sleeeeeepy!I_aM_Always_V3ry_Sl33py!}`

# Platform
Linux

# Hint
`Floyd` is being used to calculate `Multi-Source-Shortest-Path`, and it takes $O(n^3)$ time complexity.

# WriteUp
使用`IDA Pro`打开程序，分析算法发现是一个`Floyd`板子，但是观察输出只需要求点1开始的单源最短路径即可。故将数据提取出来再跑一个`SPFA`或者`Dijkstra`就行。
