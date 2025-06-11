#ifndef SRC_LED_DISPLAY_H_
#define SRC_LED_DISPLAY_H_

#define I2C_PORT GPIOB
#define SDA_PIN GPIO_PIN_7
#define SCL_PIN GPIO_PIN_6

#define 0x43 //Byte para indicar que vamos a escribir a un determinado address

//Funciones
void MX_I2C1_Init(void);
void printHumValue(void);
void show_char(uint8_t *pData,  uint16_t Size);
void clean_display(void);

#endif
