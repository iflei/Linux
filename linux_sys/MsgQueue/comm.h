/*************************************************************************
	> File Name: comm.h
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#ifndef _COMM_H
#define _COMM_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define PATHNAME "."
#define PROJ_ID 64
#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf{
    long mtype;
    char mtext[1024];
};

int createMsgQueue();
int getMsgQueue();
int destroyMsgQueue(int msgid);
int sendMsg(int msgid, int who, char* msg);
int recvMsg(int msgid, int recvType, char out[]);

#endif
