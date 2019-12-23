#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        /* in child */
        printf("child process PID is %d\n", getpid());
        printf("child group ID id %d\n", getpgid(0));
        printf("child session ID is %d\n", getsid(0));
        sleep(10);
        
        printf("**************************************\n");
        setsid();
        printf("have changed child session ID\n");
        printf("**************************************\n");

        printf("child process PID is %d\n", getpid());
        printf("child group ID id %d\n", getpgid(0));
        printf("child session ID is %d\n", getsid(0));
        sleep(20);
        exit(0);

    }
    return 0;
}
