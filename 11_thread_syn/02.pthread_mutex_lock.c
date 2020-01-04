/* 多线程对全局变量操作 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define LOOP 5000

/* 全区变量锁,直接宏初始化, 或者可以在main()内调用pthread_mutex_init()初始化 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int count;

void * thread_action(void * arg)
{
    int val;
    for(int i = 0; i < LOOP; i++)
    {
        pthread_mutex_lock(&mutex);
        val = count;
        printf("thread.no=%x ; count=%d\n", (unsigned int)pthread_self(), val + 1);
        count = val + 1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    /* 定义一把局部锁 */
    /* pthread_mutex_t mutex; */
    /* pthread_mutex_init(&mutex, NULL); */

    pthread_t tidA, tidB;
    pthread_create(&tidA, NULL, &thread_action, NULL);
    pthread_create(&tidB, NULL, &thread_action, NULL);

    /* 回收子线程 */
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
