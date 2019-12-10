/* 孤儿进程 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int n = 5;
    pid_t pid = fork();
    if(pid > 0)
    {
        printf("I am parent\n");
        exit(0);
    }
    else if(pid == 0)
    {
        while(n--)
        {
            /* 父进程终止时，子进程的getppid()会发生改变 */
            printf("I am %d, my parent is %d\n", getpid(), getppid());
            sleep(1);
        }
    }
    else
    {
        perror("fork error");
        exit(-1);
    }
    return 0;
}
