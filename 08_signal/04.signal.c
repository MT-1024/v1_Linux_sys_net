#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void catch_signal_action(int i)
{
    printf("have catch signal , action: ......\n");
}

int main()
{
    /* C 标准版的sigaction() */
    /* catch_signal_action是回调函数 */
    signal(SIGINT, catch_signal_action);
    while(1)
    {
        printf("******************\n");
        sleep(1);
    }
    return 0;
}
