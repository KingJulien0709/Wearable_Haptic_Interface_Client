#include "i2c_multiplexer.h"

#define I2C_MULTIPLEXER_ADRESS 0x70


void i2c_multiplexer_init(){

}
/**
 * @brief Change the channel of the multiplexer
 * 
 * @param channel from 0-7
 */
void i2c_multiplexer_change_channel(uint8_t channel){
    i2c_write_without_register(I2C_MULTIPLEXER_ADRESS,1<<(channel+1));
}

/**
 * @brief Reset multiplexer. See 10.1 Power-On Reset Requirements on Datasheet: file:///C:/Users/kinde/Downloads/1811081942_Texas-Instruments-TCA9548APWR_C130026.pdf
 * 
 */
void i2c_multiplexer_reset(uint8_t resetPin){
    //TODO: implement function
}