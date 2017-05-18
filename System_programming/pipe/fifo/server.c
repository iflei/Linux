/*************************************************************************
	> File Name: server.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "comm.h"

int main()
{
    umask(0);
    if(mkfifo("./myfifo", S_IFIFO|0664) < 0)
        perror("mkfifo");

    int fd = open(PATHNAME, O_RDONLY); //读方式打开
    char buf[128];
    while(1)
    {
        ssize_t s = read(fd, buf, sizeof(buf)-1);
        if(s > 0)
        {
            buf[s] = 0;
            printf("%s\n", buf);
        }
        else
        {
            break;
        }
    }
    
    return 0;
}

