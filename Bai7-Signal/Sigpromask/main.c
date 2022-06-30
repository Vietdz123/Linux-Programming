#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

void handel_signum1()
{
    printf("Hello ae wibu\n");
}

int main()
{
    sigset_t newset, oldset;
    signal(11, handel_signum1);
    signal(10, handel_signum1);
    signal(3, handel_signum1);
    sigemptyset(&newset);
    sigaddset(&newset, 11);
    sigaddset(&newset, 4);
    sigprocmask(SIG_SETMASK, &newset, &oldset);
    printf("pid of main is : %d\n", getpid());

    while (1)
    {
        printf("Hello ae\n");
        sleep(2);
    }
    
}