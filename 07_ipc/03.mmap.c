/* 需要先创建一个文件 */
/* 通过mmap在内存上创建磁盘文件的映射区，通过修改映射区从而修改磁盘文件 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

void my_error(char * str, int exitno)
{
    perror(str);
    exit(exitno);
}

int main()
{
    /* 创建内存映射区之前需要先打开文件 */
    int fd = open("tempbuffer", O_RDWR);
    if(-1 == fd)
    {
       my_error("open error", 1); 
    }
    
    /* 获取文件大小 */
    int file_length = lseek(fd, 0, SEEK_END);
    /* 创建内存映射区 */
    char * p = (char *)mmap(NULL, file_length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
    p[0] = 'Q';
    munmap(p, file_length);
    close(fd);
    return 0;
}
