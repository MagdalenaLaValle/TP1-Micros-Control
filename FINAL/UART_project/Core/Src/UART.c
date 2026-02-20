#include "UART.h"
#include <string.h>


extern UART_HandleTypeDef huart1;

void UART_Transmit_Message(void){
	char message[] = "hello world\r\n";
	HAL_UART_Transmit(&huart1, (uint8_t*)message, strlen(message), 1000);
	return;
}
