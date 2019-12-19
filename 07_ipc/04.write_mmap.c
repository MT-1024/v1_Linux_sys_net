#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define MMAP_SIZE 4096
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

    int fd = open(argv[1], O_RDWR | O_CREAT, 0664);
    if(fd < 0)
    {
        my_error("open error", 1);
    }

    /* 将磁盘文件映射到内存 */
    lseek(fd, MMAP_SIZE - 1, SEEK_SET);
    write(fd ,"\0", 1);

    char * p = (char *)mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
    if(MAP_FAILED == p) 
    {
        my_error("mmap error", 2);
    }
    close(fd);

    /* 输入数据到mmap映射区 */
    int i = 0;
    while(1)
    {
        sprintf(p, "hello world %d;", i++);
        sleep(1);
    }

    /* 释放内存映射区 */
    munmap(p, MMAP_SIZE);


    return 0;
}

