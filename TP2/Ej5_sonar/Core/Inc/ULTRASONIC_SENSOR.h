
#include "stm32f4xx_hal.h"


/* defines y macros ----------------------*/
#define m 1
#define s 1
#define us 1e6
#define cm 1e-2
#define V_Sonido 0.0343 //  cm/us
#define Distancia(t) (t*V_Sonido) // --> cm
#define M2cm(x) (x/cm)
#define cm2M(x) (x*cm)

/* Pines ---------------------------------*/

#define US_PORT GPIOA
#define ECHO_PIN GPIO_PIN_10
#define TRIGGER_PIN GPIO_PIN_9


#define TIMER TIM2
#define CORE_CLK  16000000 // 16 MHz
#define PRESCALER 1000
#define FREQ_US 1e6 // Frecuencia de muestreo 1 us
#define Period(x)	(-1+(CORE_CLK/(x*PRESCALER))/2)  // Period in [ms] non fractional


uint8_t Hw_Init(void);
void GPIO_Config(void); // GPIO Configuration
void TIM2_Config(void); // TIM2 Configuration
void TIM2_IRQHandler(void); // TIM2 IRQ Routine
#ifndef INC_ULTRASONIC_SENSOR_H_
#define INC_ULTRASONIC_SENSOR_H_



#endif /* INC_ULTRASONIC_SENSOR_H_ */
