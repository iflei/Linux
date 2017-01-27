#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


static void usage(const char* proc)
{
    printf("Usage:%s [ip] [port]\n", proc);
}

int main(int argc, char* argv[])
{
   if(argc!=3)
    {
        usage(argv[0]);
        return 1;
    }
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(2);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sock, (struct sockaddr*)&server, (socklen_t)sizeof(server)) < 0)
    {
        perror("connect");
        exit(3);
    }

    char buf[1024];

    while(1)
    {
        printf("client# ");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf)-1);
        buf[s-1] = 0;
        write(sock, buf, s-1);

    }
    
    close(sock);
    return 0;
}
