#include <Arduino.h>
#include "WiFi.h"
#include "lwip/sockets.h"
#include "lwip/err.h"
#include "peripheral/i2c_multiplexer.hpp"
#include "service/communication.hpp"
#include  "classes/tcp_socket_communication.hpp"
#include "peripheral/bno_imu.hpp"


#define UPDATEINTERVAL_MS 20

#define WIFI_SSID "FRITZ!Box Mesh-KK"
#define WIFI_PASSWORT "00965943372456668602"

#define HOST_IP_ADDR "192.168.178.44"
#define PORT 100

#define PIN_SDA 
#define PIN_SCLK


typedef struct imu_struct{
  float r;
  float h;
  float p;
} imu_struct_t;

struct sockaddr_in dest_addr;
int16_t arr[9];

TCP_Socket_Communication my_tcp_socket(PORT,HOST_IP_ADDR,0); 


void setup() {
  
  Serial.begin(115200);
 
  delay(1000);
   Serial.println("start_1");

  bno_imu_init();
  
  


  communication_connect_wifi(WIFI_SSID,WIFI_PASSWORT);
//
  my_tcp_socket.tcp_socket_init();
  while(my_tcp_socket.tcp_socket_connect()!=0){
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
//

  //communication_create_socket_connection(PORT,HOST_IP_ADDR);
  //communication_create_socket_connection(PORT+100,HOST_IP_ADDR);
  //WiFi.mode(WIFI_STA);
  //WiFi.begin("FRITZ!Box Mesh-KK","00965943372456668602");
  //while (WiFi.status() != WL_CONNECTED) {
  //  delay(1000);
  //  Serial.println("Connecting to WiFi..");
  //}
 //
  //Serial.println("Connected to the WiFi network");
  //Serial.println(WiFi.localIP());
//
  //
  //dest_addr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
  //dest_addr.sin_family = AF_INET;
  //dest_addr.sin_port = htons(PORT);

}

void loop() {

  //const char* result = my_tcp_socket.tcp_socket_receive_string_non_blocking();
  //if(strlen(result)>0){
  //  Serial.println(result);
  //}
  
  

  //bno_imu_get_sensor_data(arr);
  //String sensor_data_str = "s:"+String(arr[0])+";"+String(arr[1])+";"+String(arr[2])+0x00;
//
  //uint8_t len=sizeof(sensor_data_str);
  //char char_arr [30];
  //snprintf(char_arr,30,"s:%8x;%8x;%8x",arr[0],arr[1],arr[2]);
  //Serial.println(char_arr);
  //
  //sensor_data_str.toCharArray(char_arr,len);
  //

  char p[128];
  bno_imu_get_sensor_data_struct_char(p);
  Serial.println(p);
  my_tcp_socket.tcp_socket_send_string(p,sizeof(p));
  vTaskDelay(250/portTICK_PERIOD_MS);
  //Serial.println("round");

  //char rx_buffer[128];
 //
  //int s = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);//
  //if(s<0){
  //  Serial.println("Couldn't create Socket");
  //  return;
  //}
  //int err = connect(s,(struct sockaddr *)&dest_addr,sizeof(struct sockaddr_in));
  //
  //if(err !=0){
  //  Serial.println("Error");
  //  return;
  //}
//
  //while (1)
  //{
  //  int len = recv(s,rx_buffer,sizeof(rx_buffer)-1,0);
//
  //  if(len<0){
  //    Serial.println("Too small");
  //    return;
  //  }else{
  //    rx_buffer[len] = 0; //NULL terminated
  //    Serial.println(rx_buffer);
  //  }
  //  vTaskDelay(2000 / portTICK_PERIOD_MS);
  //}
//
  //if(s!=-1){
  //  shutdown(s,0);
  //  close(s);
  //}
 //
  //

  // put your main code here, to run repeatedly:
}