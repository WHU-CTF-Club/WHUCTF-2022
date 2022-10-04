## Description

Kal'tsit wants to know if you remember how old she is

## Difficulty

:star:

## flag

flag{a_s3cr3t_makes_a_w0man_w0man}

## Platform

Linux

## Hint

What's the type of the sizeof()?

## WriteUp

首先IDA打开，看到需要输入一个大于4000的数字，但是在输入大于2000时，会直接返回。

sizeof得到的类型是size_t, 实际上属于unsigned int, 当int和unsigned int参与运算时，int会强制类型转换为unsigned int

所以输入任意负数即可