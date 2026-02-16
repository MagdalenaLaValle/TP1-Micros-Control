/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Variables Globales --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern uint8_t flag_LEER;

extern uint8_t flag_100ms, flag_500ms, flag_1s;
char tecla_pulsada;

/* Main ----------------------------------------------------------------------*/
int main(void){
  key_state pressed_matrix[CANT_FILAS][CANT_COLUMNAS];
  init_matrix(pressed_matrix);

  char str_print[2], tecla, last_selection = '\0'; //es un char de dos elementos de forma que el elemnto final sea NULL y lcd_send_string lo lea bien
  str_print[1] = '\0';

  uint8_t *selected_flag, dead_flag = 0;
  selected_flag = &dead_flag; // originalmente, no hay ningún flag. Sólo es 0

  HAL_Init();
  MX_TIM2_Init();
  SystemClock_Config();
  MX_I2C1_Init();
  MX_GPIO_Init();
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);

  HAL_Delay(100);
  lcd_init();
  lcd_put_cur(0, 0);
  lcd_send_string("Inserte:");

  while (1){
	  //LECTURA DE LA MATRIZ
	  if (flag_1s==1){ //Con cada pulso del timer, leo la matriz
		leer_matriz(pressed_matrix);
		tecla = get_key_pressed(pressed_matrix);
		if(last_selection != tecla && tecla!='0'){
			last_selection = tecla;
		}
		//Si no hay ninguna tecla apretada, o no cambió el valor de la tecla, conservamos el mismo last_selection

	  }
	  switch (last_selection){
	  			case '1':
	  				lcd_put_cur(0, 9);
	  				lcd_send_string("       ");
	  				lcd_put_cur(0, 9);
	  				lcd_send_string("1s");
	  				selected_flag = &flag_1s;
	  				break;
	  			case '2':
	  				lcd_put_cur(0, 9);
	  				lcd_send_string("       ");
	  				lcd_put_cur(0, 9);
	  				lcd_send_string("500ms");
	  				selected_flag = &flag_500ms;
	  				break;
	  			case '3':
	  				lcd_put_cur(0, 9);
	  				lcd_send_string("       ");
	  				lcd_put_cur(0, 9);
	  				lcd_send_string("100ms");
	  				selected_flag = &flag_100ms;
	  				break;
	  			case 'A':
	  				lcd_put_cur(0, 9);
	  				lcd_send_string("       ");
	  				lcd_put_cur(0, 9);
	  				lcd_send_string("INVALID");
	  				selected_flag = &dead_flag;
	  				break;
	  }
	if(*selected_flag==1){
		HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_RESET);
	}

  }
}



