#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char * argv[])
{
    if(-1 == access(argv[2], F_OK))
    {
        perror("file not exit");
        exit(-1);
    }

    if(argc < 3)
    {
        printf("format error\n");
    }

    int mode = atoi(argv[1]);
    //待完善二进制装八进制
    if(-1 == chmod(argv[2], mode))
    {
        perror("chmod fail");
    }

        
    return 0;
}
