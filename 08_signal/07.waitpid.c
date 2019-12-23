/* 通过信号回收子进程 */
/* 子进程结束时，发SIGCHLD给父进程，通知父进程回收子进程的PCB */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void catch_signal_action(int signo)
{
    int status;
    pid_t pid;

    /* waitpid回收成功，返回被回收子进程的pid */
    while((pid = waitpid(0, &status, WNOHANG)) > 0)
    {
        if(WIFEXITED(status))
        {
            printf("child %d exit %d\n", pid, WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status))
        {
            printf("child %d cancel signal %d\n", pid, WTERMSIG(status));
        }

    }
}

int main()
{
    pid_t pid;
    int i ;
    for(i = 0; i < 10; i++)
    {
        if((pid = fork()) == 0)
        {
            break;
        }
        else if(pid < 0)
        {
            perror("fork error");
            exit(1);
        }
    }


    if(pid == 0)
    {
        /* in child */
        int n = 8;
        while(n--)
        {
            printf("child ID : %d\n", getpid());
            sleep(1);
        }
        return i;
    }
    else if(pid > 0)
    {
        /* in parent */

        struct sigaction act;
        act.sa_handler = catch_signal_action;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGCHLD, &act, NULL);

        while(1)
        {
            printf("parent ID : %d\n", getpid());
            sleep(1);
        }
    }
}
