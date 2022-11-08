# Sheep

## 通关就能得到flag！

+ 通关去得flag，这恐怕是非专业人员才会做的事。我们直接***F12***看源码；

  [![xvZZ6A.md.png](https://s1.ax1x.com/2022/11/07/xvZZ6A.md.png)](https://imgse.com/i/xvZZ6A)

  没想到游戏的实现逻辑代码直接给我们啦，读懂game.js就能破解此题！

## 破解game.js

* 一大堆变量定义、什么createGoods、gameStart、gameFinish都不是重点。我们仔细一瞧，在goodsClick里面一段关键代码

  [![xvZ0tU.md.png](https://s1.ax1x.com/2022/11/07/xvZ0tU.md.png)](https://imgse.com/i/xvZ0tU)

  这里是你是否通关的逻辑部分，什么boxVolume > 7是判断7个格子填满就输了，chronoscopeNum <= 0是判断你消消乐完了，时间大于20s则失败......我们主要看游戏胜利的逻辑，***fetch("/fl4g.php", )***这不是明摆着告诉我们flag在哪里嘛~~~；

## 访问fl4g.php/BP抓包测试

* 好好翻译一下”Please use ***hack*** browser“->”请使用***hack***浏览器“；

  [![xvZ20x.md.png](https://s1.ax1x.com/2022/11/07/xvZ20x.md.png)](https://imgse.com/i/xvZ20x)

* 我们知道Edge浏览器、Chrome浏览器，哪里去找什么hack浏览器呢？我们用burpsuite抓包一下

  [![xveG4O.md.png](https://s1.ax1x.com/2022/11/07/xveG4O.md.png)](https://imgse.com/i/xveG4O)

  我们在Request中得到了很多标志着本次请求的一些关键信息，***GET***请求方式、***User-Agent***（用户代理）信息、***Cookie***（标志着我们的身份”guest“，大胆猜一下可能说明有***user=host***）；

* 在User-Agent里我们发现他记录了我们是用***Chrome***浏览器发送的请求！仔细去搜索***User-Agent***到底记录了什么信息[User-Agent介绍](https://zhuanlan.zhihu.com/p/97973031)，它要我们使用hack浏览器就把User-Agent里面的Chrome改成hack再发送请求咯；

  [![xvnU0I.md.png](https://s1.ax1x.com/2022/11/07/xvnU0I.md.png)](https://imgse.com/i/xvnU0I)

* 奏效了，Response又要我们用admin的身份去发送请求，这不就是要我们***修改cookies里的user***么，修改完再请求；

  [![xvnhNV.md.png](https://s1.ax1x.com/2022/11/07/xvnhNV.md.png)](https://imgse.com/i/xvnhNV)

* 越来越接近flag了，Response提示我们使用POST请求而不是GET请求，修改请求方式；

   [![xvnTc4.md.png](https://s1.ax1x.com/2022/11/07/xvnTc4.md.png)](https://imgse.com/i/xvnTc4)

  诶嘿，得到flag：***mayctf{Wow!_You_have_Real1y_H4ndle_http}***