/*************************************************************************
	> File Name: client.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include"comm.h"

int main()
{
    int shmid = getShm();
    char* buf = shmat(shmid, NULL, SHM_RDONLY);//只读
    int i = 0;
    while(i < 26)
    {
        printf("server: %s\n", buf);
        sleep(1);
    }

    shmdt(buf);
    destroyShm(shmid);
    return 0;
}
