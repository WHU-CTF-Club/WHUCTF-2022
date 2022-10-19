FROM ubuntu
MAINTAINER Qian-YM
# x86支持

# copy源文件 
COPY ./fmt  /fmt
COPY ./flag  /fmt/
# add低权限用户
RUN useradd -U -m pwn
# 配置权限, 程序属于低权限用户, flag属于root与低权限组, 组可查看flag
RUN chown root:pwn /tmp/flag\
    &&chown root:pwn /tmp/pwn
RUN chmod  750 /tmp/pwn\
    &&chmod 740 /tmp/flag

CMD sudo -u pwn socat tcp-l:4444,fork exec:/tmp/pwn
EXPOSE 4444


