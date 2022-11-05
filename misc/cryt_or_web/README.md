# Description
Do it! Just do it!

# Difficulty
⭐⭐

# Flag
`mayctf{n0w_y0u_Mas7er_r8a_anD_f1ask_Mayb3}`

# WriteUp
运行flask即可rsa解密得到网站子域名, 进入网站通过正则通配三个非字符+字符后拼接, 两次base64解码可得
mayctf{bbaassee6644(YmpCM1gza3dkVjlOWVhNM1pYSmZjamhoWDJGdVJGOW1NV0Z6YTE5TllYbGlNdz09)}
mayctf{bbaassee6644(YmpCM1gza3dkVjlOWVhNM1pYSmZ5jYamhoWDJGdVJGOW1NV0Z6YTE5TllYbGlNdz09)}

也可加
Content-Type: application/x-www-form-urlencoded
构造POST
