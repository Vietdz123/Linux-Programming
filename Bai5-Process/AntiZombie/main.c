#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

void func()
{
    printf("Hello i'm fun()\n");
    wait(NULL);
}

int main()
{
    pid_t child = fork();
    if(child >= 0){
        if(child == 0){
            printf("Hello I'm PID con %d\n", getpid());
        }
        else{
            signal(SIGCHLD, func);
            printf("I'm parent\n");
            while(1);
        }
    }
    else{
        printf("failed");
    }
}