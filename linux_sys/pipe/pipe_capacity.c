/*************************************************************************
	> File Name: testpipe.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int pipefd[2];
    if(pipe(pipefd)==-1)
    {
        perror("pipe");
        exit(1);
    }
    
    int size = 0;
    fcntl(pipefd[1], F_SETFL, O_NONBLOCK );
    while(1==write(pipefd[1], "a", 1))
        size++;

    printf("pipe size is: %d\n", size);
    return 0;
}
