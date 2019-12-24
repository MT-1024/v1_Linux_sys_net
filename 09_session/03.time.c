#include <stdio.h>
#include <time.h>

int main()
{
    char buf[4096];
    time_t mytime;
    time(&mytime);

    char * p = ctime_r(&mytime, buf);
    printf("current time is : %s", p);

    return 0;
}
