# Description
To get the next shell

# Difficulty
⭐⭐⭐⭐

# Flag
`mayctf{N0w_Y0u_m@y_Know_wh@t_1s_unserialize!}`

# Hint (Optional)
可能你需要些反序列化的知识

# WriteUp
简单审计源代码
## 考点
 - 弱类型比较
 - 简单的类知识`__construct` 和 `__toString`魔术方法
 - 简单的构造序列化数据 `O:5:"Shell":1:{s:3:"cmd";s:3:"env";}` 由`genSerial.php`生成