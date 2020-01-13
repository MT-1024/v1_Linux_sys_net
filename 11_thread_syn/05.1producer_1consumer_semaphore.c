/* 信号量机制实现单生产者和单消费者模型 */
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

/* 定义一个环形队列，长度为5 */
#define NUM 5
int queue[NUM];

/* 描述仓库的空位的信号量 */
sem_t blank_number;
/* 描述仓库中产品的个数的信号量 */
sem_t product_number;

void *producer(void *arg)
{
    int p = 0;
    while (1) {
        sem_wait(&blank_number);
        queue[p] = rand() % 1000 + 1;
        printf("Produce %d\n", queue[p]);
        sem_post(&product_number);
        p = (p+1)%NUM;
        sleep(rand()%5);
    }
    
}
void *consumer(void *arg)
{
    int c = 0;
    while (1) {
        sem_wait(&product_number);
        printf("Consume %d\n", queue[c]);
        queue[c] = 0;
        sem_post(&blank_number);
        c = (c+1)%NUM;
        sleep(rand()%5);
        
    }
    
}
int main(int argc, char *argv[])
{
    pthread_t pid, cid;
    /* 信号量blank_number大小初始化为NUM */
    /* 第二个参数为0，表示该信号量用于线程间通信 */
    sem_init(&blank_number, 0, NUM);
    /* 信号量product_number大小初始化为0 */
    sem_init(&product_number, 0, 0);
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
    sem_destroy(&blank_number);
    sem_destroy(&product_number);
    return 0;
}
