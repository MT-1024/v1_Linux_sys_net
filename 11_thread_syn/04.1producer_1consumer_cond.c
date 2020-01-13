//条件变量实现单生产者，单消费者，n缓冲区模型
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void err_pthread(int, const char *);
void * consumter(void *);
void * producer(void *);

struct node
{
    int data;
    struct node * next;
};

typedef struct node Node;

//定义头地址
Node * head = NULL;

pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;     //静态初始化互斥量
pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;     //初始化条件变量

//线程函数检查错误
void err_pthread(int ret, const char * str)
{
    if(ret != 0)
    {
        fprintf(stderr, "%s error:%s\n", str, strerror(ret));
        pthread_exit(NULL);
    }
}

void * consumter(void * arg)
{
    while(1)
    {
        pthread_mutex_lock(&mymutex);   //加锁互斥量
        if(NULL == head)
        {
            pthread_cond_wait(&mycond, &mymutex);     //阻塞等待条件变量
            //阻塞等待mycond被唤醒
            //临界区没有产品，应该解锁pthread_mutex_unlock(&mymutex)并且让生产者获得临界区;
            //当被唤醒时，解除阻塞，并且重新去申请获得互斥锁 pthread_mutex_lock(&mymutex) 
        }

        //从头指针指向的节点开始删除
        printf("---consumer:[%d]\n", head->data);
        Node * temp = head;
        head = head->next;

        pthread_mutex_unlock(&mymutex);

        free(temp);
        temp = NULL;

        sleep(rand() % 3); 
    }
    return NULL;
}

void * producer(void * arg)
{
    while(1)
    {
        Node * tempnode = (Node *)malloc(sizeof(Node));
        tempnode->data = rand() % 1000 + 1;     //1~1000
        printf("producer:[%d]\n", tempnode->data);
        pthread_mutex_lock(&mymutex);   //加锁互斥量

        //头插法建立链表，head不断移动，指向新创建的节点
        tempnode->next = head;
        head = tempnode;

        pthread_mutex_unlock(&mymutex);      //解锁互斥量
        pthread_cond_signal(&mycond);     //通知pthread_cond_wait()

        sleep(rand() % 3);     //睡眠几秒，让出cpu时间片给消费者线程
    }
    return NULL;
}

int main()
{
    srand(time(NULL));     //随机数种子
    pthread_t producer_thread, consumer_thread;
    int ret;

    ret = pthread_create(&producer_thread, NULL, producer, NULL);     //创建生产者线程
    err_pthread(ret, "pthread_create");
    ret = pthread_create(&consumer_thread, NULL, consumter, NULL);     //创建消费者线程
    err_pthread(ret, "pthread_create");


    pthread_join(producer_thread, NULL);     //回收生产者线程
    pthread_join(consumer_thread, NULL);     //回收消费者线程

    pthread_cond_destroy(&mycond);
    pthread_mutex_destroy(&mymutex);

    return 0;
}
