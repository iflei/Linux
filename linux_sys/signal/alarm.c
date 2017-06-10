/*************************************************************************
	> File Name: alarm.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int count = 0;
void my_handler(int sig)
{
    printf("count is: %d\n", count);
    exit(1);
}

int main()
{
    signal(SIGALRM, my_handler);
    alarm(1);
    while(1)
        count++;
    return 0;
}
