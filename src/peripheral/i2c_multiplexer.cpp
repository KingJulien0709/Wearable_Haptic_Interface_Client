#include "i2c_multiplexer.h"

#define I2C_MULTIPLEXER_ADRESS 0x70

/**
 * @brief Change the channel of the multiplexer
 * 
 * @param channel from 0-7
 */
void i2c_change_channel(uint8_t channel){
    i2c_write_without_register(I2C_MULTIPLEXER_ADRESS,1<<(channel+1));
}