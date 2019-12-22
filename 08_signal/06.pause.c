#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void catch_signal_action(int i)
{
    /* do nothing */
}

int main()
{
    struct sigaction act;
    /* act.sa_handler = catch_signal_action; */
    act.sa_handler = SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGUSR1, &act, NULL);
    pause();

    printf("hello world\n");
    return 0;
}
