/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "VCNL4020X01.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TEMP_REG		(0x00)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

VCNL_struct sensor1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
static void print_m(const char *data, ...);
static void toBinary(uint16_t source , char* target);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char Buffer[20];
char uart_data;
char resultBuffer[20];
uint8_t index_Buffer;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
HAL_StatusTypeDef status = HAL_ERROR;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */


  HAL_Delay(1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  if(VCNL4020_Init(&sensor1, &hi2c1, VCNL_SLAVE_ADDRESS, 1000) == VCNL_OK)
  				{
  					//VCNL_GetLight(&sensor1, &light_sensor);
  					print_m("\nbasarili\n");


  				}
  				else
  					HAL_UART_Transmit(&huart1, (uint8_t*)"basarisiz\n", 10, 1000);
  if(VCNL4020_GetProximity_RAW(&sensor1) == VCNL_OK)
  	  				{
  	    					print_m("\nolcum_alindi\n");
  	    					toBinary(sensor1.Proximity_RawValue, resultBuffer);
  	    					print_m("\n%s\n",resultBuffer);
  	  				}
  	  				else
  	  					print_m("\nolcum_alinamadi\n");

  HAL_UART_Receive_IT(&huart1, (uint8_t*)&uart_data, 1);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



/*	  if(VCNL4020_GetProximity_RAW(&sensor1) == VCNL_OK)
	  				{
	    					print_m("\nolcum_alindi\n");
	    					toBinary(sensor1.Proximity_RawValue, resultBuffer);
	    					print_m("\n%s\n",resultBuffer);
	  				}
	  				else
	  					print_m("\nolcum_alinamadi\n");
	  HAL_Delay(500);


*/


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC1 PC3 PC4 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static void print_m(const char *data, ...)
{
	va_list arg;
	const char *tempData = data;
	char c;
	int d;
	char integerBuffer[20];
	char *s;
	va_start(arg, data);

	while(*tempData != '\0')
	{
		if(*tempData == '%')
		{
			if(*(tempData + 1) == 'c')
			{
				c = va_arg(arg , int);
				HAL_UART_Transmit(&huart1,(uint8_t *)&c , 1, 1000);
				tempData++;
			}
			else if(*(tempData + 1) == 'd')
			{
				d = va_arg(arg, int);
				itoa(d, integerBuffer,10);
				HAL_UART_Transmit(&huart1,(uint8_t *)integerBuffer , strlen(integerBuffer), 2000);
				tempData++;
			}
			else if(*(tempData + 1) == 's')
			{
				s = va_arg(arg, char*);
				HAL_UART_Transmit(&huart1,(uint8_t *)s , strlen(s), 2000);
				tempData++;
			}
			else
			{
				HAL_UART_Transmit(&huart1,(uint8_t *)"%" , 1, 2000);
			}
		}
		else
		{
			HAL_UART_Transmit(&huart1,(uint8_t *)tempData , 1, 2000);
		}
		tempData++;
	}

	//USART_Transmit(&huart, (uint8_t*)data, 20);
	va_end(arg);

}
static void toBinary(uint16_t source , char* target)
{
	for(int i = 0; i < 16; i++)
	{
		if((source & (0x1 << (16-i))))
		{
			target[i] = '1';
		}
		else
		{
			target[i] = '0';
		}

	}
	target[16] = '\0';
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart1)
	{
		if(uart_data == 0x0D)
		{
			if(!strcmp(Buffer, "basla"))
			{
				print_m("\nbasladi\n");
			}
			else if(!strcmp(Buffer, "sensorinit"))
			{
				if(VCNL4020_Init(&sensor1, &hi2c1, VCNL_SLAVE_ADDRESS, 1000) == VCNL_OK)
				{
					//VCNL_GetLight(&sensor1, &light_sensor);
					print_m("\nbasarili\n");


				}
				else
					HAL_UART_Transmit(&huart1, (uint8_t*)"basarisiz\n", 10, 1000);
			}
			else if(!strcmp(Buffer, "light"))
			{
				if(VCNL4020_GetAmbiant_RAW(&sensor1) == VCNL_OK)
				{
  					print_m("\nolcum_alindi\n");
  					toBinary(sensor1.Ambiant_RawValue, resultBuffer);
  					print_m("\n%s\n",resultBuffer);
				}
				else
					print_m("\nolcum_alinamadi\n");
			}
			else if(!strcmp(Buffer, "prox"))
			{
				if(VCNL4020_GetProximity_RAW(&sensor1) == VCNL_OK)
				{
  					print_m("\nolcum_alindi\n");
  					toBinary(sensor1.Proximity_RawValue, resultBuffer);
  					print_m("\n%s\n",resultBuffer);
				}
				else
					print_m("\nolcum_alinamadi\n");
			}

			index_Buffer = 0;
			memset(Buffer, 0, 20);
		}
		else
		{
			Buffer[index_Buffer] = uart_data;
			index_Buffer++;
		}

		HAL_UART_Receive_IT(&huart1, (uint8_t*)&uart_data, 1);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
