/* 测试主机最大创建线程个数 */
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void * th_fun(void * arg)
{
    while(1)
    {
        sleep(1);
    }
}
int main()
{
    pthread_t tid;
    int i = 1, err;

    while(1)
    {
        /* 循环创建子线程 */
        err = pthread_create(&tid, NULL, th_fun, NULL);
        if(err != 0)
        {
            printf("%s\n", strerror(err));
            exit(1);
        }
        printf("%d\n", i++);
    }
    return 0;
}
