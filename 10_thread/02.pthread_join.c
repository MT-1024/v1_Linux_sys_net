/* 回收线程 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thr_fn1(void *arg)
{
    printf("thread 1 returning\n");
    return (void *)1;

}
void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);

}
void *thr_fn3(void *arg)
{
    while(1)
    {
        printf("thread 3 writing\n");
        sleep(1);

    }
}
int main(void)
{
    pthread_t tid;

    /* 存子线程结束时的返回值 */
    void *tret;
    pthread_create(&tid, NULL, thr_fn1, NULL);
    /* 回收子线程，tret中保存的是回收掉的线程的返回值 */
    pthread_join(tid, &tret);
    printf("thread 1 exit code %d\n", (int)tret);

    pthread_create(&tid, NULL, thr_fn2, NULL);
    pthread_join(tid, &tret);
    printf("thread 2 exit code %d\n", (int)tret);
    
    pthread_create(&tid, NULL, thr_fn3, NULL);
    sleep(3);
    /* 终止子线程 */
    pthread_cancel(tid);
    pthread_join(tid, &tret);
    printf("thread 3 exit code %d\n", (int)tret);
    return 0;

}
