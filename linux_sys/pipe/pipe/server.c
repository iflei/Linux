#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefd[2];
    if(pipe(pipefd) < 0)
        perror("pipe");

    
    pid_t id = fork();
    if(id < 0)
        perror("fork");
    else if(id == 0)
    {
        //子进程写
        close(pipefd[0]);
        char* msg = "hello father";
        int i = 0;
        while(i < 10)
        {
            write(pipefd[1], msg, strlen(msg));
            sleep(1);
            i++;
        }
    }
    else
    {
        //父进程读
        close(pipefd[1]);
        char buf[128];
        while(1)
        {
            ssize_t s = read(pipefd[0], buf, sizeof(buf));
            if(s > 0)
                buf[s] = 0;
            else
            {
                break;
            }
            printf("%s\n", buf);
        }
    }
    return 0;
}
