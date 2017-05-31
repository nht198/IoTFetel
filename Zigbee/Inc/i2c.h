#ifndef __I2C_H_
#define __I2C_H_
#include "stm32f1xx_hal.h"

uint8_t scan_address();
uint16_t readValue(uint8_t address);

#endif