/*************************************************************************
	> File Name: atexit.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

void exitfunc1()
{
    printf("exitfunc1\n");
}

void exitfunc2()
{
    printf("exitfunc2\n");
}

void exitfunc3()
{
    printf("exitfunc3\n");
}

int main()
{
    atexit(exitfunc1);
    atexit(exitfunc2);
    atexit(exitfunc3);
    atexit(exitfunc3);
    return 0;
}
