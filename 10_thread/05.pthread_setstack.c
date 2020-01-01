#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
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
    int err;
    /* pthread_attr_t是一个结构体 */
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    void * stackaddr;
    size_t stacksize;
    pthread_attr_getstack(&attr, &stackaddr, &stacksize);
    /* 打印出stackaddr为NULL，表示默认地址，不表示地址是0 */
    printf("default stackaddr : %p\n", stackaddr);
    /* 打印出stacksize为0，表示默认栈大小，不表示大小是0 */
    printf("default stacksize : %ld\n", stacksize);


    /* 设置线程属性默认为分离态 */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);


    /* 分配1M的内存空间给栈 */
    stackaddr = malloc(0x100000);
    stacksize = 0x100000;
    pthread_attr_setstack(&attr, stackaddr, stacksize);


    /* **************以上都是设置线程属性******************** */
    pthread_create(&tid, &attr, thread_action, NULL);
    /* 回收子线程 */
    pthread_join(tid, NULL);
    return 0;
}
