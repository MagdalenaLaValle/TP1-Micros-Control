#include "main.h"
#include "my_lib.h"


int main(void){
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  while (1)
  {

  }

}

