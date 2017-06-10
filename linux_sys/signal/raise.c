/*************************************************************************
	> File Name: raise.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

int count = 0;

void my_handler(int sig)
{
    printf("count: %d, sig: %d\n", count++, sig);
}

int main()
{
    signal(2, my_handler);
    while(1)
    {
        raise(2);
        sleep(1);
    }
    return 0;
}
