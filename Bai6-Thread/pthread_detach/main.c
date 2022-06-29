#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

pthread_t threadID1;

void *thread_handle1() {
    pthread_detach(pthread_self());
}

int main()
{
    int check_create_thread;
    int counter = 0;
    check_create_thread  = pthread_create(&threadID1, NULL, (void *)thread_handle1, NULL);
    if (check_create_thread == 0) {
        printf("Successflly create thread\n");
    } else {
        printf("fail to create thread \n");
    }

    while(1) {
        check_create_thread  = pthread_create(&threadID1, NULL, (void *)thread_handle1, NULL);
        if (check_create_thread == 0) {
            //printf("Successflly create thread\n");
        } else {
            printf("fail to create thread \n");
            break;
        }
        counter++;
        if (counter % 1000 == 0) {
            printf("Thread created: %d\n", counter);
        }
    }
}