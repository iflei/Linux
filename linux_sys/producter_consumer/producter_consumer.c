/*************************************************************************
	> File Name: producter_consumer.c
	> Author: iflei
	> Mail: admin@iflei.com
	> Blog: www.iflei.com
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct _node
{
    int data;
    struct _node* next;
}node_t, *node_p, **node_pp;

//有头结点的链表
node_p head = NULL;
//互斥锁
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//条件变量
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 

static node_p alloc_node(int _d)
{
    node_p node = (node_p)malloc(sizeof(node_t));
    if(!node)
    {
        perror("malloc");
        exit(1);
    }

    node->data = _d;
    node->next = NULL;
    return node;
}

static free_node(node_p _n)
{
    if(_n)
    {
        free(_n);
        _n = NULL;
    }
}

int isEmpty(node_p _h)
{
    return _h->next == NULL ? 1 : 0;
}

void initList(node_pp _h)
{
    *_h = alloc_node(0);
}

void pushHead(node_p _h, int _d)
{
    node_p _n = alloc_node(_d);
    _n->next = _h->next;
    _h->next = _n;
}

void popHead(node_p _h, int* _x)
{
    if(!isEmpty(_h))
    {
        node_p _n = _h->next;
        _h->next = _n->next;
        *_x = _n->data;
        free_node(_n);
    }
}

void showList(node_p _h)
{
    node_p start = _h->next;
    while(start)
    {
        printf("%d ", start->data);
        start = start->next;
    }
    printf("\n");
}

void destroyList(node_p _h)
{
    int data = 0;
    while(!isEmpty)
    {
        popHead(_h, &data);
    }
    free_node(_h);
}

void* consume(void* arg)
{
    int data = -1;
    int i = 0;
    while(i++ < 15)
    {
        pthread_mutex_lock(&lock);//加锁
        if(isEmpty(head))
        {
            pthread_cond_wait(&cond, &lock);//无锁等待 
        }
        popHead(head, &data);
        printf("consumer done... %d\n", data);
        pthread_mutex_unlock(&lock);//解锁
    }
}

void* product(void* arg)
{
    int i = 0;
    while(i++ < 15)
    {
        pthread_mutex_lock(&lock);//加锁
        int data = rand()%1024;
        pushHead(head, data);
        printf("producter done... %d\n", data);
        pthread_mutex_unlock(&lock);//解锁
        pthread_cond_signal(&cond);//唤醒等待的线程
        sleep(1);
    }
}

int main()
{
    initList(&head);
    pthread_t consumer, producter;
    pthread_create(&consumer, NULL, consume, NULL);
    pthread_create(&producter, NULL, product, NULL);
    
    pthread_join(consumer, NULL);
    pthread_join(producter, NULL);

    destroyList(head);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
