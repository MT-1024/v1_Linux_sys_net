//递归遍历目录，并且递归打印文件名
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Please enter correct format\n");
    }

    DIR * mydir = opendir(argv[1]);
    struct dirent * mydirent = readdir(mydir); 
    if(strcmp(".", mydirent->d_name) == 0 || strcmp("..", mydirent->d_name) == 0)
    {

    }
    

    closedir(mydir); 
    return 0;
}
