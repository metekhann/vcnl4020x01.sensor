/*
 * VCNL4020X01.c
 *
 *  Created on: Sep 10, 2023
 *      Author: meteh
 */


#include "VCNL4020X01.h"







static VCNL4020_StatusTypedef_t VCNL4020_LL(VCNL4020_struct *sensor, Ambiant_Typedef_t *ambiant, Proximity_Typedef_t *proximity, VCNL4020_OperationTypedef_t operation)
{
	VCNL4020_StatusTypedef_t status = VCNL_OK;
	uint8_t value = 0;

	switch(operation)
	{

		case	VCNL4020_GET_AMBIANT:

				/*value = 0x10;
				status = (VCNL_StatusTypedef_t)HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;*/

				value = 0x00;
				while(!(value & 0x40))
				{
					status = (VCNL4020_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
					if(status != VCNL_OK)
						return status;
				}

				status = (VCNL4020_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_AMBIENT_LIGHT_RESULT_HB, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;
				*ambiant = (uint16_t)(value << 8);


				status = (VCNL4020_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_AMBIENT_LIGHT_RESULT_LB, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;
				*ambiant |= (uint16_t)(value);

				return status;



		case	VCNL4020_GET_PROX:

				value = 0x08;
				status = (VCNL4020_StatusTypedef_t)HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;


				value = 0x00;
				while(!(value & 0x20))
				{
					status = (VCNL4020_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
					if(status != VCNL_OK)
						return status;
				}

				status = (VCNL4020_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_PROXIMITY_RESULT_HB, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;
				*proximity = (uint16_t)(value << 8);

				status = (VCNL4020_StatusTypedef_t)HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_PROXIMITY_RESULT_LB, 1, &value, 1, sensor->ProgramTimeout);
				if(status != VCNL_OK)
					return status;
				*proximity |= (uint16_t)(value);

				return status;

		case	VCNL4020_GET_PROX_AMBIANT:
				break;

	}
}




VCNL4020_StatusTypedef_t VCNL4020_Init(VCNL4020_struct *sensor, I2C_HandleTypeDef *i2chandle, uint8_t deviceAddress, uint16_t TimeOut)
{
	sensor->deviceADDR = deviceAddress;
	sensor->ProgramTimeout = TimeOut;
	sensor->i2chandle = i2chandle;

	VCNL4020_StatusTypedef_t status = VCNL4020_isConnected(sensor);
	if(status != VCNL_OK)
		return status;


	/*status = VCNL4020_Selftimed_Enable(sensor, VCNL_ENABLE);
	if(status != VCNL_OK)
		return status;


	status = VCNL4020_AmbiantOnDemand_Enable(sensor, VCNL_ENABLE);
	if(status != VCNL_OK)
		return status;

	status = VCNL4020_ProximityOnDemand_Enable(sensor, VCNL_ENABLE);
	if(status != VCNL_OK)
		return status;*/

	return status;

}

VCNL4020_StatusTypedef_t VCNL4020_isConnected(VCNL4020_struct *sensor)
{
	if(HAL_I2C_IsDeviceReady(sensor->i2chandle, sensor->deviceADDR, 5, sensor->ProgramTimeout) == HAL_OK)
		return VCNL_OK;

	return VCNL_ERROR;
}





VCNL4020_StatusTypedef_t VCNL4020_Read(VCNL4020_struct *sensor, uint8_t regAddr, uint8_t *pData)
{
	VCNL4020_StatusTypedef_t status = VCNL_OK;

	status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, regAddr, 1, pData, 1, sensor->ProgramTimeout);

	return status;
}




VCNL4020_StatusTypedef_t VCNL4020_Write(VCNL4020_struct *sensor, uint8_t regAddr, uint8_t *pData)
{
	VCNL4020_StatusTypedef_t status = VCNL_OK;

	status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, regAddr, 1, pData, 1, sensor->ProgramTimeout);

	return status;
}

VCNL4020_StatusTypedef_t VCNL4020_AmbiantOnDemand_Enable(VCNL4020_struct *sensor, VCNL4020_FunctionalStateTypedef_t state)
{
	VCNL4020_StatusTypedef_t status = VCNL_OK;
	uint8_t value = 0;



	if(state == VCNL_ENABLE)
	{
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		value |= (0x1 << 2);
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		return VCNL_OK;
	}
	else
	{
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		value &= ~(0x1 << 2);
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		return VCNL_OK;
	}
}

VCNL4020_StatusTypedef_t VCNL4020_ProximityOnDemand_Enable(VCNL4020_struct *sensor, VCNL4020_FunctionalStateTypedef_t state)
{
	VCNL4020_StatusTypedef_t status = VCNL_OK;
	uint8_t value = 0;



	if(state == VCNL_ENABLE)
	{
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		value |= (0x1 << 1);
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		return VCNL_OK;
	}
	else
	{
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		value &= ~(0x1 << 1);
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		return VCNL_OK;
	}
}

VCNL4020_StatusTypedef_t VCNL4020_Selftimed_Enable(VCNL4020_struct *sensor, VCNL4020_FunctionalStateTypedef_t state)
{
	VCNL4020_StatusTypedef_t status = VCNL_OK;
	uint8_t value = 0;



	if(state == VCNL_ENABLE)
	{
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		value |= (0x1 << 0);
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		return VCNL_OK;
	}
	else
	{
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Read(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		value &= ~(0x1 << 0);
		status = (VCNL4020_StatusTypedef_t) HAL_I2C_Mem_Write(sensor->i2chandle, sensor->deviceADDR, VCNL_REG_COMMAND, 1, &value, 1, sensor->ProgramTimeout);
		if(status != VCNL_OK)
			return status;

		return VCNL_OK;
	}
}

VCNL4020_StatusTypedef_t VCNL4020_GetAmbiant_RAW(VCNL4020_struct *sensor)
{
	return VCNL4020_LL(sensor, &sensor->Ambiant_RawValue, 0, VCNL4020_GET_AMBIANT );
}





float VCNL4020_GetAmbiant(VCNL4020_struct *sensor, float *ambiant)
{
	return VCNL4020_convertRawAmbiant(VCNL4020_LL(sensor, &sensor->Ambiant_RawValue, 0, VCNL4020_GET_AMBIANT ));
}




float VCNL4020_convertRawAmbiant(Ambiant_Typedef_t rawAmbiant)
{
	return ((float)(rawAmbiant) / 4);
}




VCNL4020_StatusTypedef_t VCNL4020_GetProximity_RAW(VCNL4020_struct *sensor)
{
	return VCNL4020_LL(sensor, 0, &sensor->Proximity_RawValue, VCNL4020_GET_PROX );
}



float VCNL4020_convertRawProximity(Proximity_Typedef_t rawProximity)
{
	return ((float)(rawProximity) / 4);
}


VCNL4020_StatusTypedef_t VCNL4020_SetLowTH(VCNL4020_struct *sensor)
{
	VCNL4020_StatusTypedef_t status = VCNL_OK;
	uint8_t value = 0;

	value = (uint8_t)(VCNL_AMBIANT_LOW_TH >> 8);

	status = VCNL4020_Write(sensor, VCNL_REG_LOW_THRESHOLD_HB, &value);
	if(status != VCNL_OK)
		return status;

	value = (uint8_t)(VCNL_AMBIANT_LOW_TH & 0xFF);
	status = VCNL4020_Write(sensor, VCNL_REG_LOW_THRESHOLD_LB, &value);
	if(status != VCNL_OK)
		return status;

	return status;
}

VCNL4020_StatusTypedef_t VCNL4020_SetHighTH(VCNL4020_struct *sensor)
{
	VCNL4020_StatusTypedef_t status = VCNL_OK;
	uint8_t value = 0;

	value = (VCNL_AMBIANT_HIGH_TH >> 8);

	status = VCNL4020_Write(sensor, VCNL_REG_HIGH_THRESHOLD_HB, &value);
	if(status != VCNL_OK)
		return status;

	value = (VCNL_AMBIANT_HIGH_TH & 0xFF);
	status = VCNL4020_Write(sensor, VCNL_REG_HIGH_THRESHOLD_LB, &value);
	if(status != VCNL_OK)
		return status;

	return status;
}

/*VCNL4020_StatusTypedef_t VCNL4020_Ambiant_Interrupt_Enable(VCNL4020_struct *sensor)
{
	VCNL4020_StatusTypedef_t status = VCNL_OK;
	uint8_t value = 0;


	status = VCNL4020_Read(sensor, VCNL_REG_INTERRUPT_CONTROL, &value);
	if(status != VCNL_OK)
		return status;


	value |= (0x3 << 0);
	status = VCNL4020_Write(sensor, VCNL_REG_INTERRUPT_CONTROL, &value);
	if(status != VCNL_OK)
		return status;

	value = 0x0F;
	status = VCNL4020_Write(sensor, VCNL_REG_INTERRUPT_STATUS, &value);
	if(status != VCNL_OK)
		return status;



	return status;
}*/
#define REGISTER_INTERRUPT_CONTROL                                                        (0x89)
#define INTERRUPT_COUNT_EXCEED_1                                                           (0x00)
#define INTERRUPT_THRES_ENABLE                                                                 (0x02)
#define INTERRUPT_THRES_SEL_ALS                                                                (0x01)
#define REGISTER_INTERRUPT_STATUS                                                           (0x8e)
#define INTERRUPT_STATUS_THRES_HI                                                           (0x01)
#define INTERRUPT_STATUS_ALS_READY                                                        (0x04)
#define REGISTER_INTERRUPT_LOW_THRES                                                  (0x8a)
#define REGISTER_INTERRUPT_HIGH_THRES                                                   (0x8c)
#define REGISTER_COMMAND                                                                          (0x80)
#define COMMAND_SELFTIMED_MODE_ENABLE                                          (0x01)
#define COMMAND_AMBI_ENABLE                                                                  (0x04)

#define AMBI_LOW_THRESHOLD_BOTTOM                                                   (0)
#define AMBI_HIGH_THRESHOLD_BOTTOM                                                   (260)
#define AMBI_LOW_THRESHOLD_TOP                                                            (0)
#define AMBI_HIGH_THRESHOLD_TOP                                                           (5)


VCNL4020_StatusTypedef_t VCNL4020_Ambiant_Interrupt_Enable(VCNL4020_struct *sensor)
{
	uint8_t value = 0;

	value = (INTERRUPT_COUNT_EXCEED_1 | INTERRUPT_THRES_ENABLE|INTERRUPT_THRES_SEL_ALS);
	VCNL4020_Write(sensor,REGISTER_INTERRUPT_CONTROL, &value );


	value = 0;
	value = (INTERRUPT_STATUS_THRES_HI|INTERRUPT_STATUS_ALS_READY);
	VCNL4020_Write(sensor,REGISTER_INTERRUPT_STATUS, &value);


	value = 0;
	value = (AMBI_LOW_THRESHOLD_BOTTOM&0xFF00)>>8;
	VCNL4020_Write(sensor,REGISTER_INTERRUPT_LOW_THRES,&value);


	value = 0;
	value = (AMBI_LOW_THRESHOLD_BOTTOM&0x00FF);
	VCNL4020_Write(sensor,REGISTER_INTERRUPT_LOW_THRES+1,&value);


	value = 0;
	value = (AMBI_HIGH_THRESHOLD_BOTTOM&0xFF00)>>8;
	VCNL4020_Write(sensor,REGISTER_INTERRUPT_HIGH_THRES,&value);


	value = 0;
	value = (AMBI_HIGH_THRESHOLD_BOTTOM&0x00FF);
	VCNL4020_Write(sensor,REGISTER_INTERRUPT_HIGH_THRES+1, &value);





				 /* if(VCNL4020_OK != VCNL4020_Write(me,REGISTER_INTERRUPT_LOW_THRES,(AMBI_LOW_THRESHOLD_BOTTOM&0xFF00)>>8))
				  {
								return VCNL4020_ERROR;
				  }
				  if(VCNL4020_OK != VCNL4020_Write(me,REGISTER_INTERRUPT_LOW_THRES+1,(AMBI_LOW_THRESHOLD_BOTTOM&0x00FF)))
				  {
								return VCNL4020_ERROR;
				  }
				  if( VCNL4020_OK != VCNL4020_Write(me,REGISTER_INTERRUPT_HIGH_THRES,(AMBI_HIGH_THRESHOLD_TOP&0xFF00)>>8))
				  {
								return VCNL4020_ERROR;
				  }
				  if( VCNL4020_OK != VCNL4020_Write(me,REGISTER_INTERRUPT_HIGH_THRES+1,(AMBI_HIGH_THRESHOLD_TOP&0x00FF)))
				  {
								return VCNL4020_ERROR;
				  }*/

	 value = 0;
	 value = (COMMAND_SELFTIMED_MODE_ENABLE | COMMAND_AMBI_ENABLE);
	 VCNL4020_Write(sensor, REGISTER_COMMAND, &value);





	return VCNL_OK;


}

VCNL4020_StatusTypedef_t VCNL4020_Proximity_Interrupt_Enable(VCNL4020_struct *sensor)
{
	VCNL4020_StatusTypedef_t status = VCNL_OK;
	uint8_t value = 0;


	status = VCNL4020_Read(sensor, VCNL_REG_INTERRUPT_CONTROL, &value);
	if(status != VCNL_OK)
		return status;


	value |= (0x1 << 1);
	value &= ~(0x1 << 0);
	status = VCNL4020_Write(sensor, VCNL_REG_INTERRUPT_CONTROL, &value);
	if(status != VCNL_OK)
		return status;

	return status;
}



