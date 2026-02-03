/*
 Libreria para comunicacion con el sensor DHT11
 */
#include "stm32f4xx_hal.h"

#define DHT11_PORT  GPIOA
#define DHT11_PIN   GPIO_PIN_10
#define PIN_ON   GPIO_PIN_SET
#define PIN_OFF    GPIO_PIN_RESET
#define SIZE_MESSAGE 8

#define us 1e-6
#define ms 1e-3
#define SHAKE_MICRO (18*ms)
#define UNSHAKE_MICRO (80*us)
#define SHAKE_DHT11 (80*us)
#define UNSHAKE_DHT11 (80*us)

void configurar_DHT11(void);
void setear_lectura();
void setear_escritura();
void Saludo_micro(int *Counter);
int Saludo_DHT11(int *Counter);
void leer_medicion(int *Counter);
int Cheksum(int vector_mediciones[4]);



#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#endif /* INC_DHT11_H_ */
