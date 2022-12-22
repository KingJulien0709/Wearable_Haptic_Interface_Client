#include "drv.hpp"

uint8_t state;

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
void drv_set_register_for_all_devices(uint8_t address,uint8_t register_v,uint8_t value){
    for(uint8_t i=0;i<DRV_DEVICE_COUNTER;i++){
        i2c_multiplexer_change_channel(i);
        i2c_write_with_register(address, register_v, value);
    }
}

/**
 * @brief state machine for the graph 8.4 on the datasheet https://www.ti.com/lit/ds/symlink/drv2605l.pdf?ts=1669975217122&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FDRV2605L
 * 
 * @param var The state to set the controller
 */
void drv_power_state_machine(uint8_t var, uint8_t channel){
    if(state==DRV_STATE_ACTIVE){
        if(var==DRV_STATE_SHUTDOWN){
            digitalWrite(DRV_ENABLE_PIN,0);
            state=DRV_STATE_SHUTDOWN;
        }else if(var==DRV_STATE_TRANSITION_DEV_RESET){
            drv_set_register_for_all_devices(0x5A,0x01,1);//set bit for devreset in register to 1 TODO change to just change the bit 7 
            state=DRV_STATE_STANDBY;
            state=DRV_STATE_STANDBY;
        }else if(var==DRV_STATE_TRANSITION_DEV_TOGGLE_STANDBY){
            drv_set_register_for_all_devices(0x5A,0x01,1);//set bit for standby in register to 1 TODO change to just change the bit 6 
            state=DRV_STATE_STANDBY;
        }
    }else if(state==DRV_STATE_STANDBY){
        if(var==DRV_STATE_SHUTDOWN){
            digitalWrite(DRV_ENABLE_PIN,0);
            state=DRV_STATE_SHUTDOWN;
        }else if(var==DRV_STATE_ACTIVE){
            drv_set_register_for_all_devices(0x5A,0x01,0);//set bit for standby in register to 0  TODO change to just change the bit 6
            state=DRV_STATE_STANDBY;
            state=DRV_STATE_ACTIVE;
        }
    }else if(state==DRV_STATE_SHUTDOWN){
        if(var==DRV_STATE_STANDBY){
            digitalWrite(DRV_ENABLE_PIN,1);
            state=DRV_STATE_STANDBY;
        }
    }
}


void drv_run(uint8_t chanel, uint16_t level){

}

uint8_t drv_get_power_state(){
    return state;
}