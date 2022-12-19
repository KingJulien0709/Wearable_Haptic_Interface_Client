#include "tcp_socket_communication.h"


    
TCP_Socket_Communication::TCP_Socket_Communication(int port, const char* ip_address, bool read_write){
    blocking_mode_=false;
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
    if(!blocking_mode_){
        tcp_socket_configure_block_mode(true);// send function has to be in blocking mode and wait until data is sent, because the data can be important for the master. 
    }
    int sent_bytes_amount = send(socket_num_,data,sizeof(data),0);
    Serial.println("[tcp_socket_communication]: Bytes sent:" + String(sent_bytes_amount));
    return sent_bytes_amount;
}

char* TCP_Socket_Communication::tcp_socket_receive_string_blocking(){
    if(!blocking_mode_){
        tcp_socket_configure_block_mode(true);
    }
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
/**
 * @brief Receive function with non_blocking mode and MSG_DONTWAIT 
 * If blocking mode is disabled and the MSG_DONTWAIT flag is set at the receive function, the function does not wait for the socket receive function to finish.
 * An error will be return by the socket function and an empty arr will be returned by this function
 * 
 * @return char* 
 */
char* TCP_Socket_Communication::tcp_socket_receive_string_non_blocking(){
    if(blocking_mode_){
        tcp_socket_configure_block_mode(false);
    }
    static char data[TCP_SOCKET_READ_SIZE];
    int length = recv(socket_num_,data,sizeof(data)-1,MSG_DONTWAIT);
    if(length < 0){
       //Serial.println("[tcp_socket_communication]: Not enougth bytes received:" + String(length)); No message, because errors will happen a lot. But should not effect the program.
       data[0]= 0; 
    }else{
        data[length] = 0;
        Serial.println("[tcp_socket_communication]: received data:" + String(data));
    }
    return data;
}


/**
 * @brief configure the socket to a blocking or non_blocking socket.
 * If blocking mode is enabled, the function waits for the socket operation(mostly receive function) to finish.
 * If blocking mode is disabled and the MSG_DONTWAIT flag is set at the receive function, the function does not wait for the socket receive function to finish.
 * 
 * 
 * @param block_mode BOOLEAN if the program should set to blocking mode.
 */
void TCP_Socket_Communication::tcp_socket_configure_block_mode(bool block_mode){
    if(blocking_mode_==block_mode){
        return;//no need for changing mode
    }else{
        if(!block_mode){
            fcntl(socket_num_,F_SETFL,O_NONBLOCK);//set to the non_blocking mode. Socket operation will not wait until finished, but can return an error if not finished properly.
        }else{
            fcntl(socket_num_,F_SETFL,0);//set to the blocking mode. Socket operation will wait until finished.
        }
        //general solution if other flags are set. In this class there is just the 0_NONBLOCK flag. So the simple implmentation is enougth.
        //int flags = fcntl(socket_num_,F_GETFL,0);
        //if(block_mode){
        //    fcntl(socket_num_,F_SETFL,flags | O_NONBLOCK);// c
        //}else{
        //    fcntl(socket_num_,F_SETFL,flags & ~O_NONBLOCK);
        //}
    }
    

}
        
        

