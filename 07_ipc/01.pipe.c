/* pipe */
/* pipe适用于有父子血缘关系进程间通信，pipe()常和fork()联用 */
/* 调用pipe后会在内核中开辟一个专门用于父子进程间通信的缓冲区 */
/* 父子进程都会有2个fd指向该缓冲区 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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
    
    char buf1[4096] = "hello world";
    char buf2[4096];
    pid = fork();
    /* 人为规定父写子读 */
    if(pid > 0)
    {
        /* parent process */
        /* 关闭父读端 */
        close(fd[0]);
        /* 父将buf1数据写入pipe缓冲区 */
        write(fd[1], buf1, strlen(buf1));
        close(fd[1]);
        wait(NULL);
    }
    else if(pid == 0)
    {
        /* child process */
        /* 关闭子写端 */
        close(fd[1]);
        int read_length;
        read_length = read(fd[0], buf2, sizeof(buf2));
        close(fd[0]);
        write(STDOUT_FILENO, buf2, read_length);
        /* printf("child read content : %s\n", buf2); */
    }

    return 0;
}
