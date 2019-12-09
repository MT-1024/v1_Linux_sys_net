#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    pid_t pid;
    //fork()调用一次返回两次，在父进程中返回子进程的pid，在子进程中返回0
    pid = fork();
    if(pid > 0)
    {
        /* in parent process */
        printf("I am parent\n");
        printf("my pid = %d\n", getpid());
        printf("my ppid = %d\n", getppid());
        while(1);
    }
    else if(pid == 0)
    {
        /* in child process */
        printf("I am child\n");
        printf("my pid = %d\n", getpid());
        printf("my ppid = %d\n", getppid());
        while(1);
    }
    else if(pid == -1)
    {
        perror("forkk error");
        exit(1);
    }
    return 0;
}
