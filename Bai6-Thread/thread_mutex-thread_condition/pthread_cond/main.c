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
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int g_global = 5;

void thread_handle1() {
    pthread_detach(thread_ID1);
    char x;
    printf("hello ae wibu I'm thread handle1\n");
    pthread_mutex_lock(&lock);
    while(1) {
        printf("Enter anything to transmiss signal *cond* to main: ");
        scanf("%c", &x);
        getchar();
        pthread_cond_signal(&cond);
        //sleep(1);
        pthread_mutex_unlock(&lock);
        sleep(1);
        pthread_mutex_lock(&lock);
    }
}

int main()
{
    pthread_create(&thread_ID3, NULL, (void *)thread_handle1, NULL);

    pthread_mutex_lock(&lock);
    //sleep(2);
    while (1) {
        pthread_cond_wait(&cond, &lock);
        printf("Hello ae wibu I'm thread main\n");
    }

    return 0;
}