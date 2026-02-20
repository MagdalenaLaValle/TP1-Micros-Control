#include "teclado.h"

//Variables
uint8_t flag_matrix = 0;
const char keymap[CANT_FILAS][CANT_COLUMNAS] = {
	{'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
/*Cada letra va con comillas simples porque cada una es un char de 8bit.
 * Si el pusiera comillas dobles sería un arrelgo de chars*/

extern volatile uint8_t deBounce_count[CANT_FILAS][CANT_COLUMNAS];
uint16_t filas[CANT_FILAS] = {F1_PIN, F2_PIN, F3_PIN, F4_PIN};
uint16_t cols[CANT_COLUMNAS] = {C1_PIN, C2_PIN, C3_PIN, C4_PIN};


//FUNCIONES
void init_matrix(key_state matrix[CANT_FILAS][CANT_COLUMNAS]){
    for(int f = 0; f < CANT_FILAS; f++){
        for(int c = 0; c < CANT_COLUMNAS; c++){
            matrix[f][c] = _Non_Pressed;
        }
    }
}

key_state SWICTH_Filtered(GPIO_TypeDef* GPIO_PORT, uint16_t GPIO_PIN, int f, int c){
    static key_state last_state[CANT_FILAS][CANT_COLUMNAS] = {{_Non_Pressed}};
    key_state actual_state;

    actual_state = (HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN)==GPIO_PIN_SET)
                   ? _Pressed : _Non_Pressed;

    if((actual_state != last_state[f][c]) &&
       (deBounce_count[f][c]==0))
    {
        deBounce_count[f][c] = DeBounce_Delay;
        last_state[f][c] = actual_state;
    }
    else if((deBounce_count[f][c]==0) &&
            (last_state[f][c]==actual_state))
    {
        return actual_state;
    }

    return _Non_Pressed;
}


void leer_matriz(key_state matrix[CANT_FILAS][CANT_COLUMNAS]){
    for(int f=0; f<CANT_FILAS; f++){
        HAL_GPIO_WritePin(KEY_PORT, filas[f], GPIO_PIN_SET);
        for(int c=0; c<CANT_COLUMNAS; c++){
            matrix[f][c] = SWICTH_Filtered(KEY_PORT, cols[c], f, c);
        }
        HAL_GPIO_WritePin(KEY_PORT, filas[f], GPIO_PIN_RESET);
    }
}

char get_key_pressed(key_state matrix[CANT_FILAS][CANT_COLUMNAS]){
    char detected = 0;

    for(int f=0; f<CANT_FILAS; f++){
        for(int c=0; c<CANT_COLUMNAS; c++){
            if(matrix[f][c] == _Pressed){
                if(detected != 0)
                    return ' '; // más de una tecla
                detected = keymap[f][c];
            }
        }
    }
    return detected;
}


