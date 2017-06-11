/*************************************************************************
	> File Name: pending.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

void show_pending(sigset_t* pending)
{
    int i = 1;
    while(i <= 31)
    {
        if(sigismember(pending, i))
            printf("1 ");
        else
            printf("0 ");

        i++;
    }
    printf("\n");
}

void my_handler(int sig)
{
    printf("sig: %d\n", sig);
}

int main()
{
    sigset_t sigset, osigset;
    sigemptyset(&sigset); //清空信号集
    sigemptyset(&osigset);
    sigaddset(&sigset, 2); //添加2号信号到信号集中
    //将信号屏蔽字修改为sigset，并把原信号屏蔽字备份到osigset
    sigprocmask(SIG_SETMASK, &sigset, &osigset);
    signal(2, my_handler);

    sigset_t pending;
    int count = 1;
    while(1)
    {
        sigpending(&pending);
        show_pending(&pending);
        
        if(count++ > 3)
        {
            //3秒后把信号屏蔽字改回去
            sigprocmask(SIG_SETMASK, &osigset, NULL);
        }
        sleep(1);
    }
    return 0;
}
