#ifndef TECLADO_H
#define TECLADO_H

#include "stm32f303xe.h"
#include "my_lib.h"
#include "stm32f3xx_hal_gpio.h"

//TIPOS DE DATOS

//VARIABLES

//FUNCIONES
void init_matrix(key_state matrix[CANT_FILAS][CANT_COLUMNAS]);
void leer_matriz(key_state matrix[CANT_FILAS][CANT_COLUMNAS]);
key_state SWICTH_Filtered(GPIO_TypeDef* GPIO_PORT, uint16_t GPIO_PIN, int f, int c);
char get_key_pressed(key_state matrix[CANT_FILAS][CANT_COLUMNAS]);

#endif /*TECLADO_H*/
