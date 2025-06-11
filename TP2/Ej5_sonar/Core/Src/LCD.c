/*NO OLVDARSE DE PONER EN EL HwInit():
 MX_I2C1_Init(); */

#include "LCD.h"
#include "my_lib.h"
#include "stm32f4xx_hal_i2c.h"

//Variables Globales
I2C_HandleTypeDef hi2c1;


//Funciones
void MX_I2C1_Init(void){
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
}


void printHumValue(void);
void show_char(uint8_t *pData,  uint16_t Size){
	  /* @brief  Transmits in master mode an amount of data in blocking mode.
	  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
	  *                the configuration information for the specified I2C.
	  * @param  DevAddress Target device address: The device 7 bits address value
	  *         in datasheet must be shifted to the left before calling the interface
	  * @param  pData Pointer to data buffer
	  * @param  Size Amount of data to be sent
	  * @param  Timeout Timeout duration
	  * @retval HAL status
	  */
	//HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
	HAL_I2C_Master_Transmit(&hi2c1, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)

}
/*para mostrar un caracter necesito: mandarle el binario en ASCII (fijarse en datasheet del LCD); en qué cuadrante lo mando; bit de start y de end*/
void clean_display(void);
