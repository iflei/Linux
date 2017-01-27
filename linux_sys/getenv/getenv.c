/*************************************************************************
	> File Name: getenv.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
	> Created Time: Sat 15 Apr 2017 05:20:43 PM CST
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[])
{
    //第一种方法
    extern char** environ;
    int i = 0;
    while(environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }

    //第二种方法
    i = 0;
    while(env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }

    //第三种方法
    char* path = getenv("PATH");
    printf("path: %s\n", path);
    return 0;
}

