#include <Arduino.h>
#include "WiFi.h"
#include "lwip/sockets.h"
#include "lwip/err.h"
#include "peripheral/i2c_multiplexer.hpp"
#include "service/communication.hpp"
#include "classes/tcp_socket_communication.hpp"
#include "peripheral/bno_imu.hpp"
#include <ArduinoJson.h>
#include "utils/log.hpp"
#include "peripheral/drv.hpp"


#define UPDATEINTERVAL_MS 20

#define WIFI_SSID "FRITZ!Box Mesh-KK"// "Debug Network"
#define WIFI_PASSWORT "00965943372456668602"//"1234567890"

#define HOST_IP_ADDR "192.168.178.44"
#define PORT 100

//#define PIN_SDA currently not needed, because default pin is used
//#define PIN_SCLK currently not needed, because default pin is used



TCP_Socket_Communication my_tcp_socket(PORT,HOST_IP_ADDR);

TaskHandle_t mainTask;//currently not used. maybe it will be implemented for dual core functionality

//void setupTasks(){
//  xTaskCreatePinnedToCore(
//                    mainTaskFunction,   /* Task function. */
//                    "mainTask",     /* name of task. */
//                    10000,       /* Stack size of task */
//                    NULL,        /* parameter of the task */
//                    4,           /* priority of the task */
//                    &mainTask,      /* Task handle to keep track of created task */
//                    1);          /* pin task to core 1 */                  
//  delay(500); 
//} 

//declare functions
void handle_position_data(); 
void handle_haptic_feedback();

void setup() {
  
  Serial.begin(115200);

  log_init(LOG_LEVEL_INFO); //set log levels for all modules to info
  
  //i2c_multiplexer_init();

  bno_imu_init();

  //drv_init();

  communication_connect_wifi(WIFI_SSID,WIFI_PASSWORT);

  my_tcp_socket.tcp_socket_init();
  while(my_tcp_socket.tcp_socket_connect()!=0){
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }

}

void loop() {

  handle_position_data();

  handle_haptic_feedback();
  
  vTaskDelay(250/portTICK_PERIOD_MS);
  
}
void mainTaskFunction( void * pvParameters ){

}

/**
 * @brief Function for dealing with the process for getting data from the imu to the master
 * TODO try to reduce time. now about 10 ms -> try to come down to <5
 */
void handle_position_data(){
  long a=millis();
  char p[TCP_SOCKET_SEND_SIZE];
  bno_imu_get_sensor_data_struct_char(p);
  log_debug(p);
  if(my_tcp_socket.tcp_socket_send_string(p,sizeof(p))==TCP_SOCKET_SEND_SIZE){
    log_info("successful sent and collected data in ms: "+ String(millis()-a));
  }else{
    //FIXME could handle error here
  }
  
}

/**
 * @brief Function for dealing with the process for getting data from ther master to the drv driver
 * 
 */
void handle_haptic_feedback(){
  long a=millis();
  char buff[TCP_SOCKET_READ_SIZE]; //including zero ending char
  strcpy(buff,my_tcp_socket.tcp_socket_receive_string_non_blocking());//non blocking mode -> no message skip round
  if(strlen(buff)<=1){
    log_trace("no new data");//can skip input msg for debugging possible
    return;
  }else{
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc,buff);// Empyt Input error when no msg received  ;  Invalid Input error when json String not complete
    if(error){
      log_error(error.f_str());
      return;
    }else{
      uint8_t drv_data_arr[5];
      for(uint8_t i=0;i<5;i++){
        drv_data_arr[i]=doc[String(i)];
        log_trace(String(drv_data_arr[i]));
      }
      log_info("successful received data in ms: "+ String(millis()-a));
    }
  }
}

