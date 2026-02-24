#include "my_lib.h"
#include "FinalCarrera.h"

embolo_state detectar_embolo(void){
	embolo_state lectura = _Medio;
	if(HAL_GPIO_ReadPin(FIN_CARRERA_PORT, FINAL_PIN) == GPIO_PIN_SET){
		lectura = _Final;
	}
	if(HAL_GPIO_ReadPin(FIN_CARRERA_PORT, INICIO_PIN) == GPIO_PIN_SET){
		lectura = _Inicio;
	}
	return lectura;
}
