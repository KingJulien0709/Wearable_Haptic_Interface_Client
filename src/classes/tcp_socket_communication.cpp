#include "tcp_socket_communication.h"

class TCP_Socket_Communication{
    private:
        int port_;
        const char* ip_address_;
        bool read_write_;
        int socket_num_;
        struct sockaddr_in sock_struct_local_; 
    public:
        TCP_Socket_Communication::TCP_Socket_Communication(int port, const char* ip_address, bool read_write){
            port_=port;
            ip_address_=ip_address;
            read_write_=read_write;
            sock_struct_local_.sin_addr.s_addr=inet_addr(ip_address);
            sock_struct_local_.sin_port=htons(port);
            sock_struct_local_.sin_family = AF_INET;
        }

        void tcp_socket_init(){
            socket_num_ = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
            if(socket_num_<0){
                return;
            }
            Serial.println("[tcp_socket_communication]: Socket with num:" + String(socket_num_));
        }

        int tcp_socket_connect(){
            int error = connect(socket_num_,(struct sockaddr*) &sock_struct_local_, sizeof(sock_struct_local_));
            if(error != 0){
                Serial.println("[tcp_socket_communication]: Error when connecting socket:" + String(error));
            }
            return error;
        }

        int tcp_socket_close(){
            return closesocket(socket_num_);
        }
        


};