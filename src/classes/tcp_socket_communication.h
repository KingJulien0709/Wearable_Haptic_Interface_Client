#ifndef _TCP_SOCKET_COMMUNICATION_H
#define _TCP_SOCKET_COMMUNICATION_H

#include "Arduino.h"
#include "stdint.h"
#include "lwip/sockets.h"

#define TCP_SOCKET_READ = 0
#define TCP_SOCKET_WRITE = 1

#define TCP_SOCKET_READ_SIZE 256

class TCP_Socket_Communication{
    private:
        int port_;
        const char* ip_address_;
        bool read_write_;
        int socket_num_;
        struct sockaddr_in sock_struct_local_; 
    public:
        TCP_Socket_Communication(int port, const char* ip_address, bool read_write);
        void tcp_socket_init();
        int tcp_socket_connect();
        int tcp_socket_close();
        int tcp_socket_send_string(const char* data);
        char* tcp_socket_receive_string();
};

#endif