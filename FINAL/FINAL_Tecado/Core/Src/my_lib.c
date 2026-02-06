#include "my_lib.h"

/* ===== Handle del Timer ===== */
TIM_HandleTypeDef htim2;
uint8_t flag_LEER = 0, flag_BLINK = 0;
uint16_t pulse_count = 0;
uint8_t deBounce_count = 0;
#define _max_count 1000;

/* ===== System Clock ===== */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_TIM2;
  PeriphClkInit.Tim2ClockSelection = RCC_TIM2CLK_HCLK;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
}

/* ===== GPIO ===== */
void MX_GPIO_Init(void)
{

	//CONFIGURACIÓN LED
	GPIO_InitTypeDef LED_Pin_Conf = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();

	HAL_GPIO_WritePin(LED_PORT, LED_PIN, LED_OFF);

	LED_Pin_Conf.Pin = LED_PIN;
	LED_Pin_Conf.Mode = GPIO_MODE_OUTPUT_PP;
	LED_Pin_Conf.Pull = GPIO_NOPULL;
	LED_Pin_Conf.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(LED_PORT, &LED_Pin_Conf);

	//CONFIGURACIÓN PARA TECLADO
	  GPIO_InitTypeDef KEY_PORT_Conf = {0};

	  //Configuración teclado
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  HAL_GPIO_WritePin(KEY_PORT, F1_PIN, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(KEY_PORT, F2_PIN, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(KEY_PORT, F3_PIN, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(KEY_PORT, F4_PIN, GPIO_PIN_RESET);

	  //Las filas son outputs (las prendo y apago)
	  KEY_PORT_Conf.Pin = F1_PIN | F2_PIN | F3_PIN | F4_PIN;
	  KEY_PORT_Conf.Mode = GPIO_MODE_OUTPUT_PP;
	  KEY_PORT_Conf.Pull = GPIO_NOPULL;
	  KEY_PORT_Conf.Speed = GPIO_SPEED_FREQ_HIGH;

	  HAL_GPIO_Init(KEY_PORT, &KEY_PORT_Conf);

	  //Las columnas son inputs (las leo)
	  KEY_PORT_Conf.Pin = C1_PIN | C2_PIN | C3_PIN | C4_PIN;
	  KEY_PORT_Conf.Mode = GPIO_MODE_INPUT;
	  KEY_PORT_Conf.Pull = GPIO_NOPULL;

	  HAL_GPIO_Init(KEY_PORT, &KEY_PORT_Conf);
}

/* ===== TIM2 1 kHz ===== */
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  __HAL_RCC_TIM2_CLK_ENABLE();

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = LED_PRESCALER-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = _LedPeriod(80);
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_Base_Init(&htim2);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

  /* NVIC */
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

/* ===== CALLBACK TIMER ===== */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
  }
}


void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);

  //PULSOS PARA LEER LA MATRIZ
  flag_LEER = (flag_LEER == 0) ? 1 : 0;

  //PULSOS PARA ENCENDER LED
  pulse_count++;
  if (pulse_count == 100)
  {
	  pulse_count = 0;
	  flag_BLINK = (flag_BLINK == 0)? 1 : 0;   // levanto flag
  }

  //PULSOS PARA DEBOUNCE
  if(deBounce_count > 0) deBounce_count--;
}

