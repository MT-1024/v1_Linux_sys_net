//wait()一般在父进程中调用，用于回收子进程的PCB
//wait()是阻塞函数, 如果子进程不结束，父进程的wait()会一直等待子进程结束，并且回收子进程PCB
//wait(int * status), status是传出参数，保存的是子进程退出信息
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


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
        sleep(20);
        /*wait()是阻塞函数，等待子进程执行完才会被唤醒执行*/
        printf("wait child : %d\n", wait(NULL));
    }
    else if(pid == 0)
    {
        /* int child */
        printf("I am child, pid:%d\n", getpid());
        sleep(10);
    }
    return 0;
}
