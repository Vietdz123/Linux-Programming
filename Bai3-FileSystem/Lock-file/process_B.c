#include <stdio.h>
#include <sys/stat.h> 
#include <sys/file.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <string.h>

int main(void) 
{ 
    int fd; 

    char text[30] = {0}; 
    struct flock fl; 

    sprintf(text, "hell jqk"); 
 
    if ((fd=open("./hello.txt", O_RDWR)) == -1) { 
        printf("can not open file \n"); 
        return 0; 
    } else { 
        printf("open file test.txt \n"); 
    } 

    fl.l_start = 1;         /* Offset where the lock begins */
    fl.l_len = 5;           /* Number of bytes to lock; 0 means "until EOF" */
    fl.l_type = F_WRLCK;    /* Lock type: F_RDLCK, F_WRLCK, F_UNLCK */
    fl.l_whence = SEEK_SET; /* How to interpret 'l_start': SEEK_SET, SEEK_CUR, SEEK_END */

    if (fcntl(fd, F_SETLK, &fl) == -1) {
        printf("can not set write lock byte 0-5\n"); 
    } else
        printf("Vlon\n");

    fl.l_start = 0; 
    fl.l_len = 3; 
    fl.l_type = F_WRLCK; 
    fl.l_whence = SEEK_SET; 

    if (fcntl(fd, F_SETLK, &fl) == -1) { 
        printf("can not set write lock byte 6-11\n"); 
    } else { 
        printf("set write lock byte 6-11\n"); 
        lseek(fd, 5, SEEK_SET);

        if (write(fd, text, strlen(text)) == -1) { 
            printf("can not write file \n"); 
            return 0; 
        } else {
            printf("write file \n");
        } 
    } 

    close(fd); 
    return 0; 
} 