# Description
I hacked a website, can i explore more?

# Difficulty
⭐⭐⭐⭐⭐

# Flag
`mayctf{Y0u_v3_s7e99ed_0n_th3_7hr3sh01d}`

# Hint 
hosts
frpc

# WriteUp
ssh连接成功后，hosts中找到node_admin节点地址，发现无法访问，存在防火墙，注意到frps.ini，意识到admin主机内可能存在frpc，运行frps服务，curl访问admin节点服务，发现需要认证登录，使用curl和节点中给出的admin_token登录后即可得到flag
