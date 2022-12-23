#include "bno_imu.hpp"


Adafruit_BNO055 bno=Adafruit_BNO055(550,0x28, &Wire);
sensors_event_t event;

struct imu_struct{
  float r;
  float h;
  float p;
};
  
void bno_imu_init(){
    
    if(!bno.begin()){
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }
    delay(1000);

}

void bno_imu_get_sensor_data(int16_t *arr){
    
    bno.getEvent(&event);
    arr[0]=(int16_t) event.orientation.heading;
    arr[1]=(int16_t) event.orientation.pitch;
    arr[2]=(int16_t) event.orientation.roll;
     
    //Serial.println("heading: " + String() + " - pitch:"+String(event.orientation.pitch) + " - roll: "+ String(event.orientation.roll));

}

void bno_imu_get_sensor_data_struct_char(char* buf){
    bno.getEvent(&event);
    const int capacity = JSON_OBJECT_SIZE(3);
    StaticJsonDocument<capacity> doc;
    doc["h"]=event.orientation.heading;
    doc["r"]=event.orientation.roll;
    doc["p"]=event.orientation.pitch;
    uint8_t len1 = measureJson(doc);
    char arr[64];
    serializeJson(doc,arr);
    //Serial.println(arr);
    //struct imu_struct temp_struct;
    //temp_struct.h=event.orientation.heading;
    //temp_struct.r=event.orientation.roll;
    //temp_struct.p=event.orientation.pitch;
    //static char arr[sizeof(struct imu_struct)];//static ?
    //memcpy(arr,&temp_struct, sizeof(struct imu_struct));
    //Serial.println(String(arr));
    strcpy(buf,arr);
}