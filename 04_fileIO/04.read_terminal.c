//将输入终端的数据写入到输出终端
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    char buf[8192];
    int read_len = read(STDIN_FILENO, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, read_len);
    return 0;
}
