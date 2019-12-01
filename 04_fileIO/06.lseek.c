#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main()
{
    int fd = open("test1", O_RDWR | O_TRUNC);
    if(fd == -1)
    {
        perror("open test1 error");
        exit(-1);
    }

    //1 lseek()可以拓展文件大小
    //拓展一个文件，一定要有一次写操作
    lseek(fd, 0x1000, SEEK_SET);
    write(fd, "a", 1);
    close(fd);

    //2 lseek()可以统计文件大小
    fd = open("test2", O_RDWR);
    if(fd == -1)
    {
        perror("open test2");
        exit(-1);
    }
    printf("test2 file size of bytes : %ld\n", lseek(fd, 0, SEEK_END)); 
    close(fd);
    
    return 0;
}
