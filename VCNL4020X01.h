/*
 * VCNL4020X01.h
 *
 *  Created on: Sep 10, 2023
 *      Author: meteh
 */

#ifndef SENSOR_DRIVER_INC_VCNL4020X01_H_
#define SENSOR_DRIVER_INC_VCNL4020X01_H_

#include "stm32l1xx_hal.h"

/*
 * defines
 *
 */

#define VCNL_SLAVE_ADDRESS							(0x13 << 1)



#define VCNL_REG_COMMAND							(0x80)
#define VCNL_REG_PRODUCT_ID_REVISION				(0x81)
#define VCNL_REG_PROXIMITY_RATE						(0x82)
#define VCNL_REG_IR_LED_CURRENT						(0x83)
#define VCNL_REG_AMBIENT_LIGHT_PARAMETER			(0x84)
#define VCNL_REG_AMBIENT_LIGHT_RESULT_HB			(0x85)
#define VCNL_REG_AMBIENT_LIGHT_RESULT_LB			(0x86)
#define VCNL_REG_PROXIMITY_RESULT_HB				(0x87)
#define VCNL_REG_PROXIMITY_RESULT_LB				(0x88)
#define VCNL_REG_INTERRUPT_CONTROL					(0x89)
#define VCNL_REG_LOW_THRESHOLD_HB					(0x8A)
#define VCNL_REG_LOW_THRESHOLD_LB					(0x8B)
#define VCNL_REG_HIGH_THRESHOLD_HB					(0x8C)
#define VCNL_REG_HIGH_THRESHOLD_LB					(0x8D)
#define VCNL_REG_INTERRUPT_STATUS					(0x8E)
#define VCNL_REG_PROXIMITY MODULATOR				(0x8F)

typedef uint16_t Ambiant_Typedef_t;
typedef uint16_t Proximity_Typedef_t;


#define VCNL_AMBIANT_LOW_TH							((uint16_t)(0x0004))
#define VCNL_AMBIANT_HIGH_TH						((uint16_t)(0x0400))


/*
 * @brief  VCNL Status enum definition
 *
 */


typedef enum
{
	VCNL_ENABLE				= 1U,
	VCNL_DISABLE			= 0U

}VCNL4020_FunctionalStateTypedef_t;


typedef enum
{
	VCNL_OK			= 0x00,
	VCNL_ERROR		= 0x01,
	VCNL_BUSY		= 0x02,
	VCNL_TIMEOUT	= 0x03

}VCNL4020_StatusTypedef_t;


typedef enum
{
	VCNL4020_GET_PROX				= 0x00,
	VCNL4020_GET_AMBIANT			= 0x01,
	VCNL4020_GET_PROX_AMBIANT		= 0x02,

}VCNL4020_OperationTypedef_t;


/*
 * @brief VCNL Struct
 *
 */

typedef struct
{
	I2C_HandleTypeDef 		*i2chandle;
	uint8_t 				deviceADDR;
	uint16_t				ProgramTimeout;
	Ambiant_Typedef_t		Ambiant_RawValue;
	Proximity_Typedef_t		Proximity_RawValue;

}VCNL4020_struct;







VCNL4020_StatusTypedef_t VCNL4020_Init(VCNL4020_struct *sensor, I2C_HandleTypeDef *i2chandle, uint8_t deviceAddress, uint16_t TimeOut);
VCNL4020_StatusTypedef_t VCNL4020_isConnected(VCNL4020_struct *sensor);
VCNL4020_StatusTypedef_t VCNL4020_Read(VCNL4020_struct *sensor, uint8_t regAddr, uint8_t *pData);
VCNL4020_StatusTypedef_t VCNL4020_Write(VCNL4020_struct *sensor, uint8_t regAddr, uint8_t *pData);
VCNL4020_StatusTypedef_t VCNL4020_AmbiantOnDemand_Enable(VCNL4020_struct *sensor, VCNL4020_FunctionalStateTypedef_t state);
VCNL4020_StatusTypedef_t VCNL4020_ProximityOnDemand_Enable(VCNL4020_struct *sensor, VCNL4020_FunctionalStateTypedef_t state);
VCNL4020_StatusTypedef_t VCNL4020_Selftimed_Enable(VCNL4020_struct *sensor, VCNL4020_FunctionalStateTypedef_t state);
VCNL4020_StatusTypedef_t VCNL4020_GetAmbiant_RAW(VCNL4020_struct *sensor);
float VCNL4020_GetAmbiant(VCNL4020_struct *sensor, float *ambiant);
float VCNL4020_convertRawAmbiant(Ambiant_Typedef_t rawAmbiant);
VCNL4020_StatusTypedef_t VCNL4020_GetProximity_RAW(VCNL4020_struct *sensor);
VCNL4020_StatusTypedef_t VCNL4020_SetLowTH(VCNL4020_struct *sensor);
VCNL4020_StatusTypedef_t VCNL4020_SetHighTH(VCNL4020_struct *sensor);
VCNL4020_StatusTypedef_t VCNL4020_Ambiant_Interrupt_Enable(VCNL4020_struct *sensor);
VCNL4020_StatusTypedef_t VCNL4020_Proximity_Interrupt_Enable(VCNL4020_struct *sensor);


#endif /* SENSOR_DRIVER_INC_VCNL4020X01_H_ */
