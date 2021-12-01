#include "transfer_socket.h"


void init_transfer_socket(struct _transfer_socket* transfer_socket)
{
    // Create socket
    transfer_socket->sockfd = socket(AF_INET, SOCK_STREAM , 0);
    memset(transfer_socket->inputBuffer, 0, sizeof(transfer_socket->inputBuffer));
    transfer_socket->addrlen = sizeof(transfer_socket->clientInfo);
    bzero(&transfer_socket->serverInfo, sizeof(transfer_socket->serverInfo));

    // IPV4
    transfer_socket->serverInfo.sin_family = PF_INET;

    transfer_socket->serverInfo.sin_addr.s_addr = INADDR_ANY;

    // Port
    transfer_socket->serverInfo.sin_port = htons(transfer_socket->port);

    // Bind
    bind(transfer_socket->sockfd,(struct sockaddr *)&transfer_socket->serverInfo,sizeof(transfer_socket->serverInfo));

    // listen
    listen(transfer_socket->sockfd, MAXIMUN_CLIENT);

    // Create thread for command processing
    pthread_create(&transfer_socket->t, NULL, run_transfer_socket, transfer_socket);

}

void *run_transfer_socket(void *arg)
{
    struct _transfer_socket *ptr_transfer_socket = (struct _transfer_socket*)arg;
    int forClientSockfd = 0;

    while(1) {
        forClientSockfd = accept(ptr_transfer_socket->sockfd,(struct sockaddr*) &ptr_transfer_socket->clientInfo, &ptr_transfer_socket->addrlen);

        // send(forClientSockfd, message, sizeof(message),0);

        recv(forClientSockfd, ptr_transfer_socket->inputBuffer, sizeof(ptr_transfer_socket->inputBuffer), 0);
        
        printf("Get:%s\n",ptr_transfer_socket->inputBuffer);
    }
}