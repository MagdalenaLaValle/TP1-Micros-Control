/* Includes ------------------------------*/
#include "stm32f4xx_hal.h"

/* Macros --------------------------------*/
#define LED_PORT  GPIOA
#define LED_PIN   GPIO_PIN_10
#define LED_OFF   GPIO_PIN_RESET
#define LED_ON    GPIO_PIN_SET

#define TIMER TIM2
#define CORE_CLK  16000000 // 16 MHz
#define PRESCALER 1000
#define LED_FREQUENCY 1000
#define Period(x)	(-1+(CORE_CLK/(x*PRESCALER))/2)  // Period in [ms] non fractional


/* Variable Types ------------------------*/

/* Public Function Prototypes ------------*/
uint8_t Hw_Init(void); // Hardware Configuration
void SystemClock_Config(void); // CLK Configuration
void GPIO_Config(void); // GPIO Configuration
void TIM2_Config(void); // TIM2 Configuration
void TIM2_IRQHandler(void); // TIM2 IRQ Routine

/* Private Function Prototypes ------------*/
