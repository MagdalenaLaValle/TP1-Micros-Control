/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Variables Globales --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern uint8_t flag_LEER;

extern uint8_t flag_10ms, flag_100ms, flag_1s;
char tecla_pulsada;

/* Main ----------------------------------------------------------------------*/
int main(void){
  key_state pressed_matrix[CANT_FILAS][CANT_COLUMNAS];
  init_matrix(pressed_matrix);

  char tecla = 0;

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();
  HAL_TIM_Base_Start_IT(&htim2);
  while (1){
	  if (flag_1s==1){ //Con cada pulso del timer, leo la matriz
		leer_matriz(pressed_matrix);
		tecla = get_key_pressed(pressed_matrix);

		/*//FILA 1 - COL 1
		if(pressed_matrix[0][1] == _Pressed){
			HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_10, GPIO_PIN_SET);
		}
		else{
			HAL_GPIO_WritePin(LED_PORT, GPIO_PIN_10, GPIO_PIN_RESET);
		}*/
	  }

  }
}



