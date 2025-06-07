#include "LM35.h"

float calcTemp_LM35(float voltage){
	float temp;
	temp = voltage * PENDIENTE;
	return temp;
}


