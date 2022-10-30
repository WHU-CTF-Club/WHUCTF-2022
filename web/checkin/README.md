# Description

​	在小学期的实训期间，老师在每天上前会公布六位数的密码，要求同学将学号与密码拼接进行md5加密后上传至gitlab完成签到。比如吴同学的学号是2021302181050，当日的密码是123456，需要将2021302181050123456md5加密成密文EEFC14496A84158D09B511E9BE4F805E后上传。但是有一天，Mia早上睡过头了，没有听到老师的密码，她只能看到别的同学加密过的密文，你能帮她完成签到吗？

# Difficulty

⭐

# Flag

```
flag{y0u_ha7e_che3ke8_in_suc5c3ssfu7ly}
```

# Platform (Optional)

ARCH

# Hint (Optional)

It is recommended to use hashcat,you can also write python scripts

# WriteUp

使用hashcat解出密码972513，将自己学号与密码拼接后md5加密，上传即获得flag.