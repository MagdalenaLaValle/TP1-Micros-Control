
#include "stm32f4xx_hal.h"


/* defines y macros ----------------------*/
#define m 1
#define s 1
#define us 1e6
#define cm 1e-2
#define V_Sonido 0.0343 //  cm/us
#define Distancia(t) ((t) * V_Sonido/2) // --> cm
#define Max_t 200 // cantidad de pulsos maxima --> se da a 10 cm aprox

#define M2cm(x) (x/cm)
#define cm2M(x) (x*cm)


/* Pines ---------------------------------*/
#define US_PORT GPIOA
#define ECHO_PIN GPIO_PIN_8
#define TRIGGER_PIN GPIO_PIN_9
#define TIEMPO_TOTAL 200 //us
#define TIEMPO_TRIGGER 11



//Macros de timer
#define TIMER TIM2
#define CORE_CLK  16000000 // 16 MHz
#define PRESCALER (16 - 1)     // 16 MHz / 16 = 1 MHz -> 1 µs por cuenta
#define PERIOD    (1 - 1)      // 1 µs de período -> cuenta hasta 1



void SystemClock_Config(void);
void GPIO_Init(void);
void TIM2_Config(void);
void TIM2_IRQHandler(void);
void Error_Handler(void);


#ifndef INC_ULTRASONIC_SENSOR_H_
#define INC_ULTRASONIC_SENSOR_H_



#endif /* INC_ULTRASONIC_SENSOR_H_ */
