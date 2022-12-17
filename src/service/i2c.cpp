#include "i2c.h"


void i2c_init(uint8_t sd_pin,uint8_t sc_pin){
        Wire.begin(sd_pin,sc_pin);
}
/**
 * @brief 
 * 
 * @param address 7-Bit address
 * @param data_byte 
 */
void i2c_write_without_register(uint8_t address, uint8_t data_byte){
    Wire.beginTransmission(address); 
    Wire.write(data_byte);
    Wire.endTransmission();
}

void i2c_write_with_register(uint8_t address, uint8_t register_address,uint8_t data_byte){
    Wire.beginTransmission(address);
    Wire.write(register_address); 
    Wire.write(data_byte);
    Wire.endTransmission();
}

uint8_t i2c_read_without_register(uint8_t address){
    uint8_t data = 0;
    Wire.requestFrom((int)address, (int) 1);
    while (Wire.available()) {
        data =(uint8_t) Wire.read();
    }
    return data;
}

uint8_t i2c_read_with_register(uint8_t address, uint8_t register_address){
    i2c_write_without_register(address,register_address);//data is register_address
    return i2c_read_without_register(address);
}



