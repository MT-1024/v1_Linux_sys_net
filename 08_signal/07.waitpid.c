#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    for(int i = 0; i < 10; i++)
    {
        if((pid = fork()) == 0)
        {
            break;
        }
        else if(pid < 0)
        {
            perror("fork error");
            exit(1);
        }
    }


    if(pid == 0)
    {
        int n = 8;
        while(n--)
        {
            printf("child ID : %d\n", getpid());
            sleep(1);
        }
    }
    else if(pid > 0)
    {
        while(1)
        {
            printf("parent ID : %d\n", getpid());
            sleep(1);
        }
    }
}
