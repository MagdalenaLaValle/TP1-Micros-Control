//Para incializar hardware voy a necesitar todas las cfucniones de la librería HAL
#include "stm32f4xx_hal.h"
#include "stm32f401xe.h"
#include "stm32f4xx_hal_tim.h"

//MACROS
#define ADC_Sampling_Period ((uint32_t) 1000) // 10 [ms]
#define frec (float)1000//se define la frecuencia del LED

#define LED_PORT GPIOA
#define LED_A_PIN GPIO_PIN_7 // pin 7 - D11
#define LED_B_PIN GPIO_PIN_8// pin - D7
#define LED_C_PIN GPIO_PIN_9 // pin 9 - D8
#define LED_D_PIN GPIO_PIN_10 // pin 10 - D2
#define LED_OFF GPIO_PIN_RESET
#define LED_ON GPIO_PIN_SET

#define TEMP_A 20
#define TEMP_B 22
#define TEMP_C 25
#define TEMP_D 28

#define Core_CLK (float)16000000 //16MHz -- por las dudas casteo todo a float ; el coreCLK y el x en LedPeriod
#define TIM_PRESCALER 1000 // 16MHz/1000 = 16kHz
#define _CalcPeriod(x) ((((1/x)* Core_CLK) /(TIM_PRESCALER -1))-1) //Esto va a hacer que el handler cuente cada 1ms

#define COUNT_MUESTREO 2 //para muestrear cada 1s
#define ADC_RES (3.3/4096)

#define TENSION 3.3
#define R1 10000
#define R0 10000
#define BETA 3950
#define T0 296,5
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
float calcTemp(float voltage);
void Error_Handler(void);
void setTimerCallback(void (*callback_fn)());
//PROTOTIPOS DE FUNCIONES PRIVADAS
