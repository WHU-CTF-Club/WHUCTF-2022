###学籍管理
这两篇博客讲的很详细了捏
[漏洞讲解](https://blog.csdn.net/weixin_44190459/article/details/116774912)
[session伪造](https://blog.csdn.net/weixin_52116519/article/details/124338506)

###cryt_or_web
在下发的app.py中，按照给出的解码方法将给出的cipher_text解码。
得到提示后，构造POST请求包。(注意POST包中必要的Content-Type和Content-Length内容)
成功用POST上传KEY值后，页面自动跳转，观察可以发现首字母组成了flag，并暗示了解码方式~~最后注意区分I和l (qwq!)~~

###typing train
用python的request包写一个脚本，完成6666次提交。
注意同一身份交互多次时，应该带上cookie参数。

###sheep
查看网页js源代码
在goodsClick函数末尾发现胜利响应代码，将其放入控制台中运行得到hint
再根据提示构造GET请求包即可

###find_it
在“你要找的东西就在这里”一页中的CSS代码最下方

###background
题目几乎没有过滤，直接上交一个php文件，再访问它即可执行
php中可以写入目录遍历的代码，找到flag文件后访问即可