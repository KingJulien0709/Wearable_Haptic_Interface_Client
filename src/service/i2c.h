#pragma once
#ifndef _I2C_H
#define _I2C_H

#include "Wire.h"

bool i2c_init_var;

void i2c_init(uint8_t sd_pin,uint8_t sc_pin);
void i2c_write_without_register(uint8_t address, uint8_t data_byte);
void i2c_write_with_register(uint8_t address, uint8_t register_address,uint8_t data_byte);


#endif