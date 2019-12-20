#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void printsigset(const sigset_t * set);

int main()
{
    /* 自定义信号集myset */
    /* pend_set用于保存未决信号集 */
    sigset_t myset, pend_set;
    printf("sizeof(sigset_t) = %ld\n", sizeof(sigset_t));

    /* 先将自定义信号集全部清0 */
    sigemptyset(&myset);

    /* 添加SIGINT到自定义信号集 */
    sigaddset(&myset, SIGINT);

    /* 将自定义信号集与进程pcb中的阻塞信号集 ‘与’ 操作 */
    sigprocmask(SIG_BLOCK, &myset, NULL);

    while(1)
    {
        /* 获取PEND未决信号集保存到pend_set中 */
        sigpending(&pend_set);
        printsigset(&pend_set);
        sleep(1);
    }
    return 0;
}

/* 打印1~31号信号集 */
void printsigset(const sigset_t * set)
{
    for(int i = 1; i< 32; i++)
    {
        /* 如果信号在未决信号集中，打印1 */
        if(sigismember(set, i) == 1)
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
    }
    printf("\n");
}
