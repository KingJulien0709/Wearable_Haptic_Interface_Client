#pragma once
#ifndef _BNO_IMU_HPP
#define _BNO_IMU_HPP

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_BusIO_Register.h>
#include <ArduinoJson.h>
#include "utils/log.hpp"
#include "i2c_multiplexer.hpp"
#include "force_sensor.hpp"
#include <Adafruit_BNO08x.h>


#define BNO_IC2_CHANNEL 5

void bno_imu_init_bno055();
void bno_imu_get_sensor_data_bno055(int16_t *arr);
void bno_imu_get_sensor_data_struct_char_bno055(char* buf);
void bno_log_acceleration_bno055(uint8_t value);
void check_bno055_calibration();
void bno_imu_init_bno085();
void bno_imu_get_sensor_data_struct_char_bno085(char *buf);

#endif