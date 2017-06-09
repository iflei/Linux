/*************************************************************************
	> File Name: ring_producter_consumer.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int ring[32];
sem_t blank_sem;
sem_t data_sem;

void* product(void* arg)
{
    int step = 0;
    while(1)
    {
        sem_wait(&blank_sem); //P
        int data = rand()%1024;
        ring[step++] = data;
        sem_post(&data_sem); //V
        step %= 32;
        printf("product done... %d\n", data);
        usleep(100000);
    }
}

void* consume(void* arg)
{
    int step = 0;
    while(1)
    {
        sem_wait(&data_sem); //P
        int data = ring[step++];
        sem_post(&blank_sem); //V
        step %= 32;
        printf("consume done... %d\n", data);
        usleep(600000); //让消费者慢些
    }
}

int main()
{
    sem_init(&blank_sem, 0, 32);
    sem_init(&data_sem, 0, 0);

    pthread_t producter, consumer;
    pthread_create(&producter, NULL, product, NULL);
    pthread_create(&consumer, NULL, consume, NULL);

    pthread_join(producter, NULL);
    pthread_join(consumer, NULL);

    sem_destroy(&blank_sem);
    sem_destroy(&data_sem);
    return 0;
}
