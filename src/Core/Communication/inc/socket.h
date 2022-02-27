#ifndef __SOCKET_H__
#define __SOCKET_H__
#include <stdlib.h>  
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>  
#include <sys/socket.h>  
#include <sys/epoll.h>
#include <sys/un.h>
#include <fcntl.h>
#include <errno.h>  
#include <string.h>  
#include <unistd.h>  
#include <ctype.h>
#include "http.h"

#define SOCKET_PATH "../server.socket"
#define SOCKET_MAXIMUN_LISTEN   50

typedef enum {
    _SOCKET_INITIALIZE_SUCCESS,
    _SOCKET_NON_BLOCKING_FAILED,
    _SOCKET_EPOLL_FAILED,
    _SOCKET_CREATE_FAILED,
    _SOCKET_BINDING_FAILED,
    _SOCKET_LISTENING_FAILED,
    _SOCKET_ACCEPT_FAILED,
} _SOCKET_STATUS;

struct _socket {
    struct sockaddr_un socker_server_addr; 
    struct sockaddr_un socker_client_addr;
    struct epoll_event events[SOCKET_MAXIMUN_LISTEN];
    int listenfd;
    int epfd;
    int size;
    int connsock;
};

_SOCKET_STATUS socket_init(struct _socket*);
void socket_run_forever(struct _socket*);

#endif