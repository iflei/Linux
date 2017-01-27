/*************************************************************************
	> File Name: server.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include "comm.h"

int main()
{
    int msgid = createMsgQueue();

    char buf[1024];
    while(1)
    {
        buf[0] = 0; //清空
        recvMsg(msgid, CLIENT_TYPE, buf); //从客户端接收消息
        printf("client# %s\n", buf);
        printf("Please Enter# ");
        fflush(stdout);

        ssize_t s = read(0, buf, sizeof(buf));
        if(s > 0)
        {
            buf[s-1] = 0;
            sendMsg(msgid, SERVER_TYPE, buf); //服务端发送消息
            printf("send done, wait recv...\n");
        }
    }

    destroyMsgQueue(msgid);
    return 0;
}
