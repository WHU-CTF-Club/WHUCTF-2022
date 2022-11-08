# mix_secret

一点开，好嘛老熟人了，又是这种格式的description

老方法，还是拖到google搜索出处，找到出处来自于[ModdingWiki](https://moddingwiki.shikadi.net/wiki/MIX_Format_(Westwood))，又是一种红警文件格式，顺利找到打开mix文件的工具xcc mixer,打开后才发现没这么简单，首先就像discription里说的那样，mix文件将文件名的hash作为索引，所以我们只能看到文件名hash之后的结果，好在另一个文件给了flag的文件名，分别是FLAG0,FLAG1···

但是试了很多hash算法都无法匹配上文件名，java似乎有能产生相同位数的hash算法，但是java环境懒得安装，于是作罢。

这时有了个新的想法，假如我能创建名字一样的一组文件，手动用这个工具创建一个包含它们的mix文件，再读出hash值，不就可以将hash和文件名对应起来了么？

说做就做

```python
import os
filename=''
for x in range(38):
    filename='FLAG'+str(x)
    c = open(filename,'w')
    c.write('w')
```

注意需要写入数据使文件不为空，否则无法导入mix(这一步卡了一会儿)。

在导入之后关闭这个文件，重新打开包含flag的文件，惊喜的发现可以正确的显示FLAGx的文件名了，看来是建立了hash缓存，自动将匹配的文件名替换。

成功读出flag