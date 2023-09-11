/*
 * VCNL4020X01.c
 *
 *  Created on: Sep 10, 2023
 *      Author: meteh
 */


#include "VCNL4020X01.h"







static VCNL_StatusTypedef_t VCNL4020_LL(VCNL_struct *sensor, Ambiant_Typedef_t *ambiant, Proximity_Typedef_t *proximity, VCNL_OperationTypedef_t operation)
{
	VCNL_StatusTypedef_t status = VCNL_OK;
	uint8_t value = 0;

	switch(operation)
	{

		case	VCNL4020_GET_AMBIANT:

				value = 0x10;
				status = (VCNL_StatusTypedef_t)HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;

				value = 0x00;
				while(!(value & 0x40))
				{
					status = (VCNL_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
					if(status != VCNL_OK)
						return status;
				}

				status = (VCNL_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_AMBIENT_LIGHT_RESULT_HB, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;
				*ambiant = (uint16_t)(value << 8);


				status = (VCNL_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_AMBIENT_LIGHT_RESULT_LB, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;
				*ambiant |= (uint16_t)(value);

				return status;



		case	VCNL4020_GET_PROX:

				value = 0x08;
				status = (VCNL_StatusTypedef_t)HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;


				value = 0x00;
				while(!(value & 0x20))
				{
					status = (VCNL_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
					if(status != VCNL_OK)
						return status;
				}

				status = (VCNL_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_PROXIMITY_RESULT_HB, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;
				*proximity = (uint16_t)(value << 8);

				status = (VCNL_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_PROXIMITY_RESULT_LB, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;
				*proximity |= (uint16_t)(value);

				return status;

		case	VCNL4020_GET_PROX_AMBIANT:
				break;

	}
}




VCNL_StatusTypedef_t VCNL4020_Init(VCNL_struct *sensor, I2C_HandleTypeDef *i2chandle, uint8_t deviceAddress, uint16_t TimeOut)
{
	sensor->deviceADDR = deviceAddress;
	sensor->ProgramTimeout = TimeOut;
	sensor->i2chandle = i2chandle;

	VCNL_StatusTypedef_t status = VCNL4020_isConnected(sensor);
	return status;


}

VCNL_StatusTypedef_t VCNL4020_isConnected(VCNL_struct *sensor)
{
	if(HAL_I2C_IsDeviceReady(sensor->i2chandle, sensor->deviceADDR, 5, sensor->ProgramTimeout) == HAL_OK)
		return VCNL_OK;

	return VCNL_ERROR;
}


VCNL_StatusTypedef_t VCNL4020_Read(VCNL_struct *sensor, uint8_t regAddr, uint8_t *pData)
{
	VCNL_StatusTypedef_t status = VCNL_OK;

	status = (VCNL_StatusTypedef_t) HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, regAddr, 1, pData, 1, sensor->ProgramTimeout);

	return status;
}

VCNL_StatusTypedef_t VCNL4020_Write(VCNL_struct *sensor, uint8_t regAddr, uint8_t *pData)
{
	VCNL_StatusTypedef_t status = VCNL_OK;

	status = (VCNL_StatusTypedef_t) HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, regAddr, 1, pData, 1, sensor->ProgramTimeout);

	return status;
}

VCNL_StatusTypedef_t VCNL4020_GetAmbiant_RAW(VCNL_struct *sensor)
{
	return VCNL4020_LL(sensor, &sensor->Ambiant_RawValue, 0, VCNL4020_GET_AMBIANT );
}

float VCNL4020_GetAmbiant(VCNL_struct *sensor, float *ambiant)
{
	return VCNL4020_convertRawAmbiant(VCNL4020_LL(sensor, &sensor->Ambiant_RawValue, 0, VCNL4020_GET_AMBIANT ));
}

float VCNL4020_convertRawAmbiant(Ambiant_Typedef_t rawAmbiant)
{
	return ((float)(rawAmbiant) / 4);
}

VCNL_StatusTypedef_t VCNL4020_GetProximity_RAW(VCNL_struct *sensor)
{
	return VCNL4020_LL(sensor, 0, &sensor->Proximity_RawValue, VCNL4020_GET_PROX );
}



float VCNL4020_convertRawProximity(Proximity_Typedef_t rawProximity)
{
	return ((float)(rawProximity) / 4);
}



