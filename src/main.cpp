#include <Arduino.h>
#include "WiFi.h"
#include "lwip/sockets.h"
#include "lwip/err.h"
#include "peripheral/i2c_multiplexer.h"



#define UPDATEINTERVAL_MS 20


#define HOST_IP_ADDR "192.168.178.44"
#define PORT 100

struct sockaddr_in dest_addr;


void setup() {

  Serial.begin(115200);
 
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin("FRITZ!Box Mesh-KK","00965943372456668602");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());

  
  dest_addr.sin_addr.s_addr = inet_addr(HOST_IP_ADDR);
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(PORT);

}

void loop() {

  char rx_buffer[128];
 
  int s = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);//
  if(s<0){
    Serial.println("Couldn't create Socket");
    return;
  }
  int err = connect(s,(struct sockaddr *)&dest_addr,sizeof(struct sockaddr_in));
  
  if(err !=0){
    Serial.println("Error");
    return;
  }

  while (1)
  {
    int len = recv(s,rx_buffer,sizeof(rx_buffer)-1,0);

    if(len<0){
      Serial.println("Too small");
      return;
    }else{
      rx_buffer[len] = 0; //NULL terminated
      Serial.println(rx_buffer);
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }

  if(s!=-1){
    shutdown(s,0);
    close(s);
  }
 
  

  // put your main code here, to run repeatedly:
}