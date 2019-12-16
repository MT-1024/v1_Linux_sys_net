/* 创建一个named pipe用于无血缘进程间通信 */
/* 向Named fifo中写入数据 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void my_error(char * str, int exitno)
{
    perror(str);
    exit(exitno);
}

int main(int argc, char * argv[])
{
    /* 输入错误 */
    if(argc < 2)
    {
        printf("Please enter format like this : ./a.out xx\n");
        exit(1);
    }

    /* 创建named pipe */
    mkfifo(argv[1], 0664);
    int fd = open(argv[1], O_WRONLY);
    if(-1 == fd)
    {
       my_error("open error", 1); 
    }
    
    char buf[4096] = "hello World\n";
    /* 将buf中的数据写入fd */
    write(fd, buf, strlen(buf));
    close(fd);
    return 0;
}
