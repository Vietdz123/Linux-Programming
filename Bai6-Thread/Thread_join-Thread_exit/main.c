#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

pthread_t threadID1;
int ret = 5;

void *thread_handle1() {
    int i = -1;
    while(1) {
        i++;
        printf("I'm thread I i = %d\n", i);
        sleep(1);
        if (i == 3) {
            pthread_exit(NULL);
            //pthread_exit(&ret);
        }
    }
}

int main()
{
    int *ptr = &ret;
    int check_create_thread;
    check_create_thread  = pthread_create(&threadID1, NULL, (void *)thread_handle1, NULL);
    
    if (check_create_thread == 0) {
        printf("Successflly create thread\n");
    } else {
        printf("fail to create thread \n");
    }

    //pthread_join(threadID1, (void**)&ptr);
    printf("\n return value from first thread is [%d]\n", *ptr);
    
    while(1) {
        sleep(1);
    }
}