/*************************************************************************
	> File Name: exec.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char* env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main()
{
    pid_t pid;
    if((pid = fork()) < 0)
        printf("fork error\n");
    else if(pid == 0)
        if(execle("/bin/ls", "ls", "-a", "-l", "-h", (char*)0, env_init) < 0)
            printf("execle error\n");
    else
        if(waitpid(pid, NULL, 0) < 0)
            printf("waitpid error\n");

    
    if((pid = fork()) < 0)
        printf("fork error\n");
    else if(pid == 0)
        if(execlp("ls", "ls", (char*)0) < 0)
            printf("execlp error\n");
    else
        if(waitpid(pid, NULL, 0) < 0)
            printf("waitpid error\n");

    return 0;
}
