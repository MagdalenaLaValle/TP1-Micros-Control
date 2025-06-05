//INCLUDES
#include "my_lib.h"
#include <math.h>

//MACROS

//VARIABLE GLOBAL
ADC_HandleTypeDef hadc1;
TIM_HandleTypeDef htim2;

uint8_t counter=0, sampling =0;
read_now_t read= _NO;


static void (*timer_callback)();

//DEFINICIÓN DE FUNCIONES GLOBALES (PÚBLICAS)
uint8_t Hw_Init(void){
	HAL_Init();
	SystemClock_Config(); //CONFIGURACIÓN DEL CLOCK
	MX_ADC1_Init(); //CONFIGURACIÓN DEL ADC
	MX_TIM2_Init(); //CONFIGURACIÓN DEL TIMER
	MX_GPIO_Init(); //CONFIGURACIÓ GPIO
	return 1;
}

void Hw_Start(void){
	HAL_TIM_Base_Start_IT(&htim2);
}

//Configuración del CLOCK
void SystemClock_Config(void)
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

//CONFIGURACIÓN DEL ADC
void MX_ADC1_Init(void){
  ADC_ChannelConfTypeDef sConfig = {0};
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  HAL_ADC_Init(&hadc1);

  /*if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }*/

  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

void MX_TIM2_Init(void){
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = TIM_PRESCALER - 1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = (uint32_t) _CalcPeriod(frec);
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
	Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
	Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
	Error_Handler();
	}
}

//CONFIGURACIÓN GPIO
void MX_GPIO_Init(void){
	GPIO_InitTypeDef TRANS_Conf = {0};
	GPIO_InitTypeDef ADC_Pin_Conf = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, TRANS_PIN, GPIO_PIN_RESET);

	/*Configure GPIO pin : PA10 */
	TRANS_Conf.Pin = TRANS_PIN;
	TRANS_Conf.Mode = GPIO_MODE_OUTPUT_PP;
	TRANS_Conf.Pull = GPIO_NOPULL;
	TRANS_Conf.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOA, &TRANS_Conf);

	/* ADC Pin Hardware Configuration */
	__HAL_RCC_ADC1_CLK_ENABLE();
	ADC_Pin_Conf.Pin = GPIO_PIN_0;
	ADC_Pin_Conf.Mode = GPIO_MODE_ANALOG;
	ADC_Pin_Conf.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &ADC_Pin_Conf);
}

void setTimerCallback(void (*callback_fn)()){
	timer_callback = callback_fn;
}

void TIM2_IRQHandler(void){ //TIM2 IRQ definition
	/* if(sampling > 0) sampling--;
	else sampling = ADC_Sampling_Period;*/

	HAL_TIM_IRQHandler(&htim2);


  read = (counter == (COUNT_MUESTREO - 1))? _YES : _NO;
  if(counter < (COUNT_MUESTREO -1) ){
	  counter++;
  }
  else {
	  counter = 0;
	  if(timer_callback){
		  timer_callback();	// Ejecutar la funcion de callback
	  }
  }
}



//ERROR HANDLER
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



