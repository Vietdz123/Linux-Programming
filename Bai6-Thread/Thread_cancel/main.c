#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

pthread_t threadID1, threadID2;

void *thread_handle1() {
    int i = -1;
    while(1) {
        i++;
        printf("I'm thread I i = %d\n", i);
        sleep(1);
        if (i == 3) {
            pthread_cancel(threadID2);
        }
    }
}

void *thread_handle2() {
    while(1) {
        printf("I'm thread II\n");
        sleep(1);
    }
}

int main()
{
    int check_create_thread1, check_create_thread2;
    check_create_thread1  = pthread_create(&threadID1, NULL, (void *)thread_handle1, NULL);
    check_create_thread2  = pthread_create(&threadID2, NULL, (void *)thread_handle2, NULL);

    if (check_create_thread1 == 0 && check_create_thread2 == 0) {
        printf("Successflly create thread\n");
    } else {
        printf("fail to create thread \n");
    }

    pthread_join(threadID2, NULL);
    pthread_cancel(threadID1);
    pthread_join(threadID1, NULL);

    while(1) {
        printf("Hello I'm thread main\n");
        sleep(1);
    }
}