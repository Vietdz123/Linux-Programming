#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

pthread_t threadID1;

void *thread_handle1() {
    for (int i = 0; i < 4; i++) {
        printf("I'm thread I\n");
        sleep(1);
    }
}

int main()
{
    int check_create_thread;
    check_create_thread  = pthread_create(&threadID1, NULL, (void *)thread_handle1, NULL);
    if (check_create_thread == 0) {
        printf("Successflly create thread\n");
    } else {
        printf("fail to create thread \n");
    }

    while(1) {
        sleep(1);
    }
}