#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int n = 3;
    /* 1个父进程,fork三个子进程 */
    while(n--)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
    }

    if(pid == 0)
    {
        while(1)
        {
            printf("I am child %d\n", getpid());
            sleep(3);
        }
    }
    else if(pid > 0)
    {
        pid_t pid_c;
        /* 父进程不停的回收子进程 */
        while(1)
        {
            /* 记录父进程回收的子进程的进程id */
            /* WNOHANG表示waitpid不阻塞等待回收子进程 */
            pid_c = waitpid(0, NULL, WNOHANG);
            /* 回收失败 */
            if(pid_c == -1)
            {  
                break;
            }
            else
            {
                printf("wait child id is %d\n", pid_c);
                sleep(2);
            }
        }
    }
}
