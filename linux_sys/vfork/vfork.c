/*************************************************************************
	> File Name: vfork.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int g_var = 6;

int main()
{

    int var = 88;
    int pid;
    printf("before vfrk\n");
    if((pid = vfork()) < 0)
        printf("vfork error\n");
    else if(pid == 0)
    {
        g_var++;
        var++;
        _exit(0);
    }
    printf("g_var: %d, var: %d\n", g_var, var);
    return 0;
}
