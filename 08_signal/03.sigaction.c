#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void catch_sig_action(int num)
{
    printf("catch signal : %d\n", num);
}

int main()
{
    struct sigaction act;

    /* 捕捉信号后执行catch_sig_action */
    act.sa_handler = catch_sig_action;

    /* 指定捕捉信号后执行默认动作 */
    /* act.sa_handler = SIG_DFL; */

    /* 内核在执行某信号对应动作过程中，此时不会处理sa_mask中设置了屏蔽的信号；主要防止信号处理嵌套 */
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    /* 捕捉到SIGINT信号后，执行相应动作 catch_sig_action */
    sigaction(SIGINT, &act, NULL);

    while(1)
    {
        /* 模拟一直在运行的进程，在收到SIGINT信号后，进行捕捉，并执行相应的动作 */
        printf("************\n");
        sleep(1);
    }

    return 0;
}
