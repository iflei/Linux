/*************************************************************************
	> File Name: rwlock.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int book = 0;
pthread_rwlock_t rwlock;

void* myread(void* arg)
{
    sleep(2);//让写者先写
    while(1)
    {
        //这里不用阻塞式否则会造成对方饥渴
        if(pthread_rwlock_tryrdlock(&rwlock) != 0)
            printf("wtiter is writing...tid: %u\n", pthread_self());
        else
        {
            printf("book is: %d, tid: %u\n", book, pthread_self());
            pthread_rwlock_unlock(&rwlock);
        }
        sleep(2); //读完需要2秒
    }
    return NULL;
}

void* mywrite(void* arg)
{
    while(1)
    {
        //这里不用阻塞式否则会造成对方饥渴
        if(pthread_rwlock_trywrlock(&rwlock) != 0) 
            printf("reader is reading...,tid: %u\n", pthread_self());
        else
        {
            book++;
            printf("write done: %d, tid: %u\n", book, pthread_self());
            pthread_rwlock_unlock(&rwlock);
        }
        sleep(3);//写完需要3秒
    }
    return NULL;
}

int main()
{
    pthread_rwlock_init(&rwlock, NULL);//读写锁初始化
    pthread_t reader1, reader2, writer; //两个读者一个写者
    pthread_create(&reader1, NULL, myread, NULL);
    pthread_create(&reader2, NULL, myread, NULL);
    pthread_create(&writer, NULL, mywrite, NULL);
    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);
    pthread_join(writer, NULL);
    pthread_rwlock_destroy(&rwlock);//销毁读写锁
    return 0;
}
