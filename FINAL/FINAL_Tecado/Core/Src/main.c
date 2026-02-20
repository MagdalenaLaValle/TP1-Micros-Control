/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Variables Globales --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern uint8_t flag_LEER;

extern uint8_t flag_100ms, flag_500ms, flag_1s;
char tecla_pulsada;

/* Main ----------------------------------------------------------------------*/
int main(void){
  //LECTURA DEL TECLADO Y LCD
  key_state pressed_matrix[CANT_FILAS][CANT_COLUMNAS];
  char str_print[MAX_TECLAS + 1], tecla=' ', last_selection = '\0'; //es un char de dos elementos de forma que el elemnto final sea NULL y lcd_send_string lo lea bien
  str_print[MAX_TECLAS] = '\0'; //última posición del string es NULL.
  for(int i=0; i<MAX_TECLAS; i++){
	  str_print[i]=' '; //lleno el string con vacío
  }
  uint8_t position = 0; //posición en el buffer

  //MOTOR
  uint8_t *selected_flag, dead_flag = 0;
  selected_flag = &dead_flag; // originalmente, no hay ningún flag. Sólo es 0

  //FINAL DE CARRERA
  embolo_state embolo;
  movement_state move = _Not_Move;

  HAL_Init();
  MX_TIM2_Init();
  SystemClock_Config();
  MX_I2C1_Init();
  MX_GPIO_Init();
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  init_matrix(pressed_matrix);

  HAL_Delay(100);
  lcd_init();
  lcd_put_cur(0, 0);
  lcd_send_string("Inserte:");
  lcd_put_cur(0, 9);
  lcd_send_string("       ");

  while (1){
	 if (flag_1s==1){ //Con cada pulso del timer, leo la matriz
		embolo = detectar_embolo();
		leer_matriz(pressed_matrix);
		tecla = get_key_pressed(pressed_matrix);
		if(last_selection != tecla && tecla!=0){
			last_selection = tecla;
		}

		//Si no hay ninguna tecla apretada, o no cambió el valor de la tecla, conservamos el mismo last_selection
		/*if(tecla!= ' '){
			if(position < MAX_TECLAS){
			str_print[position] = tecla;
			tecla = ' '; //limpio tecla hasta que se ingrese otro valor
			position++;
			}
			else{
				lcd_put_cur(1,0);
				lcd_send_string("              ");
				lcd_put_cur(1,0);
				lcd_send_string("ERROR: max 3 num");
			}
		}*/

	}
	//lcd_put_cur(0, 9);
	//lcd_send_string(str_print);


	 if(embolo == _Final){
		 move = _Not_Move;
		 selected_flag = &dead_flag;
		 lcd_put_cur(1,0);
		lcd_send_string("       ");
		lcd_put_cur(1,0);
		lcd_send_string("FINAL");
	 }
	 else{
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
	 }

	if(*selected_flag==1){
		HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_RESET);
	}

  }
}



