#include "my_lib.h"
#include "FinalCarrera.h"


embolo_state detectar_embolo(void){
	embolo_state lectura = _Medio;
	GPIO_PinState final = GPIO_PIN_RESET, inicio = GPIO_PIN_RESET;
	final = HAL_GPIO_ReadPin(FIN_CARRERA_PORT, FINAL_PIN);
	inicio = HAL_GPIO_ReadPin(FIN_CARRERA_PORT, INICIO_PIN);

	if(final == GPIO_PIN_SET){
		lectura = _Final;
	}
	if(inicio == GPIO_PIN_SET){
		lectura = _Inicio;
	}
	return lectura;
}
