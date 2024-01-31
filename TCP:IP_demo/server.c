#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>

#include "lshSocket.h"
#include "lshIO.h"


void echo(int connfd);

int main(int argc, char const *argv[]) 
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; //sockadd_in 存储IPV4地址，sockaddr_storage 可以存储任何地址。服务端面对的不止IPV4
    char client_hostName[MAXBUF], client_port[MAXBUF];

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port> \n", argv[0]);
        exit(0);
    }

    listenfd = lsh_openListenfd((char *)argv[1]);

    while (1)
    {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen); //accept函数 和客户端的connect是相互阻塞
        if (connfd < 0) {
            printf("accpet failed connfd: %d\n",connfd);
            continue;
        }
        getnameinfo((struct sockaddr *)&clientaddr, clientlen, client_hostName, MAXBUF, client_port, MAXBUF, 0);
        printf("connected to (%s, %s)\n",client_hostName, client_port);
        echo(connfd);
        close(connfd);
    }
    return 0;
}

void echo(int connfd) {
    size_t n;
    char buf[MAXBUF];
    lshRio_t rio;
    lshRio_readinitb(&rio, connfd);

    while ((n = lshc_readline(&rio, buf, MAXBUF)) != 0)
    {
        printf("server received %d bytes, buffer is %s\n",(int)n, buf);
        char *temp = "server:";
        int len = strlen(temp);
        char *tail = "\n";
        int tailLen = strlen(tail);
        char b[n + len + tailLen];
        memmove(b, temp, len);
        memmove(b + len, buf, n);
        memmove(b + len + n, tail, tailLen);
        printf("server send len is  %zu, buffer is %s\n",n + len + tailLen, b);
        lsh_writen(connfd, b, n + len + tailLen);
    }
}