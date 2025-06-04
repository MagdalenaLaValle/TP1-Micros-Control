#include "main.h"
#include "my_lib.h"

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

  Hw_Start();

  while (1){
	  if (adc_running==1){
	  //if (sampling == 0){
		  // Poll for 100us
		  HAL_ADC_PollForConversion(&hadc1, 100);
		  // Read Value
		  counts = HAL_ADC_GetValue(&hadc1);
		  // ADC Stop
		  HAL_ADC_Stop(&hadc1);
		  adc_running = 0;
		  // Voltage
		  voltage = counts * ADC_RES;

		  temperature = calcTemp(voltage);
		  if(temperature < TEMP_A){
			  HAL_GPIO_WritePin(LED_PORT, LED_A_PIN, LED_OFF);
			  HAL_GPIO_WritePin(LED_PORT, LED_B_PIN, LED_OFF);
			  HAL_GPIO_WritePin(LED_PORT, LED_C_PIN, LED_OFF);
			  HAL_GPIO_WritePin(LED_PORT, LED_D_PIN, LED_OFF);
		  }
		  if((temperature >= TEMP_A) && temperature < TEMP_B){
			  HAL_GPIO_WritePin(LED_PORT, LED_A_PIN, LED_ON);
			  HAL_GPIO_WritePin(LED_PORT, LED_B_PIN, LED_OFF);
			  HAL_GPIO_WritePin(LED_PORT, LED_C_PIN, LED_OFF);
			  HAL_GPIO_WritePin(LED_PORT, LED_D_PIN, LED_OFF);
		  }
		  if((temperature >= TEMP_B) && (temperature < TEMP_C)){
			  HAL_GPIO_WritePin(LED_PORT, LED_A_PIN, LED_ON);
			  HAL_GPIO_WritePin(LED_PORT, LED_B_PIN, LED_ON);
			  HAL_GPIO_WritePin(LED_PORT, LED_C_PIN, LED_OFF);
			  HAL_GPIO_WritePin(LED_PORT, LED_D_PIN, LED_OFF);
		  }
		  if((temperature >= TEMP_C) && (temperature < TEMP_D)){
			  HAL_GPIO_WritePin(LED_PORT, LED_A_PIN, LED_ON);
			  HAL_GPIO_WritePin(LED_PORT, LED_B_PIN, LED_ON);
			  HAL_GPIO_WritePin(LED_PORT, LED_C_PIN, LED_ON);
			  HAL_GPIO_WritePin(LED_PORT, LED_D_PIN, LED_OFF);
		  }
		  if(temperature >= TEMP_D){
			  HAL_GPIO_WritePin(LED_PORT, LED_A_PIN, LED_ON);
			  HAL_GPIO_WritePin(LED_PORT, LED_B_PIN, LED_ON);
			  HAL_GPIO_WritePin(LED_PORT, LED_C_PIN, LED_ON);
			  HAL_GPIO_WritePin(LED_PORT, LED_D_PIN, LED_ON);
		  }
	  }
  }

}

