//检查文件是否存在、可读、可写
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    //检查文件是否存在
    if(access("./hello", F_OK) == -1)
    {
        perror("access error");
        exit(-1);
    }
    printf("file exit\n");

    return 0;
}
