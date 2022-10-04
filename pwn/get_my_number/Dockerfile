FROM ubuntu
MAINTAINER Nemo
# x86支持
RUN dpkg --add-architecture i386
# update列表
RUN apt-get update
# 安装基础程序
RUN apt-get install -y libc6:i386 libncurses5:i386 libstdc++6:i386\
    &&apt-get install -y socat sudo

# copy源文件
COPY ./get_my_number /tmp/pwn
COPY ./flag /tmp/
# add低权限用户
RUN useradd -U -m pwn
# 配置权限, 程序属于低权限用户, flag属于root与低权限组, 组可查看flag
RUN chown root:pwn /tmp/flag\
    &&chown root:pwn /tmp/pwn
RUN chmod  750 /tmp/pwn\
    &&chmod 740 /tmp/flag

CMD sudo -u pwn socat tcp-l:4444,fork exec:/tmp/pwn
EXPOSE 4444
