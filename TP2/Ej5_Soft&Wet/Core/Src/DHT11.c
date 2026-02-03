/*
 * DHT11.c
 *
 *  Created on: Jun 10, 2025
 *      Author: Juan Bautista
 */
#include "DHT11.h"
#include <math.h>

extern uint8_t Counter;
void configurar_DHT11(){
	GPIO_InitTypeDef DHT11_Pin_Config = {0};

	/* GPIO Port Hardware Enable */
	// --> Hardware
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* LED Initial State : OFF */
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, PIN_OFF);

	/* GPIO Pin Features Load */
	// --> Software
	DHT11_Pin_Config.Pin = DHT11_PIN;
	DHT11_Pin_Config.Mode = GPIO_MODE_OUTPUT_PP;
	DHT11_Pin_Config.Pull = GPIO_NOPULL;
	DHT11_Pin_Config.Speed = GPIO_SPEED_FREQ_LOW;

	/* GPIO Pin Hardware Configuration */
	// --> Hardware
	HAL_GPIO_Init(DHT11_PORT, &DHT11_Pin_Config);

	return;
}
void setear_escritura(){
	GPIO_InitTypeDef DH_Pin_Conf = {0};
	HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, PIN_OFF);

	/* GPIO Pin Features Load */
	// --> Software
	DH_Pin_Conf.Pin = DHT11_PIN;
	DH_Pin_Conf.Mode = GPIO_MODE_OUTPUT_PP;
	DH_Pin_Conf.Pull = GPIO_NOPULL;
	DH_Pin_Conf.Speed = GPIO_SPEED_FREQ_LOW;

	/* GPIO Pin Hardware Configuration */
	// --> Hardware
	HAL_GPIO_Init(DHT11_PORT, &DH_Pin_Conf);

	return;
}
void setear_lectura(){
	GPIO_InitTypeDef DH_Pin_Conf = {0};
	/* GPIO Pin Features Load */
	// --> Software
	DH_Pin_Conf.Pin = DHT11_PIN;
	DH_Pin_Conf.Mode = GPIO_MODE_INPUT;
	DH_Pin_Conf.Pull = GPIO_NOPULL;
	DH_Pin_Conf.Speed = GPIO_SPEED_FREQ_LOW;

	/* GPIO Pin Hardware Configuration */
	// --> Hardware
	HAL_GPIO_Init(DHT11_PORT, &DH_Pin_Conf);

	return;
}

int Bin2Int(int vec_bin[SIZE_MESSAGE]){
	int a = 0;
	for(int index = 0;index < SIZE_MESSAGE;index ++){
		a += vec_bin[index]*pow(2,index);
	}
	return a;
}
int leer_medicion(){
	int actual= (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)==PIN_ON) ? 0:1 ;
	counter =



}
/*
int leer_medicion(){
	int medicion_actual;
	int vec_bin[SIZE_MESSAGE];
	int bit_actual = 0, bit_prev = 0;


	bit_actual = (HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN)==SWITCH_ON)?	Pressed:Non_Pressed;

	if(prev!=actual) counter = DeBounce_Delay;
	else{

		if(counter==0) res = Pressed;
		else res = Non_Pressed;
	}


	prev = actual;


		// OPCION PARA DESAPROBAR
		// for(uint32_t i=0; i<1000; i++);

		// OTRA FORMA DE DESAPROBAR
		// counter = 10
		// while(counter!=0);

	return(res);
}
*/
