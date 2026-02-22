#include "my_lib.h"


TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart1;
I2C_HandleTypeDef hi2c1;

uint8_t UART1_rxBuffer[DATA_LENGTH] = {0};

volatile uint8_t deBounce_count[CANT_FILAS][CANT_COLUMNAS] = {0};
#define _max_count 1000
volatile uint8_t flag_100ms = 0, flag_500ms = 0, flag_1s = 0, UART_flag = 0;
volatile uint16_t cnt_100ms = 0, cnt_500ms = 0, cnt_1s = 0;

void Hardware_Init(void){
  HAL_Init();
  SystemClock_Config();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_GPIO_Init();
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  MX_USART1_UART_Init();
}

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
void MX_GPIO_Init(void){
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//CONFIGURACIÓN PARA MOTOR
	GPIO_InitTypeDef MOTOR_Pin_Conf = {0};

	HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_RESET);

	MOTOR_Pin_Conf.Pin = MOTOR_PIN;
	MOTOR_Pin_Conf.Mode = GPIO_MODE_OUTPUT_PP;
	MOTOR_Pin_Conf.Pull = GPIO_NOPULL;
	MOTOR_Pin_Conf.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(MOTOR_PORT, &MOTOR_Pin_Conf);


	//CONFIGURACIÓN PARA TECLADO
	GPIO_InitTypeDef KEY_PORT_FILAS_Conf = {0};
	GPIO_InitTypeDef KEY_PORT_COLS_Conf = {0};

	//Las filas son outputs (las prendo y apago)
	HAL_GPIO_WritePin(KEY_PORT, F1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(KEY_PORT, F2_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(KEY_PORT, F3_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(KEY_PORT, F4_PIN, GPIO_PIN_RESET);

	KEY_PORT_FILAS_Conf.Pin = F1_PIN | F2_PIN | F3_PIN | F4_PIN;
	KEY_PORT_FILAS_Conf.Mode = GPIO_MODE_OUTPUT_PP;
	KEY_PORT_FILAS_Conf.Pull = GPIO_NOPULL;
	KEY_PORT_FILAS_Conf.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(KEY_PORT, &KEY_PORT_FILAS_Conf);

	//Las columnas son inputs (las leo)
	KEY_PORT_COLS_Conf.Pin = C1_PIN | C2_PIN | C3_PIN | C4_PIN;
	KEY_PORT_COLS_Conf.Mode = GPIO_MODE_INPUT;
	KEY_PORT_COLS_Conf.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(KEY_PORT, &KEY_PORT_COLS_Conf);


	//CONFIGURACIÓN PARA FINAL DE CARRERA
	GPIO_InitTypeDef FINAL_CARRERA_Conf = {0};

	FINAL_CARRERA_Conf.Pin = INICIO_PIN | FINAL_PIN;
	FINAL_CARRERA_Conf.Mode = GPIO_MODE_INPUT;
	FINAL_CARRERA_Conf.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(FIN_CARRERA_PORT, &FINAL_CARRERA_Conf);
}

/* ============  I2C  ===============  */
void MX_I2C1_Init(void){
  hi2c1.Instance = I2C1;

  hi2c1.Init.Timing = 0x2000090E; // 100 kHz típico @8MHz
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  if (HAL_I2C_Init(&hi2c1) != HAL_OK){
    Error_Handler();
  }
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = SCL_PIN|SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();

  }
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
  htim2.Init.Period = Timer_Period;
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
  if (htim->Instance == TIM2){

  }
}


void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);

    // ---- TICK BASE 1 ms ----

    // ---- 2s ----
    if(++cnt_100ms >= 100){
        cnt_100ms = 0;
        flag_100ms = (flag_100ms == 1)? 0 : 1;
    }

    // ---- 500 ms ----
    if(++cnt_500ms >= 500){
        cnt_500ms = 0;
        flag_500ms = (flag_500ms == 1)? 0 : 1;
    }

    // FLAG PARA LEER MATRIZ ----- 1s (1000 ms)
    if(++cnt_1s >= 1000){
        cnt_1s = 0;
        flag_1s  = (flag_1s == 1)? 0 : 1;
    }

    // DEBOUNCE TECLADO - CADA 50ms
    for(int f=0; f<CANT_FILAS; f++){
        for(int c=0; c<CANT_COLUMNAS; c++){
            if(deBounce_count[f][c] > 0)
                deBounce_count[f][c]--;
        }
    }
}

void Error_Handler(void){
	while(1);
}

void MX_USART1_UART_Init(void){
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  //huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  //huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

  return;
}
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if(huart->Instance == USART1){
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin =  TX_PIN | RX_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(UART_PORT, &GPIO_InitStruct);

        HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
}

//---------[ UART Data Reception Completion CallBackFunc. ]---------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	UART1_rxBuffer[DATA_LENGTH-1] = '\0'; //que el último caracter sea NULL para poder comprar strings después
    UART_flag = 1;
    HAL_UART_Receive_IT(&huart1, UART1_rxBuffer, DATA_LENGTH);
    return;
}

void USART1_IRQHandler(void){
    HAL_UART_IRQHandler(&huart1);
}
