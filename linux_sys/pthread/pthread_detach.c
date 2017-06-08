/*************************************************************************
	> File Name: pthread.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <pthread.h>

void* thread_run(void* arg)
{
    printf("thread running...\n");
    sleep(1);
    return NULL;
}

int main()
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, thread_run, NULL))
    {
        perror("pthread_creare");
        return -1;
    }
    sleep(3);
    pthread_detach(tid);//线程分离
    return 0;
}
