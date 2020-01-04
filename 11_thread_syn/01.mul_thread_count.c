/* 多线程对全局变量操作造成的混乱 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define LOOP 5000

int count;

void * thread_action(void * arg)
{
    int val;
    for(int i = 0; i < LOOP; i++)
    {
        val = count;
        printf("thread.no=%x ; count=%d\n", (unsigned int)pthread_self(), val + 1);
        count = val + 1;
    }
    return NULL;
}

int main()
{
    pthread_t tidA, tidB;
    pthread_create(&tidA, NULL, &thread_action, NULL);
    pthread_create(&tidB, NULL, &thread_action, NULL);

    /* 回收子线程 */
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);
    return 0;
}
