#include "drv.h"



/**
 * @brief inits all drv devices
 * 
 */
void drv_init(){
    pinMode(DRV_DEVICE_COUNTER,OUTPUT);

    digitalWrite(DRV_ENABLE_PIN,HIGH);
    Wire.begin();
    for(uint8_t i=0;i<DRV_DEVICE_COUNTER;i++){
        drv_single_init(i);
    }
}

/**
 * @brief inits a single drv device at the given multiplxer channel
 * 
 * @param channel given multiplexer-channel starting from 0 to DRV_DEVICE_COUNTER-1
 */
void drv_single_init(uint8_t channel){
    i2c_multiplexer_change_channel(channel);
}

void drv_init_protocoll(){
    
}

/**
 * @brief state machine for the graph 8.5 on the datasheet https://www.ti.com/lit/ds/symlink/drv2605l.pdf?ts=1669975217122&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FDRV2605L
 * 
 * @param var 
 */
void drv_power_state_machine(uint8_t var){

}


void drv_run(uint8_t chanel, uint8_t level){

}