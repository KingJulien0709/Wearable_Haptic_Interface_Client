#include "communication.h"

void communication_init_wifi(const char* wifi_ssid,const char* wifi_passwort){

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_passwort);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
 
    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());
}
/**
 * @brief 
 *  AF_INET - ip4
 *  SOCK_STREAM - TCP
 *  IPPROTO_IP - ip-address
 * 
 * @param port Port for the communication
 * @param master_ip_address ip4 address of the server-master
 * @return uint8_t 0 at succes, 1 at error
 */
uint8_t communication_create_socket_connection(uint16_t port, const char* master_ip_address){

    struct sockaddr_in sock_struct_local;

    sock_struct_local.sin_addr.s_addr = inet_addr(master_ip_address);
    sock_struct_local.sin_port = htons(port);
    sock_struct_local.sin_family = AF_INET;


    int socket_num = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
    if(socket_num<0){
        return 1;
    }

    //int err = connect()  connection of socket can be put in a seperate function.
}

