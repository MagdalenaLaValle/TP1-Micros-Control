#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "my_lib.h"

//Prototipos de funciones
embolo_state detectar_embolo(void);
key_state  EMBOLO_Filtered(GPIO_TypeDef* GPIO_PORT, uint16_t GPIO_PIN);

#endif
