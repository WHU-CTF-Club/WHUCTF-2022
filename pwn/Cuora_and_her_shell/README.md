## Description

Cuora lost her shell, can you find it?

![Cuora](./Cuora.png)

## Difficulty

:star: :star:

## flag

flag{4sian_box_turtles_are_terrestrial_semiaquatic_0r_mainly_aquatic}

## Platform

Linux-x64

## Hint

1. what is the type of ((void (\*)())?
2. How to get shell use assembly language？



## WriteUp

((void (\*)())将map强制类型转换为函数指针，直球写shell code

exp见本目录下py文件