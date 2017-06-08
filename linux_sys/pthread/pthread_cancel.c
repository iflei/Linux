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
    while(1)
    {
        printf("thread running...wait canceled...\n");
        sleep(1);
    }
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
    pthread_cancel(tid); //线程取消
    
    void* exitCode;
    int err;
    if(err = pthread_join(tid, &exitCode))
    {
        printf("pthread_join: %s\n",strerror(err));
        return -2;
    }
    printf("pthread exitCode: %d\n", (int*)exitCode);
    return 0;
}
