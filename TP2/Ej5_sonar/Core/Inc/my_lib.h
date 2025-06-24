//Para incializar hardware voy a necesitar todas las cfucniones de la librería HAL
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_i2c.h"




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
void floatToString(float valor, char* str, int decimales);


void Error_Handler(void);

