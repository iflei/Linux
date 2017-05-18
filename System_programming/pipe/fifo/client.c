/*************************************************************************
	> File Name: client.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "comm.h"

int main()
{
    int fd = open("./myfifo", O_WRONLY);//写方式打开
    char buf[128];
    while(1)
    {
        ssize_t s = read(0, buf, sizeof(buf-1));//从键盘读
        if(s > 0)
        {
            buf[s-1] = 0;
            write(fd, buf, strlen(buf));
        }
    }
    return 0;
}
