#ifndef MY_LIB_H
#define MY_LIB_H

#include "stm32f3xx_hal.h"

//MACROS TIMER
#define LED_TIMER TIM2
#define Core_CLK (float) 72000000
#define LED_PRESCALER 72 // 72MHz/1000 = 72KHz
#define _LedPeriod(x) (((x * (Core_CLK/1000)) /LED_PRESCALER +1)-1) //Periodo en ms

//MACROS LED
#define LED_PORT  GPIOA
#define LED_PIN   GPIO_PIN_10
#define LED_OFF   GPIO_PIN_RESET
#define LED_ON    GPIO_PIN_SET

//MACROS TECLADO
#define KEY_PORT GPIOB
#define F1_PIN GPIO_PIN_8 //PB8 D15
#define F2_PIN GPIO_PIN_9 //PB9 D14
#define F3_PIN GPIO_PIN_10 //PB10 D6
#define F4_PIN GPIO_PIN_0 //PB0 A3
#define C1_PIN GPIO_PIN_3//PB3 D3
#define C2_PIN GPIO_PIN_4 //PB4 D5
#define C3_PIN GPIO_PIN_5 //PB5 D4
#define C4_PIN GPIO_PIN_6 //PB6 D10
#define FILAS 4
#define COLUMNAS 4
#define DeBounce_Delay	5

//TIPOS DE DATOS
typedef enum{
	_Pressed,
	_Non_Pressed,
}key_state;

typedef enum{
	_Ok,
	_Multiple_Keys,
	_No_Keys,
}matrix_state;

// Handles externos
extern TIM_HandleTypeDef htim2;

// Prototipos
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_TIM2_Init(void);

#endif /* MY_LIB_H */
