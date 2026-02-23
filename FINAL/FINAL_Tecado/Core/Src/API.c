#include "API.h"

extern UART_HandleTypeDef huart1;
extern uint8_t flag_1ms, flag_2ms, flag_10ms, flag_1s, UART_flag, dead_flag;
volatile uint8_t *selected_flag = &dead_flag;

char selection = '\0', last_printed = '\0', last_motor = '\0';

void Print_lcd(uint8_t row, const char *text){
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


void Print_UART(const char *text){
    static char last_msg[64] = "";   // guardamos último mensaje enviado

    if(strcmp(last_msg, text) != 0)
    {
        UART_Transmit_Message(text);
        UART_Transmit_Message("\r\n");   // opcional

        strncpy(last_msg, text, sizeof(last_msg) - 1);
        last_msg[sizeof(last_msg) - 1] = '\0';
    }
}

void Select(void){
	key_state pressed_matrix[CANT_FILAS][CANT_COLUMNAS];
	init_matrix(pressed_matrix);
	char tecla = '\0';
	if(UART_flag == 1){// Si recibe un mensaje por UART, prioriza UART, y sino lee el teclado
		 tecla = Interpret_UART();
		 UART_flag = 0;
	 }
	 else{
		 if(flag_1s == 1){ //cada 1s se lee la matriz
			 leer_matriz(pressed_matrix);
			 tecla = get_key_pressed(pressed_matrix);
		 }
	  }
	 if(selection != tecla && tecla!= 0){
		 selection = tecla;
	  }

}

void print_message(void){
	if(selection != last_printed){
		switch (selection){
			case '1'://T = 1ms   f = 1kHz
				Print_lcd(1, "1KHz");
				Print_UART("1KHz ");
				break;
			case '2':// T = 2ms	  f=500 Hz
				Print_lcd(1, "500 Hz");
				Print_UART("500 Hz ");
				break;
			case '3':// T = 10ms	f=
				Print_lcd(1, "100 Hz");
				Print_UART("100 Hz ");
				break;
			case '#':
				Print_lcd(1, "STOP");
				Print_UART("STOP ");
				break;
			case '\0':
				break;
			default:
				Print_lcd(1, "Invalid");
				Print_UART("Invalid Selection ");
				break;
		 }
		last_printed = selection;
	}
}


void select_motor_flag(void){
	if(selection != last_motor){
		switch (selection){
		   case '1':
			   selected_flag = &flag_1s;
			   break;
		   case '2':
			   selected_flag = &flag_2ms;
			   break;
		   case '3':
			   selected_flag = &flag_10ms;
			   break;
		   case '#':
			   selected_flag = &dead_flag;
				break;
		   case '\0':
				break;
		   default:
			   selected_flag = &dead_flag;
			   break;
		}
		last_motor = selection;
	}
}

void control_motor(void){
	if(*selected_flag==1){
	        HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_SET);
	}
	else{
	        HAL_GPIO_WritePin(MOTOR_PORT, MOTOR_PIN, GPIO_PIN_RESET);
	}
}
