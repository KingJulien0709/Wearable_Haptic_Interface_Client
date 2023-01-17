#include "bno_imu.hpp"


Adafruit_BNO055 bno=Adafruit_BNO055(55,0x28, &Wire);
sensors_event_t event_orientation , event_acceleration;

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
    
    bno.getEvent(&event_orientation,Adafruit_BNO055::VECTOR_GYROSCOPE);
    bno.getEvent(&event_acceleration,Adafruit_BNO055::VECTOR_ACCELEROMETER);

    arr[0]=(int16_t) event_orientation.orientation.heading;
    arr[1]=(int16_t) event_orientation.orientation.pitch;
    arr[2]=(int16_t) event_orientation.orientation.roll;


     
    //Serial.println("heading: " + String() + " - pitch:"+String(event.orientation.pitch) + " - roll: "+ String(event.orientation.roll));

}

void bno_imu_get_sensor_data_struct_char(char* buf){
    bno.getEvent(&event_orientation,Adafruit_BNO055::VECTOR_EULER);
    bno.getEvent(&event_acceleration,Adafruit_BNO055::VECTOR_ACCELEROMETER);
    //const int capacity = JSON_OBJECT_SIZE(6);
    //StaticJsonDocument<capacity> doc;
    //doc["h"]=event_orientation.orientation.heading,4;
    //doc["r"]=event_orientation.orientation.roll,4;
    //doc["p"]=event_orientation.orientation.pitch,4;
    //doc["x"]=event_acceleration.acceleration.x,4;
    //doc["y"]=event_acceleration.acceleration.y,4;
    //doc["z"]=event_acceleration.acceleration.z,4;

    //doc["y"]=event.acceleration.y;
    //doc["z"]=event.acceleration.z;
    //Serial.println(event_orientation.orientation.heading);
    char arr[128];
    snprintf(arr, sizeof(arr),"{\"h\":%3.2f,\"r\":%3.2f,\"p\":%3.2f,\"x\":%3.2f,\"y\":%3.2f,\"z\":%3.2f}",
    event_orientation.orientation.heading,event_orientation.orientation.roll,event_orientation.orientation.pitch,
    event_acceleration.acceleration.x,event_acceleration.acceleration.y,event_acceleration.acceleration.z);
    //snprintf(arr, sizeof(arr),"{\"h\":%3.2f,\"r\":%3.2f,\"p\":%3.2f,\"x\":%3.2f,\"y\":%3.2f,\"z\":%3.2f,\"m1\":%3.2f,\"m2\":%3.2f,\"m3\":%3.2f}",
    //event_orientation.orientation.heading,event_orientation.orientation.roll,event_orientation.orientation.pitch,
    //event_acceleration.acceleration.x,event_acceleration.acceleration.y,event_acceleration.acceleration.z,
    //event_orientation.magnetic.x,event_orientation.magnetic.y,event_orientation.magnetic.z);

    log_debug(arr);

    //serializeJson(doc,arr);
    //Serial.println(arr);
    //struct imu_struct temp_struct;
    //temp_struct.h=event.orientation.heading;
    //temp_struct.r=event.orientation.roll;
    //temp_struct.p=event.orientation.pitch;
    //static char arr[sizeof(struct imu_struct)];//static ?
    //memcpy(arr,&temp_struct, sizeof(struct imu_struct));
    //Serial.println(String(arr));
    strcpy(buf,arr);//maybe removeable
}