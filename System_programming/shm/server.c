/*************************************************************************
	> File Name: server.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include "comm.h"

int main()
{
    int shmid = creatShm(4096);
    char* buf = (char*)shmat(shmid, NULL, 0);//以读写挂接
    int i = 0;
    sleep(5);
    while(i < 26)
    {
        buf[i] = 'A' + i;
        buf[++i] = '\0';
        sleep(1);
    }
    
    shmdt(buf);
    destroyShm(shmid);
    return 0;
}
