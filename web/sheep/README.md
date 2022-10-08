# Description
赢得游戏取得胜利吧！

# Difficulty
⭐⭐⭐

# Flag
`mayctf{Wow!_You_have_Real1y_H4ndle_http}`

# Platform (Optional)
ARCH

# Hint (Optional)


# WriteUp
f12查看网页网页源代码，发现游戏胜利后是访问`/fl4g.php`，因此我们可以跳过游戏直接访问该接口
访问后会提示修改对应的请求包内容
- 修改`User-Agent`请求头来伪造浏览器    `User-Agent: hack`
- 修改`Cookie`请求头来伪造身份          `Cookie: user=admin`
- 修改`GET`为`POST`更改请求方式
