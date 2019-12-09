//当进程调用一种exec函数时，该进程的用户空间代码和数据完全被新程序替换，从新程序的启动例程开始执行。
//新程序执行完返回的是新程序的返回值;不会再继续执行原进程
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("hello\n");
    //替换
    execl("/bin/ls", "ls", "-l", NULL);
    printf("world\n");
    return 0;
}
