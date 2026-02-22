#ifndef UART_H
#define UART_H

/* STM32 UART4 Address
 * 0x4000 4C00 - 0x4000 4FFF
 * */

#include "my_lib.h"
#include "main.h"

extern uint8_t UART1_rxBuffer[DATA_LENGTH];

//Prototipos de funciones
void UART_Transmit_Message(char *message);
char Interpret_UART(void);


#endif
