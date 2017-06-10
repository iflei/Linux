/*************************************************************************
	> File Name: test.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

typedef void(*sighandler_t)(int);
sighandler_t _handler = NULL;

void my_handler(int sig)
{
    printf("this is handler, signum is %d\n", sig);
    signal(2, _handler);
}
int main()
{
    _handler = signal(2, my_handler);
    while(1);
    return 0;
}
