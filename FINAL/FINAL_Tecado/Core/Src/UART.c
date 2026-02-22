#include "UART.h"
#include <string.h>


extern UART_HandleTypeDef huart1;
//extern uint8_t UART1_rxBuffer[DATA_LENGTH];

void UART_Transmit_Message(char *message){
    HAL_UART_Transmit(&huart1, (uint8_t*)message,  strlen(message), 1000);
}

char Interpret_UART(void){
	char selection;

	if (strcmp((char*)UART1_rxBuffer, "1s   ") == 0) {
	   HAL_UART_Transmit(&huart1, UART1_rxBuffer, DATA_LENGTH, 100);
	   selection = '1';
	 }
	else if (strcmp((char*)UART1_rxBuffer, "500ms") == 0) {
	   HAL_UART_Transmit(&huart1, UART1_rxBuffer, DATA_LENGTH, 100);
	   selection = '2';
	 }
	else if (strcmp((char*)UART1_rxBuffer, "100ms") == 0) {
	   HAL_UART_Transmit(&huart1, UART1_rxBuffer, DATA_LENGTH, 100);
	   selection = '3';
	 }
	else{
		UART_Transmit_Message("VALOR INVALIDO");
		selection = 'A';
	}

	return selection;
}
