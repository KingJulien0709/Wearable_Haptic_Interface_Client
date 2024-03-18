#include "bno_imu.hpp"


Adafruit_BNO055 bno=Adafruit_BNO055(55,0x28, &Wire);
sensors_event_t event_orientation , event_acceleration, event_gyro, event_linear_acceleration;

Adafruit_BNO08x  bno08x(-1);
sh2_SensorValue_t sensorValue;

float linear_acceleration_x=0;
float linear_acceleration_y=0;
float linear_acceleration_z=0;
float roll=0;
float pitch=0;
float heading=0;
float quaternion_w=0;
float quaternion_x=0;
float quaternion_y=0;
float quaternion_z=0;

  
void bno_imu_init_bno055(){
    i2c_multiplexer_change_channel(BNO_IC2_CHANNEL);
    if(!bno.begin(OPERATION_MODE_NDOF)){
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.println("no BNO055 detected ... Check your wiring or I2C ADDR!");
        return;
    }
    bno.setMode(OPERATION_MODE_NDOF);
    delay(100);
    
    
    //bno_imu_init();
}


void bno_imu_get_sensor_data_struct_char_bno055(char* buf){
    Serial.println("read bno_imu_get_sensor_data_struct_char");
    i2c_multiplexer_change_channel(BNO_IC2_CHANNEL);
    if(!bno.begin(OPERATION_MODE_NDOF)){
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("no BNO055 detected.");
        buf[0]='\0';
        return; //return and set the given array to empty string
    }

    
    /*check_bno055_calibration();

    Serial.print("bno mode: ");
    Serial.println(bno.getMode());*/



    
    bno.getEvent(&event_acceleration,Adafruit_BNO055::VECTOR_ACCELEROMETER); //get the acceleration from the imu

    //bno.getEvent(&event_orientation,Adafruit_BNO055::VECTOR_GYROSCOPE);
    bno.getEvent(&event_orientation,Adafruit_BNO055::VECTOR_EULER);
    bno.getEvent(&event_gyro,Adafruit_BNO055::VECTOR_GYROSCOPE);
    bno.getEvent(&event_linear_acceleration,Adafruit_BNO055::VECTOR_LINEARACCEL);

    /*Serial.print("acceleration x: ");
    Serial.println(event_acceleration.acceleration.x);
    Serial.print("acceleration y: ");
    Serial.println(event_acceleration.acceleration.y);
    Serial.print("acceleration z: ");
    Serial.println(event_acceleration.acceleration.z);

    Serial.print("gyro x: ");
    Serial.println(event_gyro.gyro.x);
    Serial.print("gyro y: ");
    Serial.println(event_gyro.gyro.y);
    Serial.print("gyro z: ");
    Serial.println(event_gyro.gyro.z);

    Serial.print("linear acceleration x: ");
    Serial.println(event_linear_acceleration.acceleration.x);
    Serial.print("linear acceleration y: ");
    Serial.println(event_linear_acceleration.acceleration.y);
    Serial.print("linear acceleration z: ");
    Serial.println(event_linear_acceleration.acceleration.z);*/

    
    //double wq=quat.w();
    //double xq=quat.x();
    //double yq=quat.y();
    //double zq=quat.z();
    imu::Quaternion quat = bno.getQuat(); //get the quaternion from the imu
    double wq=quat.w();
    double xq=quat.x();
    double yq=quat.y();
    double zq=quat.z();
    /*Serial.print("wq: ");
    Serial.println(wq,4);
    Serial.print("xq: ");
    Serial.println(xq,4);
    Serial.print("yq: ");
    Serial.println(yq,4);
    Serial.print("zq: ");
    Serial.println(zq,4);*/
    float force = force_sensor_read(); //get the force sensor value

    /*Serial.print("euler roll: ");
    Serial.println(event_orientation.orientation.roll/6.24 *360);
    Serial.print("euler pitch: ");
    Serial.println(event_orientation.orientation.pitch/6.24 *360);
    Serial.print("euler heading: ");
    Serial.println(event_orientation.orientation.heading/6.24 *360);*/

    char arr[256];
    snprintf(arr, sizeof(arr),"{\"w\":%1.5f,\"xq\":%1.5f,\"yq\":%1.5f,\"zq\":%1.5f,\"x\":%3.2f,\"y\":%3.2f,\"z\":%3.2f,\"h\":%3.2f,\"r\":%3.2f,\"p\":%3.2f,\"f\":%1.4f}",
    wq,xq,yq,zq,
    event_acceleration.acceleration.x,event_acceleration.acceleration.y,event_acceleration.acceleration.z,
    event_orientation.orientation.heading,event_orientation.orientation.roll,event_orientation.orientation.pitch,
    force); //format the data as json string, which can be send to the master

    //snprintf(arr, sizeof(arr),"{\"h\":%3.2f,\"r\":%3.2f,\"p\":%3.2f,\"x\":%3.2f,\"y\":%3.2f,\"z\":%3.2f}",event_orientation.orientation.heading,event_orientation.orientation.roll,event_orientation.orientation.pitch,event_acceleration.acceleration.x,event_acceleration.acceleration.y,event_acceleration.acceleration.z);

    log_debug(arr);
    strcpy(buf,arr);
}

void check_bno055_calibration(){
    i2c_multiplexer_change_channel(BNO_IC2_CHANNEL);
    uint8_t calib_stat,calib_sys,calib_gyro,calib_accel;
    bno.getCalibration(&calib_stat,&calib_sys,&calib_gyro,&calib_accel);
    Serial.print("calib_stat: ");
    Serial.println(calib_stat);
    Serial.print("calib_sys: ");
    Serial.println(calib_sys);
    Serial.print("calib_gyro: ");
    Serial.println(calib_gyro);
    Serial.print("calib_accel: ");
    Serial.println(calib_accel);
    //best case is 3, worst case is 0
}

void setReports(void) {
  Serial.println("Setting desired reports");
  if (!bno08x.enableReport(SH2_ACCELEROMETER)) {
    Serial.println("Could not enable accelerometer");
  }
  if (!bno08x.enableReport(SH2_GYROSCOPE_CALIBRATED)) {
    Serial.println("Could not enable gyroscope");
  }
  /*if (!bno08x.enableReport(SH2_MAGNETIC_FIELD_CALIBRATED)) {
    Serial.println("Could not enable magnetic field calibrated");
  }*/
  /*if (!bno08x.enableReport(SH2_LINEAR_ACCELERATION)) {
    Serial.println("Could not enable linear acceleration");
  }*/
  /*if (!bno08x.enableReport(SH2_GRAVITY)) {
    Serial.println("Could not enable gravity vector");
  }*/
  /*if (!bno08x.enableReport(SH2_ROTATION_VECTOR)) {
    Serial.println("Could not enable rotation vector");
  }*/
  /*if (!bno08x.enableReport(SH2_GEOMAGNETIC_ROTATION_VECTOR)) {
    Serial.println("Could not enable geomagnetic rotation vector");
  }*/
  if (!bno08x.enableReport(SH2_GAME_ROTATION_VECTOR, 5000U /* 5ms */)) {
    Serial.println("Could not enable game rotation vector");
  }
  /*if (!bno08x.enableReport(SH2_RAW_ACCELEROMETER)) {
    Serial.println("Could not enable raw accelerometer");
  }
  if (!bno08x.enableReport(SH2_RAW_GYROSCOPE)) {
    Serial.println("Could not enable raw gyroscope");
  }
  if (!bno08x.enableReport(SH2_RAW_MAGNETOMETER)) {
    Serial.println("Could not enable raw magnetometer");
  }*/
}

void bno_imu_init_bno085(){
    i2c_multiplexer_change_channel(BNO_IC2_CHANNEL);
    if(!bno08x.begin_I2C()){
        /* There was a problem detecting the BNO085 ... check your connections */
        Serial.println("no BNO085 detected ... Check your wiring or I2C ADDR!");
        return;
    }
    setReports();
}
void bno_imu_get_sensor_data_struct_char_bno085(char* buf){
    i2c_multiplexer_change_channel(BNO_IC2_CHANNEL);
    

    float force = force_sensor_read(); //get the force sensor value

    while (bno08x.getSensorEvent(&sensorValue)) {
        //Serial.print("got sensor event: ");
        //Serial.println(sensorValue.sensorId);
        switch (sensorValue.sensorId) {
          case SH2_ACCELEROMETER:
              linear_acceleration_x = sensorValue.un.accelerometer.x;
              linear_acceleration_y = sensorValue.un.accelerometer.y;
              linear_acceleration_z = sensorValue.un.accelerometer.z;
              break;
          case SH2_GYROSCOPE_CALIBRATED:
              roll = sensorValue.un.gyroscope.x;
              pitch = sensorValue.un.gyroscope.y;
              heading = sensorValue.un.gyroscope.z;
              break;
          case SH2_ROTATION_VECTOR:
              quaternion_w = sensorValue.un.rotationVector.real;
              quaternion_x = sensorValue.un.rotationVector.i;
              quaternion_y = sensorValue.un.rotationVector.j;
              quaternion_z = sensorValue.un.rotationVector.k;
              break;
          case SH2_GAME_ROTATION_VECTOR:
              quaternion_w = sensorValue.un.gameRotationVector.real;
              quaternion_x = sensorValue.un.gameRotationVector.i;
              quaternion_y = sensorValue.un.gameRotationVector.j;
              quaternion_z = sensorValue.un.gameRotationVector.k;
              break;
          default:
              // Handle unexpected sensor data
              break;
      }
    }

    char arr[256];
    snprintf(arr, sizeof(arr),"{\"w\":%1.5f,\"xq\":%1.5f,\"yq\":%1.5f,\"zq\":%1.5f,\"x\":%3.3f,\"y\":%3.3f,\"z\":%3.3f,\"h\":%1.4f,\"r\":%1.4f,\"p\":%1.4f,\"f\":%1.4f}",
    quaternion_w,quaternion_x,quaternion_y,quaternion_z,
    linear_acceleration_x,linear_acceleration_y,linear_acceleration_z,
    heading,roll,pitch,
    force); //format the data as json string, which can be send to the master
    
    log_debug(arr);
    strcpy(buf,arr);
}
