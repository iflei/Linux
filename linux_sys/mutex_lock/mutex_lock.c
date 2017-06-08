/*************************************************************************
	> File Name: mutex_lock.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int g_val = 0;

void* pthread_run(void* arg)
{
    int i = 0;
    while(i++ < 500000)
    {
        pthread_mutex_lock(&mutex);
        //g_val++;
        int tmp = g_val;
        g_val = tmp + 1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t tid1;
    pthread_t tid2;
    pthread_create(&tid1, NULL, &pthread_run, NULL);
    pthread_create(&tid2, NULL, &pthread_run, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("g_val: %d\n", g_val);
    return 0;
}
