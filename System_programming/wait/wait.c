/*************************************************************************
	> File Name: wait.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_exit(int status)
{
    if(WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
        #ifdef WCOREDUMP
               WCOREDUMP(status)? "(core file generated)" : "");
        #else
            "");
        #endif

    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main()
{
    pid_t pid;
    int status;

    if((pid = fork()) < 0)
        printf("fork error\n");
    else if(pid == 0)
        exit(0);

    if(wait(&status) != pid)
        printf("wait error\n");
    
    print_exit(status);

    if((pid = fork()) < 0)
        printf("fork error\n");
    else if(pid == 0)
        abort();

    if(wait(&status) != pid)
        printf("wait error\n");
    
    print_exit(status);

    if((pid = fork()) < 0)
        printf("fork error\n");
    else if(pid == 0)
    {
        int a = 10 / 0;;
    }

    if(wait(&status)!= pid)
        printf("wait error\n");
    
    print_exit(status);
    
    return 0;
}
