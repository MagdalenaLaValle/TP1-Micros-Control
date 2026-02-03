/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "my_lib.h"

/* Variables Globales --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern uint8_t flag;



/* Main ----------------------------------------------------------------------*/
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();

  // Iniciamos el Timer 2 con interrupciones habilitadas
  HAL_TIM_Base_Start_IT(&htim2);

  while (1)
  {
    if(flag == 1)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
    }
    else
    {HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
    }
  }
}

/* Callbacks de Interrupción -------------------------------------------------*/

// Esta función es llamada automáticamente por la HAL cuando el timer completa su ciclo



