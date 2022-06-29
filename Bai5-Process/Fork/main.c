#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("hello_wibu.txt", O_RDWR | O_CREAT, 0666);
    pid_t childB;
    int status;

    printf("Starting...\n");
    childB = fork();
    if (childB > 0) {     
        pid_t childC;
        printf("pid A = %d and childB = %d \n", getpid(), childB);
        
        childC = fork();
        if (childC > 0) {                                              // Process A
            waitpid(childC, NULL, NULL);
            char data[100] = {0};
            lseek(fd, 0,  SEEK_SET);
            read(fd, data, 100);
            printf("Read file after C: %s\n", data);
            lseek(fd, 0,  SEEK_END); 
            write(fd, "Hello ae wibu I'm A\n", strlen("Hello ae wibu I'm A\n"));  
            
        } else if (childC == 0) {                                        // Process C
            pid_t childE;
            printf("Pid C = %d\n", getpid());
            childE = fork();
            if (childE == 0) {                                           // Process E
                char data[100] = {0};
                printf("Pid E = %d\n", getpid());
                sleep(1);
                lseek(fd, 0,  SEEK_SET);
                read(fd, data, 100);
                printf("Read file after D: %s\n", data);
                lseek(fd, 0,  SEEK_END); 
                write(fd, "Hello ae wibu I'm E\n", strlen("Hello ae wibu I'm E\n"));
            
            } else if (childE > 0) {
                char data[100] = {0};
                printf("Pid C = %d\n", getpid());                          // Process C
                sleep(4);
                lseek(fd, 0,  SEEK_SET);
                read(fd, data, 100);
                printf("Read file after B: %s\n", data);
                lseek(fd, 0,  SEEK_END); 
                write(fd, "Hello ae wibu I'm C\n", strlen("Hello ae wibu I'm C\n"));           
            } else {
                printf("Not successfully creat E process\n");
            }
        
        } else {
            printf("Not successfully creat C process\n");
        }

    } else if (childB == 0) {                                            // Process B
        pid_t childD;
        printf("Pid B = %d \n", getpid());
        childD = fork();
            if (childD == 0) {                                           // Process D
                printf("Pid D = %d\n", getpid());
                write(fd, "Hello ae wibu I'm D\n", strlen("Hello ae wibu I'm D\n"));
            
            } else if (childD > 0) {                                    // Process B
                char data[100] = {0};
                printf("Pid B = %d\n", getpid()); 
                sleep(3);  
                lseek(fd, 0,  SEEK_SET);                       
                read(fd, data, 100);
                printf("Read file after E: %s\n", data);
                lseek(fd, 0,  SEEK_END); 
                write(fd, "Hello ae wibu I'm B\n", strlen("Hello ae wibu I'm B\n"));
            } else {
                printf("Not successfully creat D process\n");
            }

    }  else {
        printf("Not successfully creat B process\n");
    }
}