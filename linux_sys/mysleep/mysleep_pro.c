/*************************************************************************
	> File Name: mysleep.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

void my_handler(int sig)
{}

int mysleep(int timeout)
{
    struct sigaction act, oact;
    
    sigset_t mask;
    //信号集默认是全1的
    sigdelset(&mask, SIGALRM);//删除SIGALRM信号

    act.sa_handler = my_handler;//设置捕捉函数
    sigemptyset(&act.sa_mask);//清空信号屏蔽集
    sigaddset(&act.sa_mask, SIGALRM);//屏蔽SIGALRM
    act.sa_flags = 0;//默认0
    sigaction(SIGALRM, &act, &oact);//注册信号处理动作

    alarm(timeout);//设置闹钟
    sigsuspend(&mask); //解除对SIGALRM屏蔽，程序挂起，直到有信号递达
    int ret = alarm(0);//取消闹钟，返回上次闹钟剩余时间
    sigaction(SIGALRM, &oact, NULL);//恢复默认信号处理动作
    return ret;
}

int main()
{
    while(1)
    {
        mysleep(2);
        printf("use mysleep!\n");
    }
    return 0;
}
