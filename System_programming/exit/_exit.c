/*************************************************************************
	> File Name: _exit.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("hello");
    _exit(0);
    //函数_exit（）会立即终止调用进程。 
    //属于该过程的任何打开的文件描述符都将关闭; 
    //进程的任何子进程都由进程1继承，
    //进程的父进程发送一个SIGCHLD信号。
}
