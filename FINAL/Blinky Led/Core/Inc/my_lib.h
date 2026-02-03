#ifndef MY_LIB_H
#define MY_LIB_H

#include "stm32f3xx_hal.h"

//MACROS


#define LED_TIMER TIM2
#define Core_CLK (float) 72000000
#define LED_PRESCALER 72 // 72MHz/1000 = 72KHz
#define _LedPeriod(x) (((x * (Core_CLK/1000)) /LED_PRESCALER +1)-1) //Periodo en ms
// Handles externos
extern TIM_HandleTypeDef htim2;

// Prototipos
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_TIM2_Init(void);

#endif /* MY_LIB_H */
