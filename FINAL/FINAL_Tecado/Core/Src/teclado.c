#include "teclado.h"

//Variables
uint8_t flag_matrix = 0;
extern uint8_t deBounce_count;

//FUNCIONES

key_state  SWICTH_Filtered(GPIO_TypeDef* GPIO_PORT, uint16_t GPIO_PIN){

	static key_state actual_state = _Non_Pressed, last_state = _Non_Pressed;

	/* Read Pin */
	actual_state = (HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN)== GPIO_PIN_SET)?	_Pressed: _Non_Pressed;

	/* Check if There is a State Change */
	if((actual_state != last_state) && (deBounce_count==0)){
		/* Delay Start */
		deBounce_count = DeBounce_Delay;
		/* Save previous state */
		last_state = actual_state;
	}
	else{
		/* Delay Ended */
		if((deBounce_count==0) && (last_state==actual_state)){
			/* If its maintain equal after DeBounce_Delay */
			return(actual_state);
		}
	}
	return(_Non_Pressed);
}
int leer_A(){
	key_state result;
	int pressed = 0;
	HAL_GPIO_WritePin(KEY_PORT, F1_PIN, GPIO_PIN_SET);//prendo la fila
	//result = (HAL_GPIO_ReadPin(KEY_PORT, C2_PIN) == GPIO_PIN_SET)? 1 : 0; //leo la columna
	result = SWICTH_Filtered(KEY_PORT, C2_PIN);
	pressed = (result == _Pressed) ? 1 : 0; // si la tecla está pulsada pressed = 1
	HAL_GPIO_WritePin(KEY_PORT, F1_PIN, GPIO_PIN_RESET);//cuando termino apago la fila
	return pressed;
}
