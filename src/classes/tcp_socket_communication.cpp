#include "tcp_socket_communication.h"


    
TCP_Socket_Communication::TCP_Socket_Communication(int port, const char* ip_address, bool read_write){
    port_=port;
    ip_address_=ip_address;
    read_write_=read_write;
    sock_struct_local_.sin_addr.s_addr=inet_addr(ip_address);
    sock_struct_local_.sin_port=htons(port);
    sock_struct_local_.sin_family = AF_INET;
}
void TCP_Socket_Communication::tcp_socket_init(){
    socket_num_ = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(socket_num_<0){
        return;
    }
    Serial.println("[tcp_socket_communication]: Socket with num:" + String(socket_num_));
}
int TCP_Socket_Communication::tcp_socket_connect(){
    
    int error = connect(socket_num_,(struct sockaddr*) &sock_struct_local_, sizeof(sock_struct_local_));
    if(error != 0){
        Serial.println("[tcp_socket_communication]: Error when connecting socket:" + String(error));
    }
    return error;
}
int TCP_Socket_Communication::tcp_socket_close(){
    return closesocket(socket_num_);
}
int TCP_Socket_Communication::tcp_socket_send_string(const char* data){
    int sent_bytes_amount = send(socket_num_,data,sizeof(data),0);
    Serial.println("[tcp_socket_communication]: Bytes sent:" + String(sent_bytes_amount));
    return sent_bytes_amount;
}

char* TCP_Socket_Communication::tcp_socket_receive_string(){
    static char data[TCP_SOCKET_READ_SIZE];
    int length = recv(socket_num_,data,sizeof(data)-1,0);
    if(length < 0){
       Serial.println("[tcp_socket_communication]: Not enougth bytes received:" + String(length));
       data[0]= 0; 
    }else{
        data[length] = 0;
        Serial.println("[tcp_socket_communication]: received data:" + String(data));
    }
    return data;
}

        
        

