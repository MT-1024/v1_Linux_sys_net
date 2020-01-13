/* 文件锁实现互斥访问文件 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Please enter format like : ./a.out [filename]\n");
        exit(1);
    }

    int fd;
    if((fd = open(argv[1], O_RDWR)) < 0)
    {
        perror("open file error\n"); 
        exit(1);
    }

    /* struct flock */ 
    /* { */
    /*     short l_type;    /1* Type of lock: F_RDLCK, */
    /*                         F_WRLCK, F_UNLCK *1/ */
    /*     short l_whence;  /1* How to interpret l_start: */
    /*                         SEEK_SET, SEEK_CUR, SEEK_END *1/ */
    /*     off_t l_start;   /1* Starting offset for lock *1/ */
    /*     off_t l_len;     /1* Number of bytes to lock *1/ */
    /*     pid_t l_pid;     /1* PID of process blocking our lock */
    /*                         (set by F_GETLK and F_OFD_GETLK) *1/ */
    /* }; */

    struct flock f_lock;
    f_lock.l_type = F_WRLCK;
    f_lock.l_whence = SEEK_SET;
    f_lock.l_start = 0;
    f_lock.l_len = 0; //为0表示整个文件加锁

    /* 对文件加锁 */
    fcntl(fd, F_SETLKW, &f_lock);
    printf("have locked flock\n");
    
    sleep(10);
    
    /* 对文件解锁 */
    f_lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &f_lock);
    printf("unlock file\n");
    
    close(fd);
    return 0;
}
