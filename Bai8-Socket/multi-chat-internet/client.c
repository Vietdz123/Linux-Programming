#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <pthread.h>
#include <signal.h>

#define TYPE_MESSAGE            "message-data"
#define TYPE_DESTROY_CONNECT    "destroy-connect"

pthread_t threadID;
int sockfd = 0, n = 0;
char userName[30] = {0};

void signal_handler() {
    char buffer_send_disconnect[100] = {0};
    uint16_t byte_send = 0;
    
    byte_send = strlen(TYPE_DESTROY_CONNECT);
    sprintf(buffer_send_disconnect, "%s", TYPE_DESTROY_CONNECT);
    write(sockfd, &byte_send, sizeof(byte_send));
    write(sockfd, TYPE_DESTROY_CONNECT, sizeof(TYPE_DESTROY_CONNECT));
    exit(0);
}

void init_signal() {
    signal(2, signal_handler);
}

void send_message(uint16_t byte_number, const char *message) {
    write(sockfd, &byte_number, sizeof(uint16_t));
    write(sockfd, message, byte_number);
}

void clear_enter(char data_send[]) {
    data_send[strlen(data_send) - 1] = 0;
}

void login() {
    memset(userName, 0, sizeof(userName));
    printf("Enter UserName: ");
    fgets(userName, 30, stdin);
    clear_enter(userName);
    send_message(strlen(userName), userName);
}

void *thread_handle_receive_data(void *fd_socket) {
    char type_data[30] = {0};
    char message[1024] = {0};
    char data_receive[1000] = {0};
    int *fd_accept = (int *)fd_socket;
    while (1) {
        memset(data_receive, 0, 1000);
        read(*fd_accept, data_receive, 1000);
        sscanf(data_receive, "%[^,], %[^,]", type_data, message);
        if (strcmp(type_data, TYPE_MESSAGE) == 0) {
            printf("\nvlon %s\n", message);
        }
        if (strcmp(type_data, TYPE_DESTROY_CONNECT) == 0) {
            printf("\nData receive : %s\n", message);
            close(sockfd);
            exit(0);
        }
    }
}

int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr; 
    char buffer_send[1024] = {0};
    char message[1500] = {0};
    uint16_t byte_write = 0;

    if (argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    init_signal();
    login();
    pthread_create(&threadID, NULL, thread_handle_receive_data, &sockfd);
    
    while (1)
    {
        printf("Enter message to server: ");
        fgets(buffer_send, 100, stdin);           
        clear_enter(buffer_send);

        sprintf(message, "%s, %s", TYPE_MESSAGE, buffer_send);
        byte_write = strlen(message) + strlen(TYPE_MESSAGE) + 2;
        
        write(sockfd, &byte_write, sizeof(uint16_t));
        write(sockfd, message, byte_write);
    }
    

    return 0;
}