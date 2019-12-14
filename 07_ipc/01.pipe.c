/* pipe */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    /* 用于存放pipe缓冲区的文件描述符 */
    /* fd[0]是读端，fd[1]是写端 */
    int fd[2];
    pid_t pid;
    if(pipe(fd) < 0)
    {
        perror("pipe error");
        exit(1);
    }
    
    char buf[4096];
    pid = fork();
    /* 人为规定父写子读 */
    if(pid > 0)
    {
        /* in parent */
        /* 关闭父读端 */
        close(fd[0]);
        /* 父开始写数据 */
        write(fd[1], buf, strlen(buf));
    }

    return 0;
}
