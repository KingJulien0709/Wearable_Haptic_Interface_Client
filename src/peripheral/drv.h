#pragma once
#ifndef _DRV_H
#define _DRV_H

#include "stdint.h"
#include "i2c_multiplexer.h"
#include "service/i2c.h"
#include "Wire.h"

#define DRV_DEVICE_COUNTER 5
#define DRV_ENABLE_PIN 13  // not yet decided
#define DRV_STATE_ACTIVE 0
#define DRV_STATE_STANDBY 1
#define DRV_STATE_SHUTDOWN 2

#define DRV_STATE_TRANSITION_DEV_RESET 3
#define DRV_STATE_TRANSITION_DEV_TOGGLE_STANDBY 4


void drv_init();
void drv_single_init(uint8_t channel);
void drv_power_state_machine(uint8_t var);
void drv_run(uint8_t chanel, uint8_t level);
uint8_t drv_get_power_state();

#endif