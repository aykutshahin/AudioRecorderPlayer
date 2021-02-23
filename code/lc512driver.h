/*
* lc512driver.h
* Author: Aykut Sahin
*
*/

#ifndef LC512DRIVER_H_
#define LC512DRIVER_H_
#include "stm32g0xx.h"

//Initializing EEPROM
void INIT_EEPROM_512();
//Writing single byte
void WriteSingleByte(uint8_t devAddr, uint16_t destAddr, uint8_t data);
//Writing 128 bytes
void WriteMultipleByte(uint8_t devAddr, uint16_t startAddr, uint8_t* data, uint8_t size);
//Reading single byte
void ReadSingleByte(uint8_t devAddr, uint16_t resAddr, uint8_t* data);
//Reading 128 bytes
void ReadMultipleByte(uint8_t devAddr, uint16_t resAddr, uint8_t* data, uint16_t size);

#endif /* LC512DRIVER_H_ */
