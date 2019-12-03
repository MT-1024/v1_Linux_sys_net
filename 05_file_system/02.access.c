#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    if(access("./hello", F_OK) == -1)
    {
        perror("access error");
        exit(-1);
    }
    printf("file exit\n");

    return 0;
}
