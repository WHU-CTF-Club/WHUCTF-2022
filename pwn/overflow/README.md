## Description

In this question I want to show you how the parameter is transmitted.
And you should learn to use ROPgadget.

## Difficulty

:star: :star: :star:

## flag

flag{abac-hayy-1o1c-uunv}

## Platform

Linux

## Hint

What's the structure of the stack? The first parameter in which reg?

## WriteUp

用ROPgadget查找"pop|ret", 找到指令"pop rdi; retn; " 指令的地址。
用pwntools写一个交互脚本就行

