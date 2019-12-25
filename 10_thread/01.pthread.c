#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void * pthread_action(void *arg)
{
    int * p = (int *)arg;
    printf("func process id : %d\n", getpid());
    printf("thread ID : %lu\n", pthread_self());
    printf("*arg = %d\n", *p);
    /* while(1); */
}

int main()
{
    int n = 888;

    /* 记录pthread_create如果未成功的错误码 */
    int err;

    pthread_t tid;
    /* 1.创建线程 2.线程号填写到tid 3.返回函数调用 */
    err = pthread_create(&tid, NULL, pthread_action, (void *)&n);
    if(err != 0)
    {
        fprintf(stderr, "can't create thread : %s\n", strerror(err));
        exit(1);
    }
    printf("main process id : %d\n", getpid());
    printf("main thread id : %lu\n", pthread_self());
    printf("main create child thread is : %lu\n", tid);
    /* while(1); */
    /* 要求主线程比子线程晚退出 */
    /* 防止主进程先结束释放PCB，导致子线程PCB也被释放 */
    sleep(1);
    
    return 0;
}
