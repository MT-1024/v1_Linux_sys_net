#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void * thread_action(void * arg)
{
    int n = 10;
    while(n--)
    {
        printf("pthread_no : %x ; %d\n", (int)pthread_self(), n);
        sleep(1);
    }
    return (void *)1;
}

int main()
{
    pthread_t tid;
    pthread_attr_t attr;
    int err;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    /* 创建默认为分离属性的子线程 */
    pthread_create(&tid, &attr, thread_action, NULL);
    /* 主线程回收子线程 */
    err = pthread_join(tid, NULL);
    while(1)
    {
        if(err != 0)
        {
            printf("%s\n", strerror(err));
            pthread_exit((void *)1);
        }
    }
    return 0;
}
