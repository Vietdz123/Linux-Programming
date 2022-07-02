#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <pthread.h>
#include <signal.h>

int g_fdaccept[100] = {0};
int number_chat = 0;
pthread_t threadID;

#define TYPE_MESSAGE            "message-data"
#define TYPE_DESTROY_CONNECT    "destroy-connect"

void signal_handler() {
    char buffer_send[100] = {0};
    sprintf(buffer_send, "%s, %s", TYPE_DESTROY_CONNECT, "No meaning");
    
    for (int i = 0; i < number_chat; i++) {
        write(g_fdaccept[i], buffer_send, strlen(buffer_send));
        close(g_fdaccept[i]);
    }
    exit(0);
}

void init_signal() {
    signal(2, signal_handler);
}

void read_data(int fd_client, char *buffer_read) {
    uint16_t byte_read = 0;
    read(fd_client, &byte_read, sizeof(byte_read));
    read(fd_client, buffer_read, byte_read);
    printf("User name: %s\n", buffer_read);
}

void boardcast(char data_sended[], int fd_user) {
    for (int i = 0; i < number_chat; i++) {
        if (g_fdaccept[i] != fd_user) {
            write (g_fdaccept[i], data_sended, strlen(data_sended));
        }
    }
}

void *thread_handle_receive_data(void *fd_socket) {
    pthread_detach(pthread_self());
    int check_first_connect = 0;
    char data_receive[1024] = {0};
    int *fd_accept = (int *)fd_socket;
    uint16_t byte_read = 0;
    char type_data[30] = {0};
    char message[1024] = {0};
    char name_user[30] = {0};
    char buffer_send[2048] = {0};

    if(check_first_connect == 0) {
        read_data(*fd_accept, name_user);
    }

    while (1)
    {
        byte_read = 0;
        memset(data_receive, 0, sizeof(data_receive));
        memset(message, 0, sizeof(message));
        memset(buffer_send, 0, sizeof(buffer_send));

        read(*fd_accept, &byte_read, sizeof(uint16_t));
        byte_read = read(*fd_accept, data_receive, byte_read);
        //printf("Data receive: %s and byte read = %d\n", data_receive, byte_read);
        sscanf(data_receive, "%[^,], %[a-zA-Z ]", type_data, message);
        //printf("Type message = %s and message = %s\n", type_data, message);
        if (strcmp(type_data, TYPE_MESSAGE) == 0) {
            printf("Data receive: %s\n", data_receive);
            sprintf(buffer_send, "%s, %s: %s", type_data, name_user, message);
            boardcast(buffer_send, *fd_accept);
        } else if (strcmp(type_data, TYPE_DESTROY_CONNECT) == 0) {
            printf("exit thread\n");
            close(*fd_accept);
            pthread_exit(NULL);
        }
    }
}

int main(int argc, char *argv[])
{
    int listenfd = 0, fd_accept = 0;
    struct sockaddr_in serv_addr; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 
	
    int otp = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &otp, sizeof(otp));
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    init_signal();

    while (1)
    {
        int *fd_accept_client = malloc(sizeof(int));
        *fd_accept_client = accept(listenfd, (struct sockaddr*)NULL, NULL);
        g_fdaccept[number_chat] = *fd_accept_client;
        number_chat++;  
        pthread_create(&threadID, NULL, thread_handle_receive_data, fd_accept_client);
    }
    

}