#ifndef TECLADO_H
#define TECLADO_H

#include "stm32f303xe.h"
#include "my_lib.h"
#include "stm32f3xx_hal_gpio.h"

//TIPOS DE DATOS

//VARIABLES
//int filas[FILAS] = {F1, F2, F3, F4};
//int cols[COLUMNAS] = {C1, C2, C3, C4};
/*char teclado[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};*/

//FUNCIONES
/*matrix_state check_matrix(); //chequea que sólo se esté pulsando un caracter
char leer_matriz(); //lee la matriz y devuelve el caracter pulsado
key_state leer_fila(int num_fila);*/
int leer_A();
key_state  SWICTH_Filtered(GPIO_TypeDef* GPIO_PORT, uint16_t GPIO_PIN);

#endif /*TECLADO_H*/
