#pragma once
#ifndef _DRV_H
#define _DRV_H

#include "stdint.h"
#include "i2c_multiplexer.h"
#include "Wire.h"

#define DRV_DEVICE_COUNTER 6
#define DRV_ENABLE_PIN 13 // not yet decided

void drv_init();
void drv_single_init(uint8_t channel);
void drv_power_state_machine(uint8_t var);
void drv_run(uint8_t chanel, uint8_t level);

#endif