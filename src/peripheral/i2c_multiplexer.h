#pragma once
#ifndef _I2C_MULTIPLEXER_H
#define _I2C_MULTIPLEXER_H

#include "service/i2c.h"


void i2c_mult_init();
void i2c_change_channel(uint8_t channel);


#endif