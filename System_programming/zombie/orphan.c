/*************************************************************************
	> File Name: orphan.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    pid_t id = fork();
    if(id == -1)
    {
        printf("fork error! errno: %d\n", errno);
        return 2;
    }
    else if(id == 0)
    {
        printf("child pid: %d\n", getpid());
        sleep(20);
    }
    else
    {
        printf("father pid: %d\n", getpid());
        sleep(3);
        exit(3);
    }
    return 0;
}
