# Find_It

### 查看网页源码

* 要去分析一个网页，最容易想到的就是***查看源码***，很多时候flag就藏在某个文件的注释中；

  [![xvElHf.md.png](https://s1.ax1x.com/2022/11/07/xvElHf.md.png)](https://imgse.com/i/xvElHf)

  index大致一看，主要是显示动态网页的代码，再看看index1.css；

  [![xvENgs.md.png](https://s1.ax1x.com/2022/11/07/xvENgs.md.png)](https://imgse.com/i/xvENgs)

  也是没有得到有用的信息；

* 我们点击网页画面可以跳转到许多index*a*.html，其中index3.html是个泄密者***”哼，你想要找的东西就在这里“***，那就看看它的源码；

  [![xvVQz9.md.png](https://s1.ax1x.com/2022/11/07/xvVQz9.md.png)](https://imgse.com/i/xvVQz9)

  index3.css文件怎么这么多行，甚是奇怪，往下拉，原来flag就藏在最后一行，index3果然泄密啦！

  [![xvVrLt.md.png](https://s1.ax1x.com/2022/11/07/xvVrLt.md.png)](https://imgse.com/i/xvVrLt)

  这串字符不是flag啊，一看是字母数字的组合，大概率是***base-64编码***啦，解码一下就拿到flag：***mayctf{0h_yo3_ca3_f1nd_i7}***

  

  

  

  

  