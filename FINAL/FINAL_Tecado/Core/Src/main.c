#include "main.h"

/* Variables Globales --------------------------------------------------------*/
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
extern uint8_t flag_1ms, flag_2ms, flag_10ms, flag_1s, UART_flag;
//extern uint8_t selected_flag;
extern char selection;

int main(void){
  //FINAL DE CARRERA
  embolo_state embolo = _Final, last_embolo = _Final;

  //INICIALIZAR HARDWARE
  Hardware_Init();

  //INICIALIZAR I2C y UART
  Print_UART("Inicializando ");
  HAL_UART_Receive_IT(&huart1, UART1_rxBuffer, DATA_LENGTH);
  HAL_Delay(100);

  lcd_init();
  Print_lcd(0, "Inicializando");
  Print_lcd(1, "            ");

  //PROGRAMA
  while (1){
	  if(flag_1s == 1){
		  embolo = detectar_embolo();
		  if(last_embolo != embolo){
			last_embolo = embolo;
		  }
	  }

	 switch (last_embolo){
		 case _Inicio:
			 Print_lcd(0, "READY TO START");
			 Print_UART("READY TO START ");
			 Select(); //Recibe mensaje de UART o I2C
			 break;

		 case _Final:
			 Print_lcd(0, "FINAL");
			 Print_UART("FINAL");
			 selection = '#';
		  break;

		 case _Medio:
			  Print_lcd(0, "INYECTANDO");
			  Print_UART("INYECTANDO ");
			  break;
		}

	 print_message();
	 select_motor_flag();
	 control_motor();
  }
}
