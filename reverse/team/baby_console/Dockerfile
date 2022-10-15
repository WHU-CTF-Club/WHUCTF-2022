FROM ubuntu
MAINTAINER Nemo

RUN dpkg --add-architecture i386

RUN apt-get update

RUN apt-get install -y libc6:i386 libncurses5:i386 libstdc++6:i386\
    &&apt-get install -y socat sudo


COPY ./baby_console /tmp/reverse
COPY ./flag /reverse/
# add低权限用户
RUN useradd -U -m reverse
# 配置权限, 程序属于低权限用户, flag属于root与低权限组, 组可查看flag
RUN chown root:reverse /tmp/flag\
    &&chown root:reverse /tmp/reverse
RUN chmod  750 /tmp/reverse\
    &&chmod 740 /tmp/flag

CMD sudo -u reverse socat tcp-l:4444,fork exec:/tmp/reverse
EXPOSE 4444
