#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

pthread_t thread_ID1, thread_ID2, thread_ID3;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int g_global = 5;


void thread_handle1() {
    pthread_mutex_lock(&lock);
    g_global = 6;
    printf("In thread_handle1 g_global = %d \n", g_global);
    g_global = 10;
    printf("In thread_handle1 g_global = %d \n", g_global);
    //pthread_mutex_unlock(&lock);
}

void thread_handle2() {
    //pthread_mutex_lock(&lock);
    g_global = 8;
    printf("In thread_handle2 g_global = %d \n", g_global);
}

void thread_handle3() {
    printf("In thread_handle3 g_global = %d \n", g_global);
}

int main()
{
    pthread_create(&thread_ID1,  NULL,(void *) thread_handle1, NULL);
    sleep(1);
    pthread_create(&thread_ID2, NULL, (void *) thread_handle2, NULL);
    pthread_create(&thread_ID3, NULL, (void *) thread_handle3, NULL);

    while (1);
}