/* 发送信号结束进程 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char * argv[])
{
    if(argc < 3)
    {
        printf("./mykill signal pid\n");
        exit(-1);
    }

    /* 将argv[2]转成pid_t类型，将argv[1]转成int */
    int ret = kill((pid_t)atoi(argv[2]), atoi(argv[1]));
    if(ret < 0)
    {
        perror("kill error");
        exit(-1);
    }

    return 0;
}
