#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
    int fd = open("abc", O_RDWR);
    if(fd < 0)
    {
        perror("open error");
        /* printf("%s\n", strerror(errno)); */
    }
    printf("fd = %d\n", fd);
    return 0;
}
