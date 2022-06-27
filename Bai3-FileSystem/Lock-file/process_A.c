#include <stdio.h>
#include <sys/stat.h> 
#include <sys/file.h> 
#include <unistd.h> 
#include <fcntl.h> 

int main(void) 
{ 
    int fd; 
    char text[40] = {0}; 
    struct flock fl; 
 
    sprintf(text, "vlon luon dau cat moi hihhi\n"); 

    if ((fd=open("./hello.txt", O_RDWR | O_CREAT, 0666)) == -1) { 
        printf("can not create file \n"); 
        return 0; 
    } else { 
        printf("create file test.txt\n"); 
    } 

    if (write(fd, text , sizeof(text) - 1) == -1) { 
        printf("can not write file \n"); 
        return 0; 
    } else { 
        printf("write file \n"); 
    } 

    fl.l_start = 4;         /* Offset where the lock begins */
    fl.l_len = 8;           /* Number of bytes to lock; 0 means "until EOF" */
    fl.l_type = F_WRLCK;    /* Lock type: F_RDLCK, F_WRLCK, F_UNLCK */
    fl.l_whence = SEEK_SET; /* How to interpret 'l_start': SEEK_SET, SEEK_CUR, SEEK_END */

    if (fcntl(fd, F_SETLK, &fl) == -1) { 
        printf("can not set write lock byte 1-5\n"); 
    } else { 
        printf("set write lock byte 1-5 \n"); 
    } 

    while (1) { 
        sleep(1); 
    } 

    close(fd); 
    return 0; 
}