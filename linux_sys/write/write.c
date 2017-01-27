/*************************************************************************
	> File Name: write.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main()
{
    char buf[] = "write to stdout\n";
    if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
        printf("write error!\n");

    return 0;
}
