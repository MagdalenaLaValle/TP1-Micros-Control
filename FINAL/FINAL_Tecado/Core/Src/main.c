/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Variables Globales --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;

extern uint8_t flag_100ms, flag_500ms, flag_1s, UART_flag;

char tecla_pulsada;
void Print_lcd(uint8_t row, const char *text);
void Print_UART(const char *text);

int main(void){
  //LECTURA DEL TECLADO Y LCD
  key_state pressed_matrix[CANT_FILAS][CANT_COLUMNAS];
  char tecla, last_selection = '\0'; //es un char de dos elementos de forma que el elemnto final sea NULL y lcd_send_string lo lea bien
  init_matrix(pressed_matrix);

  //MOTOR
  uint8_t *selected_flag, dead_flag = 0;
  selected_flag = &dead_flag; // originalmente, no hay ningún flag. Sólo es 0

  //FINAL DE CARRERA
  embolo_state embolo = _Inicio, last_embolo = _Inicio;

  Hardware_Init();

  Print_UART("Inicializando ");
  HAL_UART_Receive_IT(&huart1, UART1_rxBuffer, DATA_LENGTH);
  HAL_Delay(100);

  lcd_init();
  Print_lcd(0, "Inicializando");
  while (1){
	  if(flag_1s == 1){
		  embolo = detectar_embolo();
		  if(last_embolo != embolo && embolo!= _Medio){
			last_embolo = embolo;
		  }
	  }

	  switch (last_embolo){
		  	 case _Inicio:
		  		 Print_lcd(0, "READY TO START");
		  		 Print_UART("READY TO START ");
			  if(UART_flag == 1){
				 tecla = Interpret_UART();
				 UART_flag = 0;
			  }

			  else{
				  leer_matriz(pressed_matrix);
				  tecla = get_key_pressed(pressed_matrix);
			  }

			  if(last_selection != tecla && tecla!= 0){
				  last_selection = tecla;
			  }
			  break;

		  	 case _Final:
		  		 Print_lcd(0, "FINAL");
		  		 Print_UART("FINAL");
		  		 selected_flag = &dead_flag;
			  break;

		  	 case _Medio:
		  		  Print_lcd(0, "Inyectando");
		  		  Print_UART("INYECTANDO ");
				  break;
	  }

     switch (last_selection){
            case '1':
            	Print_lcd(1, "1s");
                selected_flag = &flag_1s;
                break;
            case '2':
            	Print_lcd(1, "500 ms");
                selected_flag = &flag_500ms;
                break;
            case '3':
            	Print_lcd(1, "100 ms");
                selected_flag = &flag_100ms;
                break;
            default:
            	Print_lcd(1, "Invalid");
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


void Print_lcd(uint8_t row, const char *text)
{
    static char last0[17] = "";
    static char last1[17] = "";

    char *last = (row == 0) ? last0 : last1;

    if(strcmp(last, text) != 0)
    {
        lcd_put_cur(row, 0);
        lcd_send_string("                ");
        lcd_put_cur(row, 0);
        lcd_send_string(text);
        strncpy(last, text, 16);
        last[16] = '\0';
    }
}


void Print_UART(const char *text)
{
    static char last_msg[64] = "";   // guardamos último mensaje enviado

    if(strcmp(last_msg, text) != 0)
    {
        UART_Transmit_Message(text);
        UART_Transmit_Message("\r\n");   // opcional

        strncpy(last_msg, text, sizeof(last_msg) - 1);
        last_msg[sizeof(last_msg) - 1] = '\0';
    }
}
