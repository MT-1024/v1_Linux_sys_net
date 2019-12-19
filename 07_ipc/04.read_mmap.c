#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

/* #define MMAP_SIZE 4096 */

void my_error(char * str, int exitno)
{
    perror(str);
    exit(exitno);
}

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Please enter format like this : ./a.out xxx\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDWR, 0664);
    if(fd < 0)
    {
        my_error("open error", 1);
    }

    /* lseek获取文件大小 */
    int mmap_length = lseek(fd, 0, SEEK_END);

    char * p = (char *)mmap(NULL, mmap_length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
    if(MAP_FAILED == p) 
    {
        my_error("mmap error", 2);
    }
    close(fd);

    /* 删除创建的临时文件 */
    unlink(argv[1]);

    /* 从mmap内存映射区读取数据 */
    while(1)
    {
        printf("mmap content : %s\n", p);
        sleep(1);
    }

    /* 释放内存映射区 */
    munmap(p, mmap_length);


    return 0;
}

