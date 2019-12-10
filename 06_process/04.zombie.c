//僵尸进程：如果由fork()产生的子进程结束时，如果没有父进程回收，那么子进程会变成僵尸进程
//僵尸进程仅仅释放了0~3G地址空间，在内核汇中的PCB并没有释放
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    pid_t pid = fork();
    if(pid < 0)    
    {
        perror("fork error");
    }
    else if(pid > 0)
    {
        /* int parent */
        printf("I am parent, pid:%d\n", getpid());
        /* 父进程睡眠20秒期间，子进程已经执行完,没有被回收，ps aux会显示子进程为僵尸进程 */
        sleep(20);

    }
    else if(pid == 0)
    {
        /* int child */
        printf("I am child, pid:%d\n", getpid());
    }
    return 0;
}
