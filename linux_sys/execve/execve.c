
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    char* argv[] = {"/bin/ls", "-l", "-h"};
    execve("/bin/ls", argv, NULL);
    printf("end\n");
    return 0;
}
