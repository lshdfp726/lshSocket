
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "lshSocket.h"
#include "lshIO.h"
int writable_fd(int fd);

int startClient(int argc, char const *argv[]) {
    int clientfd;
    char *host, *port, buf[MAXBUF], receiveBuf[MAXBUF];
    lshRio_t rio;

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = (char *)argv[1];
    port = (char *)argv[2];

    fprintf(stdout, "请输入发送的内容\n");
    fprintf(stdout, "你将给主机: %s, 端口%s 发送消息, 你发送的内容是%s\n", host, port, buf);
    clientfd = lsh_openClientfd(host, port);
    //while 循环 标准输入一直读
    int fd = open("test.txt", O_RDONLY, 0);
    while (lsh_readn(fd, buf, MAXBUF))
    // while (fgets(buf, MAXBUF, stdin) != NULL) 
    {
        lshRio_readinitb(&rio, clientfd);
        //写给socket 文件描述符，这里是服务端
        lsh_writen(clientfd, buf, strlen(buf));
        //从服务端去读，socket 全双工
        fprintf(stdout, "begin read\n");
        lshc_readline(&rio, receiveBuf, MAXBUF);
        //服务端读的文件给标准输出。
        fprintf(stdout, "receive: %s\n", receiveBuf);
        if (strstr(receiveBuf, "\\r\\n")) {
            //关闭，
            close(clientfd);
            if (writable_fd(clientfd) < 0) {
                printf("can not write");
            }
            printf("close old clientfd: %d\n",clientfd);
            //重新连接
            clientfd = lsh_openClientfd(host, port);
            printf("connect new clientfd: %d\n",clientfd);
        }
        // fputs(buf, stdout);
        printf("继续发送, 请直接输入。如果不想玩了用Ctrl+D 结束进程:\n");
    }

    return 0;
}

int writable_fd(int fd) {
    fd_set write_fds;
    struct timeval timeout;
    FD_ZERO(&write_fds);
    FD_SET(fd, &write_fds);
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    int ret = select(fd + 1, NULL, &write_fds, NULL, &timeout);
    return ret;
}