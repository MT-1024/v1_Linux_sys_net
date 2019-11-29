//file open() write()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[])
{
    char buf[1024] = "helloWorld";
    printf("buff strlen = %ld\n", strlen(buf));
    printf("buff sizeof = %ld\n", sizeof(buf));
    int fd = open(argv[1] , O_CREAT | O_RDWR, 0644);
    printf("fd = %d\n", fd);

    int ret = write(fd, buf, strlen(buf));
    printf("ret = %d\n", ret);
    close(fd);

    return 0;
}
