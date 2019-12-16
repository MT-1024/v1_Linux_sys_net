/* 从named pipe中读数据 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void my_error(char * str, int exitno)
{
    perror(str);
    exit(exitno);
}

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Please enter format like this : ./a.out xx\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if(-1 == fd)
    {
       my_error("open error", 1); 
    }
    
    char buf[4096];
    /* 将从fd中读取的数据保存到buf中，read()返回从fd读取的数据的长度 */
    int read_length = read(fd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, read_length);
    close(fd);
    return 0;
}
