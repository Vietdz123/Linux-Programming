#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PATH_FIFO "./myfifo"

int main()
{
    int fd;
    char buff[1024];

    //mkfifo(PATH_FIFO, 0666);
    while(1){
        fd = open(PATH_FIFO, O_RDWR);
        read(fd, buff, sizeof(buff));
        printf("Message received from server : %s\n", buff);
        close(fd);
        
        fd = open(PATH_FIFO, O_RDWR);
        printf("send message to server : ");
        fgets(buff, 1024, stdin);
        write(fd, buff, sizeof(buff));
        sleep(1);
        close(fd);
    }
}
