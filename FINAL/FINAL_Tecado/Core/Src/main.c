/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Variables Globales --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern uint8_t flag_LEER, flag_BLINK;

char tecla_pulsada;

/* Main ----------------------------------------------------------------------*/
int main(void){
  int pressed = 0;
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();
  HAL_TIM_Base_Start_IT(&htim2);

  while (1){
	  if (flag_LEER==1){ //Con cada pulso del timer, leo la matriz
		pressed = leer_A();
		if(pressed == 1){//pressed queda establecido en leer_A
			//if(flag_BLINK==1) HAL_GPIO_WritePin(LED_PORT, LED_PIN, LED_ON);
			//else HAL_GPIO_WritePin(LED_PORT, LED_PIN, LED_OFF);
			/*HAL_Delay(100);
			//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
			//HAL_Delay(100);*/
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);//se mantiene prendido por el tiempo que mantenga apretado
		}
		else{
			HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
		}
	  }
	  //HAL_GPIO_WritePin(KEY_PORT, F1_PIN, GPIO_PIN_SET);
  }
}



