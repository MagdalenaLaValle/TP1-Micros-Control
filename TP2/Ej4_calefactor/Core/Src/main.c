#include "main.h"

extern ADC_HandleTypeDef hadc1;
extern uint8_t sampling ;

static uint8_t adc_running = 0;

void my_timer_callback(){
	// ADC Start
	HAL_ADC_Start(&hadc1);
	adc_running = 1;
}

int main(void){
  Hw_Init(); //Llama a HAL_Init() y el resto de funciones para inicializar el hardware
  uint32_t counts = 100;
  float voltage = 0, temperature = 25;
  //sampling = ADC_Sampling_Period;

  setTimerCallback(my_timer_callback);

  HAL_GPIO_WritePin(TRANSISTOR_PORT, TRANSISTOR_PIN, TRANSISTOR_CLOSE);

  Hw_Start();

  while (1){
	  if (adc_running==1){
		  // Poll for 100us
		  HAL_ADC_PollForConversion(&hadc1, 100);
		  // Read Value
		  counts = HAL_ADC_GetValue(&hadc1);
		  // ADC Stop
		  HAL_ADC_Stop(&hadc1);
		  adc_running = 0;
		  // Voltage
		  voltage = counts * ADC_RES;
		  //Temperature (°C)
		  temperature = calcTemp_LM35(voltage);

		  if(temperature > (TEMP_TARGET + DELTA)){
			  HAL_GPIO_WritePin(TRANSISTOR_PORT, TRANSISTOR_PIN, TRANSISTOR_OPEN);
		  }
		  if (temperature < (TEMP_TARGET - DELTA)){
			  HAL_GPIO_WritePin(TRANSISTOR_PORT, TRANSISTOR_PIN, TRANSISTOR_CLOSE);
		  }
	  }
  }

}

