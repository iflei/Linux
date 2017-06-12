/*************************************************************************
	> File Name: Asynchronous_wait.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler(int sig)
{
    pid_t id; 
    while((id = waitpid(-1, NULL, WNOHANG)) > 0)
    {
        printf("wait child success: %d\n", id);
    }
}

int main()
{
    signal(SIGCHLD, handler);
    //fork第一个进程
    if(fork() == 0)
    {
        printf("first child pid: %d\n", getpid());
        sleep(3);
        exit(1);
    }
    //fork第二个进程
    if(fork() == 0)
    {
        printf("second child pid: %d\n", getpid());
        sleep(4);
        exit(1);
    }
    //fork第三个进程
    if(fork() == 0)
    {
        printf("third child pid: %d\n", getpid());
        sleep(5);
        exit(1);
    }
    while(1)
    {
        sleep(3);
        printf("father do some other things... %d\n", getpid());
    }
    return 0;
}
