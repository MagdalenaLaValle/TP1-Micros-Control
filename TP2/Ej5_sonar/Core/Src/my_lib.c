//INCLUDES
#include "my_lib.h"
#include "ULTRASONIC_SENSOR.h"

const uint8_t DELAY_1S = 0x8;

I2C_HandleTypeDef hi2c1 ;


//DEFINICIÓN DE FUNCIONES GLOBALES (PÚBLICAS)
uint8_t Hw_Init(void){
	HAL_Init();
	TIM2_Config();
	SystemClock_Config();
	MX_I2C1_Init();
	GPIO_Init();
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	TIM2_IRQHandler();
	return 1;
}


//DEFINICIÓN DE FUNCIONES PRIVADAS
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

void floatToString(float valor, char* str, int decimales) {
    int i = 0;

    // Obtener parte entera
    int parte_entera = (int)valor;

    // Obtener parte decimal
    float decimal = valor - (float)parte_entera;
    if (decimal < 0) decimal = -decimal;

    // Convertir parte entera a string (manual)
    char temp[10];
    int j = 0;
    if (parte_entera == 0) {
        temp[j++] = '0';
    } else {
        while (parte_entera > 0) {
            temp[j++] = '0' + (parte_entera % 10);
            parte_entera /= 10;
        }
    }

    // Revertir los dígitos
    for (int k = j - 1; k >= 0; k--) {
        str[i++] = temp[k];
    }

    // Agregar punto decimal
    str[i++] = '.';

    // Escalar parte decimal
    int escala = 1;
    for (int k = 0; k < decimales; k++) escala *= 10;
    int parte_decimal = (int)(decimal * escala + 0.5f);  // redondeo

    // Convertir parte decimal a string con ceros iniciales
    for (int k = decimales - 1; k >= 0; k--) {
        str[i + k] = '0' + (parte_decimal % 10);
        parte_decimal /= 10;
    }
    i += decimales;

    str[i] = '\0';  // Fin de string
}
