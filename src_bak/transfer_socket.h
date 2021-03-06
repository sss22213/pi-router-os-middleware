#ifndef __TRANSFER_SOCKET_H__
#define __TRANSFER_SOCKET_H__
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define INIT_TRANSFER_SOCKET(TRANSFER_SOCKET_NAME, PORT) \
    struct _transfer_socket TRANSFER_SOCKET_NAME = {.port = (PORT)};\
    init_transfer_socket(&TRANSFER_SOCKET_NAME);

#define MAXIMUN_CLIENT  10

#define INPUT_BUFFER_LENGTH 256

struct _transfer_socket {
    struct sockaddr_in serveraddr;
    struct sockaddr_in serverInfo;
    struct sockaddr_in clientInfo;
    char inputBuffer[INPUT_BUFFER_LENGTH];
    int addrlen;
    int sockfd;
    int port;
    pthread_t t;
};

void *run_transfer_socket(void*);
void init_transfer_socket(struct _transfer_socket*);

#endif