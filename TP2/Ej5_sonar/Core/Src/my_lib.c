//INCLUDES
#include "my_lib.h"


//VARIABLE GLOBAL
TIM_HandleTypeDef hledtim ;
I2C_HandleTypeDef hi2c1 ;

const uint8_t DELAY_1S = 0x8;

uint8_t flag=0;


//DEFINICIÓN DE FUNCIONES GLOBALES (PÚBLICAS)
uint8_t Hw_Init(void){
	HAL_Init();
	TIM2_Config();
	SystemClock_Config();
	MX_I2C1_Init();
	MX_GPIO_Init();
	TIM2_IRQHandler();
	return 1;
}


//DEFINICIÓN DE FUNCIONES PRIVADAS
SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

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

void MX_I2C1_Init(void){
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
}

void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

void TIM2_Config(void){
	  TIM_ClockConfigTypeDef CLK_Source = {0};
	  TIM_MasterConfigTypeDef sMasterConfig = {0};

	  // T = (ARR+1)(PSC+1) / SystemCoreClock
	  hledtim.Instance = LED_TIMER; //LED_TIMER está definido como htim2 en my_lib.h
	  hledtim.Init.Prescaler = LED_PRESCALER -1;
	  hledtim.Init.CounterMode = TIM_COUNTERMODE_UP;
	  hledtim.Init.Period =  (uint32_t) _LedPeriod(frec);
	  hledtim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  hledtim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	  HAL_TIM_Base_Init(& hledtim);

	  CLK_Source.ClockSource = TIM_CLOCKSOURCE_INTERNAL; //esto de acá es software, sólo estoy cambiando la variable
	  HAL_TIM_ConfigClockSource(&hledtim, &CLK_Source); //esto es HARD.


	  //Esto habilita el tipo de interrupción. Le dice, de todas las formas que teneés de interrumpir, hacelo sólo cuando se desborde el contadpr
	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	  HAL_TIMEx_MasterConfigSynchronization(&hledtim, &sMasterConfig);

	  //Esto hace que empiece a correr el cronómetro. Esto es hardware
	  HAL_TIM_Base_Start_IT(&hledtim);

	  return;
}

void TIM2_IRQHandler(void){ //TIM2 IRQ definition
  HAL_TIM_IRQHandler(&hledtim);
  flag = (flag==0)? 1: 0;
}

void Error_Handler(void){
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

void transmitir(uint16_t DevAddress, uint8_t *pData, uint16_t Size){
	HAL_I2C_Master_Transmit(&hi2c3, DevAddress, &pData, Size, DELAY_1S);
}
