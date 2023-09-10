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
#define VCNL_REG_INTERRUPT_STATUS					(0x8E)
#define VCNL_REG_PROXIMITY MODULATOR				(0x8F)



/*
 * @brief  VCNL Status enum definition
 *
 */

typedef enum
{
	VCNL_OK			= 0x00,
	VCNL_ERROR		= 0x01,
	VCNL_BUSY		= 0x02,
	VCNL_TIMEOUT	= 0x03

}VCNL_StatusTypedef_t;




/*
 * @brief VCNL Struct
 *
 */

typedef struct
{
	I2C_HandleTypeDef *i2chandle;
	uint8_t 			deviceADDR;
	uint16_t			ProgramTimeout;
	//uint8_t				Prox_Mode;
	//uint8_t				Als_Mode;

}VCNL_struct;

VCNL_StatusTypedef_t VCNL_Init(VCNL_struct *sensor, I2C_HandleTypeDef *i2chandle, uint8_t deviceAddress, uint16_t TimeOut);
VCNL_StatusTypedef_t VCNL_isConnected(VCNL_struct *sensor);

#endif /* SENSOR_DRIVER_INC_VCNL4020X01_H_ */
