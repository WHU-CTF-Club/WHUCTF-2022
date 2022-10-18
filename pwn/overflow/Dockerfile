FROM ubuntu
MAINTAINER Qian-YM
# x86支持
RUN sudo apt-get install python-capstone
# 先安装Capstone,它是一个轻量级的多平台架构支持的反汇编架构。
RUN python setup.py install
# 下载好ROPgadget解压，并进入文件夹中

# copy源文件 
COPY ./overflow  /overflow
COPY ./flag.txt  /overflow/
# add低权限用户
RUN useradd -U -m pwn
# 配置权限, 程序属于低权限用户, flag属于root与低权限组, 组可查看flag
RUN chown root:pwn /tmp/flag\
    &&chown root:pwn /tmp/pwn
RUN chmod  750 /tmp/pwn\
    &&chmod 740 /tmp/flag

CMD sudo -u pwn socat tcp-l:4444,fork exec:/tmp/pwn
EXPOSE 4444


