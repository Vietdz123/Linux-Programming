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
    char buff[1024] = {0};
    int num_byteRead;

    mkfifo(PATH_FIFO, 0666);
    while(1){
        fd = open(PATH_FIFO, O_RDWR);
        printf("Send mesage to client : ");
        fgets(buff, 1024, stdin);
        write(fd, buff, strlen(buff) + 1);
        close(fd);
        
        sleep(1);
        fd = open(PATH_FIFO, O_RDWR);
        num_byteRead = read(fd, buff, sizeof(buff));
        printf("message received from client : %s\n", buff);
        close(fd);
    }
}
