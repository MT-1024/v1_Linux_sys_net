#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    int fd = open(argv[1] , O_CREAT, 0644);
    printf("fd = %d\n", fd);
    close(fd);
    return 0;
}
