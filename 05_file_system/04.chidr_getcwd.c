//改变目录、获取当前目录
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 4096

int main()
{
    char buf[SIZE];

    chdir("/");
    printf("pwd:%s\n",getcwd(buf, SIZE));
    return 0;
}
