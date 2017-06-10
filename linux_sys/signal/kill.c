/*************************************************************************
	> File Name: kill.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>

//使用格式说明
static void usage(const char* proc)
{
    printf("Usage: %s sig pid\n", proc);
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        return 1;
    }
    int sig = atoi(argv[1]);
    int pid = atoi(argv[2]);
    kill(pid, sig);
    return 0;
}
