# Typing Train

## 1.打开网站，马上就得到提示

[![xv96OO.md.png](https://s1.ax1x.com/2022/11/07/xv96OO.md.png)](https://imgse.com/i/xv96OO)

结合题目说明，我们需要在输入框内输入6666次正确的字符串就可以得到flag啦！所以点击“开始”看看什么情况。

[![xv9T6f.md.png](https://s1.ax1x.com/2022/11/07/xv9T6f.md.png)](https://imgse.com/i/xv9T6f)

发现是一串字符串，将它输入后又跳转啦！

[![xvCiBF.md.png](https://s1.ax1x.com/2022/11/07/xvCiBF.md.png)](https://imgse.com/i/xvCiBF)

现在可以完全理清思路了：我们需要将屏幕上显示的字符串输入正确6666次，然后就会得到flag。

## 2.写脚本替我们执行“输入显示的字符串6666次”（以**Python**为例）

+ 从何开始？打开一个网站首先就是观察url，我们每次输入一段字符串，必然要上传到网页本地进行解析，所以先看传输方式是GET还是POST。显然“http://124.220.41.254:20002/index.php?input=xxxxxxxxx”是GET方式；

+ 所以总体思路就来了：用**Python设置6666次Request**，每次传入的input即为上个网页显示的字符串，下面给出代码参考；

  ```python
  import requests
  url = "http://124.220.41.254:20002/index.php"
  begin = True
  for i in range(0, 6668):
      if begin:
          data = {'start': 0}
          res = requests.get(url, data)
          #print(res.text)
          content = str(res.text[330:362])
          cookie = res.cookies
          print(content)
          begin = False
      else:
          data = {'input': content}
          res = requests.get(url, data, cookies=cookie)
          print(res.text)
          content = str(res.text[330:362])
          print(res.url)
          print(content)
  ```

  + 在第一步分析中，我们点击“开始“时网址为”http://124.220.41.254:20002/index.php?start“，所以必须在开始时候传入start参数并随便设置一个值，我使用bool类型的begin来执行这一步；

  + 如何获取每次input的值呢？通过分析网页文本内容得知，input字符串放在body的head部分，且固定为***res.text[330:362]***（分析text列表，遍历元素，找到索引，这里不详细说明了），到这里我们已经解决大部分问题了；

    [![xvFUjx.md.png](https://s1.ax1x.com/2022/11/07/xvFUjx.md.png)](https://imgse.com/i/xvFUjx)

  + 可是却发现，只改变input的值会返回”错误！！！“，并不能得到正确的Response，说明还存在其他检测input是否正确的参数！我们仔细思考：我们新生成的input是依据先前网页的input而产生，所以简单的改变input不能建立起与前个响应的关系；通过burpsuite抓包，才了解到网页通过cookie来决定前后响应关系的！所以我们需要在每次请求时将cookie也传入（即代码段中的***cookie=res.cookies***）；

  + 综上我们发送请求***res = requests.get(url, data, cookies=cookie)***包含三个参数：url、data、cookies，对于***requests.get***中data、cookies等参数的具体组织形式可以自行搜索学习噢；

  + 至此脚本整体思路已经具备了，大家可以尝试一下，我这个仅供参考，不是很完善诶；

## 3.看看我们脚本跑出来的结果吧！

[![xvAs1A.md.png](https://s1.ax1x.com/2022/11/07/xvAs1A.md.png)](https://imgse.com/i/xvAs1A)

flag：***mayctf{gR34t!!!_You_Typ3_s0_F4st!!!}***