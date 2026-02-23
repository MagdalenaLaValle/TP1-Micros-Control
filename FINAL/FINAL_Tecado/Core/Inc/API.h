#ifndef API_H
#define API_H

#include "LCD.h"
#include "UART.h"
#include "teclado.h"
#include "my_lib.h"
#include <string.h>

void Print_lcd(uint8_t row, const char *text);
void Print_UART(const char *text);
void Select(void);
void print_message(void);
void select_motor_flag(void);
void control_motor(void);

#endif
