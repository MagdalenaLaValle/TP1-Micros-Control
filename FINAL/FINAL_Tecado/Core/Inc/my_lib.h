#ifndef MY_LIB_H
#define MY_LIB_H

#include "stm32f3xx_hal.h"

/*LISTA DE PINES EN EL SIGUIENTE LINK:
 * https://docs.google.com/spreadsheets/d/1kv1dg_1ysu0uWiti-7lAaGtYnNbYO3fvrg11gKiq1zs/edit?usp=sharing */

//MACROS TIMER
#define LED_TIMER TIM2
#define Core_CLK (float) 72000000
#define LED_PRESCALER 72 // 72MHz/1000 = 72KHz
//#define _LedPeriod(x) (((x * (Core_CLK/1000)) /LED_PRESCALER +1)-1) //Periodo en ms
#define Timer_Period 1000

//MACROS LED
#define MOTOR_PORT  GPIOB
#define MOTOR_PIN   GPIO_PIN_4 //PB5  D5

//MACROS TECLADO
#define KEY_PORT GPIOA
#define F1_PIN GPIO_PIN_5 	//PA5 	D13
#define F2_PIN GPIO_PIN_6 	//PA6 	D12
#define F3_PIN GPIO_PIN_7 	//PA7 	D11
#define F4_PIN GPIO_PIN_9 	//PA9 	D8
#define C1_PIN GPIO_PIN_8	//PA8  	D7
#define C2_PIN GPIO_PIN_10 	//PA10 	D2
#define C3_PIN GPIO_PIN_0 	//PA0  	A0
#define C4_PIN GPIO_PIN_1 	//PA1	A1
#define CANT_FILAS 4
#define CANT_COLUMNAS 4
#define DeBounce_Delay	5
#define leer_Delay 1000

//MACROS LCD
#define I2C_PORT GPIOB
#define SDA_PIN GPIO_PIN_9 	//D8
#define SCL_PIN GPIO_PIN_8 	//D7

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
void MX_I2C1_Init(void);
void TIM2_IRQHandler(void);
void Error_Handler(void);


#endif /* MY_LIB_H */
