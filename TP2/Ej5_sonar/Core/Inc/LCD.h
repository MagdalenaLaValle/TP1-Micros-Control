#ifndef INC_LCD_H_
#define INC_LCD_H_

//Macros
#define SLAVE_ADDRESS_LCD  0x4E

//Funciones
void lcd_send_cmd(uint8_t cmd);
void lcd_send_data(uint8_t data);
void lcd_init(void);
void lcd_send_string(char *str);
void lcd_put_cur(uint8_t row, uint8_t col);

#endif
