#include "main.h"
#include "my_lib.h"
#include "LCD.h"
#include "ULTRASONIC_SENSOR.h"
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;
extern uint8_t flag;
extern float distancia_medida;


uint32_t max_tim = 0;

int main(void){
  Hw_Init();
  char buffer[20];
  HAL_Delay(100);
  lcd_init();
  lcd_put_cur(0, 0);
  lcd_send_string("Distancia:");
  while (1){
	  if(flag == 1){
		  lcd_put_cur(1, 0);
		  lcd_send_string("            "); // limpia fila
		  floatToString(distancia_medida, buffer, 2);
		  lcd_put_cur(1, 0);
		  lcd_send_string(buffer);
		  HAL_GPIO_WritePin(US_PORT, TRIGGER_PIN, GPIO_PIN_SET );
		  flag = 0;

	  }
	  HAL_GPIO_WritePin(US_PORT, TRIGGER_PIN, GPIO_PIN_SET );

  }

}


