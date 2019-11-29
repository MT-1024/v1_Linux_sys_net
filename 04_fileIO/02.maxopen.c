//测试进程最大打开文件数量
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char name[1024];
    int i = 0;
    while(1)
    {
        sprintf(name, "file_%d", ++i);
        fd = open(name, O_CREAT , 0777);
        if(-1 == fd)
        {
            exit(1);
        }
        printf("%d\n", i);
    }
    return 0;
}
