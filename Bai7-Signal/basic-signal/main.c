#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void handel_signum1()
{
    printf("Hello ae wibu\n");
}

int main()
{
    signal(10, handel_signum1);
    printf("pid of main is : %d\n", getpid());
    while (1)
    {
        printf("Hello ae\n");
        sleep(2);
    }
    
}