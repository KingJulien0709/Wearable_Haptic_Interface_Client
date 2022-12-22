#include "bno_imu.hpp"


Adafruit_BNO055 bno=Adafruit_BNO055(550,0x28, &Wire);
sensors_event_t event;
  
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