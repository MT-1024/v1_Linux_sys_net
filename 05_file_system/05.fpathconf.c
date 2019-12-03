#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    long name_max;
    //fpathconf()可以获取文件名的最大长度
    name_max = fpathconf(STDOUT_FILENO, _PC_NAME_MAX);
    printf("file name max length : %ld\n", name_max); 
    return 0;
}
