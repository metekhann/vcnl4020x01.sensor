/*
 * VCNL4020X01.c
 *
 *  Created on: Sep 10, 2023
 *      Author: meteh
 */


#include "VCNL4020X01.h"





VCNL_StatusTypedef_t VCNL_Init(VCNL_struct *sensor, I2C_HandleTypeDef *i2chandle, uint8_t deviceAddress, uint16_t TimeOut)
{
	sensor->deviceADDR = deviceAddress;
	sensor->ProgramTimeout = TimeOut;
	sensor->i2chandle = i2chandle;

	VCNL_StatusTypedef_t status = VCNL_isConnected(sensor);
	return status;


}

VCNL_StatusTypedef_t VCNL_isConnected(VCNL_struct *sensor)
{
	if(HAL_I2C_IsDeviceReady(sensor->i2chandle, sensor->deviceADDR, 5, sensor->ProgramTimeout))
		return VCNL_OK;

	return VCNL_ERROR;
}



