#include "ULTRASONIC_SENSOR.h"
#include "stm32f4xx_hal.h"

TIM_HandleTypeDef hledtim; // TIM2 Handler Variable --> Software
uint8_t flag = 0;
uint8_t counter = 0;
uint8_t distancia = 0;

void SystemClock_Config(void);
void GPIO_Init(void);
/* Hardware Configuration */
uint8_t Hw_Init(void){

	/* HAL Initialization	*/
	HAL_Init(); // --> Init Software

	/* CLK Configuration */
	SystemClock_Config(); // --> Init Hardware

	/* GPIO Configuration */
	GPIO_Init(); // --> Init Hardware

	/* TIM2 Configuration */
	TIM2_Config(); // --> Init Hardware


	return(1);
}



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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;


  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
}

void GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_Trigger = {0};
  GPIO_InitTypeDef GPIO_Echo = {0};
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(US_PORT, TRIGGER_PIN, GPIO_PIN_RESET);
  GPIO_Trigger.Pin = TRIGGER_PIN;
  GPIO_Trigger.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_Trigger.Pull = GPIO_NOPULL;
  GPIO_Trigger.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(US_PORT, &GPIO_Trigger);

  GPIO_Echo.Pin = ECHO_PIN;
  GPIO_Echo.Mode = GPIO_MODE_INPUT;
  GPIO_Echo.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(US_PORT, &GPIO_Echo);


}

/* TIM2 Configuration */
void TIM2_Config(void){

	TIM_ClockConfigTypeDef CLK_Source = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/*  TIM Features Load */
	// --> Software
	hledtim.Instance = TIMER;
	hledtim.Init.Prescaler = PRESCALER-1;
	hledtim.Init.CounterMode = TIM_COUNTERMODE_UP;
	hledtim.Init.Period = Period(FREQ_US);
	hledtim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hledtim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	/* TIM Hardware Configuration */
	// --> Hardware
	HAL_TIM_Base_Init(&hledtim);

	/* CLK Source Selection */
	CLK_Source.ClockSource = TIM_CLOCKSOURCE_INTERNAL; // --> Software
	HAL_TIM_ConfigClockSource(&hledtim, &CLK_Source); // --> Hardware

	/* TIM OVF Interrupt Config */
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE; // --> Software
	HAL_TIMEx_MasterConfigSynchronization(&hledtim, &sMasterConfig); // --> Hardware

	/* TIMER RUN (Interruption)	*/
	HAL_TIM_Base_Start_IT(&hledtim); // --> Hardware

	return;
}


/* TIM2 IRQ Definition */
void TIM2_IRQHandler(void)
{

  /* TIM2 IT CATCH */
  HAL_TIM_IRQHandler(&hledtim); // --> Hardware
  if(HAL_GPIO_ReadPin(US_PORT,ECHO_PIN) == 1){
	  counter ++;
  }
  else{
	  distancia = Distancia(counter);
	  counter = 0;
	  /* Flag Change */
	  flag = (flag==1)?	0:1;
  }

  return;
}



