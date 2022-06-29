#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int rv, status;
    int child = fork();
    if (child >= 0) {
        if (child == 0) {
            printf("Pid tien trinh con %d\n", getpid());

        while (1);
	    exit(1);
	    sleep(3);
        }
        else{
            rv = waitpid(child, &status, NULL);
            if (rv == -1) {
                printf("wait failed");
            }

            if (status == 1) {
                printf("status = 1\n");
            } else if (status == 0) {
                printf("status = 0\n");
            }

            printf("Tien trinh cha %d\n",getpid());
            if (WIFEXITED(status)) {
                printf("the child terminated normally\n");
            }
            if (WIFSIGNALED(status)) {
                printf("the child process was terminated by a signal.\n");
            }
        }
    }
    else{
        printf("failed");
    }
    
}