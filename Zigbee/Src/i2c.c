#include "i2c.h"

extern I2C_HandleTypeDef hi2c2;

uint8_t scan_address()
{
	int address,error;
	for(address = 1; address < 127; address++ ) 
  {
		error = HAL_I2C_IsDeviceReady(&hi2c2,address<<1,2,500);
		if(error == 0)
			return address;
	}
	return 0;
}

uint16_t readValue(uint8_t address)
{
	uint16_t value;
	uint8_t addrToRead[2],dataRead[4];
	switch (address)
	{
		case 0x23: 
			addrToRead[0] = 0x10;
			HAL_I2C_Master_Transmit(&hi2c2,(address<<1),addrToRead,1,50);
			HAL_I2C_Master_Receive(&hi2c2,(address<<1) | 0x01,dataRead,2,50);
			value=((dataRead[0]<<8)|dataRead[1])/1.2;
			break;
		case 0x40:
			addrToRead[0] = 0x00;
			HAL_I2C_Master_Transmit(&hi2c2,(address<<1),addrToRead,1,50);
			HAL_I2C_Master_Receive(&hi2c2,(address<<1) | 0x01,dataRead,4,50);
			value=((dataRead[0]<<8)|dataRead[1])* 165.0 / 65536.0 - 40.0;
		default:
			value = 0;
			break;
	}
	return value;
}