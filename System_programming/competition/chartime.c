/*************************************************************************
	> File Name: competition.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

//存在竞争
void chartime(char* str)
{
    char* p;
    int ch;
   
    setbuf(stdout, NULL);
    for(p = str; (ch = *p++) != '\0'; )
    { 
        putc(ch, stdout);
        sleep(1);
    }
}

int main()
{

    pid_t pid;
    if((pid = fork()) < 0)
        printf("fork error\n");
    else if(pid == 0)
        chartime("child\n");
    else
        chartime("parent\n");

    return 0;
}
