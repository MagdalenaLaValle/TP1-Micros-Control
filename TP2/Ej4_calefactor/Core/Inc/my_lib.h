//Para incializar hardware voy a necesitar todas las cfucniones de la librería HAL
#include "stm32f4xx_hal.h"
#include "stm32f401xe.h"
#include "stm32f4xx_hal_tim.h"

//MACROS
#define ADC_Sampling_Period ((uint32_t) 1000) // 10 [ms]
#define frec (float)1000//se define la frecuencia del LED

#define TRANSISTOR_PORT GPIOA
#define TRANSISTOR_PIN GPIO_PIN_9 // pin 9 - D8
#define TRANSISTOR_OPEN GPIO_PIN_RESET
#define TRANSISTOR_CLOSE GPIO_PIN_SET

#define DELTA 5
#define TEMP_TARGET 25

#define Core_CLK (float)16000000 //16MHz -- por las dudas casteo todo a float ; el coreCLK y el x en LedPeriod
#define TIM_PRESCALER 1000 // 16MHz/1000 = 16kHz
#define _CalcPeriod(x) ((((1/x)* Core_CLK) /(TIM_PRESCALER -1))-1) //Esto va a hacer que el handler cuente cada 1ms

#define COUNT_MUESTREO 2 //para muestrear cada 1s
#define ADC_RES (3.3/4096)

#define _Celsius(temp) (temp - 273)
#define _Kelvin(temp) (temp + 273)

//TIPOS DE DATOS
typedef enum{
	_YES,
	_NO
}read_now_t;

//PROTOTIPOS DE FUNCIONES GLOBALES (PÚBLICAS)
uint8_t Hw_Init(void);
void Hw_Start(void);
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_TIM2_Init(void);
void MX_ADC1_Init(void);
void TIM2_IRQHandler(void);
void Error_Handler(void);
void setTimerCallback(void (*callback_fn)());
//PROTOTIPOS DE FUNCIONES PRIVADAS
