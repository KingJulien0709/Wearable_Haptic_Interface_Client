#pragma once
#ifndef _BNO_IMU_H
#define _BNO_IMU_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_BusIO_Register.h>
#include <ArduinoJson.h>

void bno_imu_init();
void bno_imu_get_sensor_data(int16_t *arr);
void bno_imu_get_sensor_data_struct_char(char* buf);

#endif