#include "socket.h"

// https://github.com/onestraw/epoll-example/blob/master/epoll.c

static inline _SOCKET_STATUS _epoll_ctl_add(int epfd, int fd, uint32_t events)
{
    struct epoll_event new_epoll_event;
    new_epoll_event.data.fd = fd;
    new_epoll_event.events = events;

    // EPOLL_CTL: https://man7.org/linux/man-pages/man2/epoll_ctl.2.html
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &new_epoll_event) == -1) {
        return _SOCKET_EPOLL_FAILED;
	}

    return _SOCKET_INITIALIZE_SUCCESS;
}

static inline _SOCKET_STATUS _setnonblocking(int sockfd)
{
	if (fcntl(sockfd, F_SETFD, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK) == -1) {
		return _SOCKET_NON_BLOCKING_FAILED;
	}
	return _SOCKET_INITIALIZE_SUCCESS;
}

static inline void _run_forever(struct _socket *my_socket)
{
    int request_number = 0;

    uint8_t read_buff[1024] = {0};

    uint8_t read_response[1024] = {0};

    int read_n = 1;

    int socklen = sizeof(my_socket->socker_client_addr);

    while (1) {
        request_number = epoll_wait(my_socket->epfd, my_socket->events, SOCKET_MAXIMUN_LISTEN, -1);
        for (int request_number_idx = 0; request_number_idx < request_number; request_number_idx++) {
            
            if (my_socket->events[request_number_idx].data.fd == my_socket->listenfd) {
                
                // Getting a new connection.
                printf("Getting a new connection.\n");
                my_socket->connsock = accept(my_socket->listenfd, \
                                        (struct sockaddr*)&(my_socket->socker_client_addr), \
                                        &socklen);

                if (my_socket->connsock == -1) {
                    printf("_SOCKET_ACCEPT_FAILED\n");
                }
                
                if (_setnonblocking(my_socket->connsock) == _SOCKET_NON_BLOCKING_FAILED) {
                    printf("_SOCKET_NON_BLOCKING_FAILED\n");
                }

                if (_epoll_ctl_add(my_socket->epfd, my_socket->connsock, \
                            EPOLLIN | EPOLLET | EPOLLRDHUP | EPOLLHUP) == _SOCKET_EPOLL_FAILED) {
                                printf("_SOCKET_EPOLL_FAILED\n");
                            }

            } else if (my_socket->events[request_number_idx].events & EPOLLIN) {
                memset(read_buff, 0, sizeof(read_buff));

                // Data reading from socket.
                do {
                    read_n = read(my_socket->events[request_number_idx].data.fd, read_buff, 1024);
                } while(read_n > 0);

                http_response_gen("200 OK", "{\"Name\": 1}", "application/json", read_response);

                printf("%d %s\n", strlen(read_response), read_response);

                write(my_socket->events[request_number_idx].data.fd, \
                                read_response, strlen(read_response));

                //printf("%d\n", read_n);

                //printf("%s\n", read_buff);

                //close(my_socket->events[request_number_idx].data.fd);
            }
            
            if (my_socket->events[request_number_idx].events & (EPOLLRDHUP | EPOLLHUP)) {
                // Disconnect event.
                printf("lose a connection.\n");
                epoll_ctl(my_socket->epfd, EPOLL_CTL_DEL, my_socket->events[request_number_idx].data.fd, NULL);
				close(my_socket->events[request_number_idx].data.fd);
            }
        }
    }
}

static inline _SOCKET_STATUS _init(struct _socket *my_socket)
{
    // Create a new socket.
    if ((my_socket->listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        return _SOCKET_CREATE_FAILED;
    }

    memset(&(my_socket->socker_server_addr), 0, sizeof(struct sockaddr_un));
    my_socket->socker_server_addr.sun_family = AF_UNIX; 

    // Get size of SOCKER_PATH
    strcpy(my_socket->socker_server_addr.sun_path, SOCKET_PATH);
    my_socket->size = offsetof(struct sockaddr_un, sun_path) + \
                        strlen(my_socket->socker_server_addr.sun_path);

    // Remove socket file
    unlink(SOCKET_PATH);

    // Binding
    if (bind(my_socket->listenfd, (struct sockaddr *)&(my_socket->socker_server_addr), my_socket->size) < 0) {  
        return _SOCKET_BINDING_FAILED;
    }

    // Config non-blocking
    if (_setnonblocking(my_socket->listenfd) == _SOCKET_NON_BLOCKING_FAILED) {
        return _SOCKET_NON_BLOCKING_FAILED;
    }

    // Listening
    if (listen(my_socket->listenfd, SOCKET_MAXIMUN_LISTEN) < 0) {  
        return _SOCKET_LISTENING_FAILED;
    }

    // Create epoll
    my_socket->epfd = epoll_create(1);
	if (_epoll_ctl_add(my_socket->epfd, my_socket->listenfd, EPOLLIN | EPOLLOUT | EPOLLET) == _SOCKET_EPOLL_FAILED) {
        return _SOCKET_EPOLL_FAILED;
    }

    return _SOCKET_INITIALIZE_SUCCESS;
}

void socket_run_forever(struct _socket *my_socket) 
{
    _run_forever(my_socket);
}

_SOCKET_STATUS socket_init(struct _socket *my_socket)
{
    _init(my_socket);
}