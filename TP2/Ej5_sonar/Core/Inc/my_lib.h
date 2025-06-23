//Para incializar hardware voy a necesitar todas las cfucniones de la librería HAL
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_i2c.h"
//MACROS
#define frec (float)100//se define la frecuencia del LED

#define LED_PORT GPIOA
#define LED_PIN GPIO_PIN_9
#define LED_OFF GPIO_PIN_RESET
#define LED_ON GPIO_PIN_SET

#define LED_TIMER TIM2
#define Core_CLK (float)16000000 //16MHz -- por las dudas casteo todo a float ; el coreCLK y el x en LedPeriod
#define LED_PRESCALER 1000 // 16MHz/1000 = 16kHz
#define _LedPeriod(x) ((((1/x)* Core_CLK) /(LED_PRESCALER -1))-1) //Esto va a hacer que el handler cuente cada 1ms

#define I2C_PORT GPIOB
#define SDA_PIN GPIO_PIN_9 // D14
#define SCL_PIN GPIO_PIN_8 // D15


//PROTOTIPOS DE FUNCIONES GLOBALES (PÚBLICAS)
uint8_t Hw_Init(void);
void SystemClock_Config(void);
void MX_I2C1_Init(void);
void TIM2_Config(void);
void MX_GPIO_Init(void);
void TIM2_IRQHandler(void);


void Error_Handler(void);
void transmitir(uint16_t DevAddress, uint8_t *pData, uint16_t Size);

