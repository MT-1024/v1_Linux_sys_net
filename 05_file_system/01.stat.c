//stat()获取文件inode信息
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("error args\n");
    }
    struct stat stat_ret;
    int ret = stat(argv[1], &stat_ret);
    if(-1 == ret)
    {
        perror("get file state error");
        exit(-1);
    }
    printf("the sizeof file : %ld\n", stat_ret.st_size);
    printf("the mode of file : %d\n", stat_ret.st_mode);
    return 0;
}
