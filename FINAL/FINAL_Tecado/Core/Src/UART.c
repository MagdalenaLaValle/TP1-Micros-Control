#include "UART.h"
#include <string.h>


extern UART_HandleTypeDef huart1;
//extern uint8_t UART1_rxBuffer[DATA_LENGTH];

void UART_Transmit_Message(char *message){
    HAL_UART_Transmit(&huart1, (uint8_t*)message,  strlen(message), 1000);
}

char Interpret_UART(void){
	char selection;
	UART_Transmit_Message("\nValor ingresado:");
	HAL_UART_Transmit(&huart1, UART1_rxBuffer, DATA_LENGTH, 100);
	if (strcmp((char*)UART1_rxBuffer, "1ms..") == 0) {
	   selection = '1';
	 }
	else if (strcmp((char*)UART1_rxBuffer, "2ms..") == 0) {
	   selection = '2';
	 }
	else if (strcmp((char*)UART1_rxBuffer, "10ms") == 0) {
	   selection = '3';
	 }
	else if (strcmp((char*)UART1_rxBuffer, "STOPX") == 0) {
	   selection = '#';
	 }
	else{
		selection = 'A';
	}

	return selection;
}
