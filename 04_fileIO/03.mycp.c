//简单实现linux cp命令
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SIZE 8192

int main(int argc, char * argv[])
{
    if(argc < 3)
    {
        printf("you should enter content format like this : ./a.out src dest\n");
        exit(1);
    }
    char buf[SIZE];
    int fd_src, fd_dest;

    fd_src = open(argv[1], O_RDONLY);
    if(-1 == fd_src)
    {
        printf("open fd_sr error!\n");
    }

    fd_dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(-1 == fd_src)
    {
        printf("open fd_sr error!\n");
    }

    //成功,返回读到的字节数
    //读到文件末尾返回0
    //读失败返回-1
    int read_content = read(fd_src, buf, sizeof(buf));
    if(-1 == read_content)
    {
        printf("read src file error!\n");
    }

    int write_content = write(fd_dest, buf, strlen(buf));
    if(-1 == write_content)
    {
        printf("write file error!\n");
    }

    close(fd_src);
    close(fd_dest);
    return 0;
}
