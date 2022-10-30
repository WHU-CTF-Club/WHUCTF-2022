# Description
Maybe you want to have some challenges, if you have a NVIDIA CUDA GPU, then try this one!

# Difficulty
⭐⭐⭐⭐⭐

# Flag
`MAYCTF{NviDiA_CuDA_GPU_ProGrAm!}`

# Platform
Linux + Nvidia CUDA

# WriteUp
发现程序调用了`CUDA C++`进行加密处理，于是对照其`CUDA`字节码还原逻辑，发现是改造过的只进行18轮的`TEA`加密，解密即可。