#include "main.h"
#include "my_lib.h"
#include "LCD.h"

extern I2C_HandleTypeDef hi2c1;

int main(void){
  Hw_Init();

  HAL_Delay(100);
  lcd_init();

  // Display example
  lcd_put_cur(0, 0);
  lcd_send_string("Distancia:");
  lcd_put_cur(1, 0);
  lcd_send_string("numerito");

  while (1)
  {
      // Your loop code
  }
}
