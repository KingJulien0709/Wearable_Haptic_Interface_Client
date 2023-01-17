#pragma once
#ifndef _I2C_MULTIPLEXER_H
#define _I2C_MULTIPLEXER_H

#include "service/i2c.hpp"
#include "Wire.h"


void i2c_multiplexer_init();
void i2c_multiplexer_change_channel(uint8_t channel);
void i2c_multiplexer_reset(uint8_t resetPin);


#endif