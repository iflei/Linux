/*************************************************************************
	> File Name: fork.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    printf("before fork"); 
    //会输出两次，因为缓冲区为刷新，并且继承给了子进程
    pid_t id;
    if((id=fork()) < 0)
        printf("fork error: %d\n", errno);
    else if(id == 0)
        exit(0);
    else
        sleep(3);

    return 0;
}
