/*
 Libreria para comunicacion con el sensor DHT11
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#define DH_PORT  GPIOA
#define DH_PIN   GPIO_PIN_10
#define COM_UP   GPIO_PIN_SET
#define COM_DOWN    GPIO_PIN_RESET

#define us 1e-6
#define ms 1e-3
#define SHAKE_MICRO (18*ms)
#define UNSHAKE_MICRO (80*us)
#define SHAKE_DHT11 (80*us)
#define UNSHAKE_DHT11 (80*us)

void setear_lectura();
void setear_escritura();
void Saludo_micro(int *Counter, uint8_t Pin_Com);
void Saludo_DHT11(int *Counter,uint8_t Pin_Com);
void leer_medicion(int *Counter);
int Cheksum(int vector_mediciones[4]);




#endif /* INC_DHT11_H_ */
