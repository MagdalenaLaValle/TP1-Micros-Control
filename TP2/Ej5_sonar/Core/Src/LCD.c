#include "my_lib.h"
#include "LCD.h"


const uint8_t ROW_16[] = {0x00, 0x40, 0x10, 0x50};

static void lcd_write_data(Lcd_HandleTypeDef * lcd, uint8_t data);
static void lcd_write_command(Lcd_HandleTypeDef * lcd, uint8_t command);
static void lcd_write(Lcd_HandleTypeDef * lcd, uint8_t data, uint8_t len);

//Inicializar LCD without cursor
void Lcd_init(Lcd_HandleTypeDef * lcd){
	lcd_write_command(lcd, FUNCTION_SET | OPT_DL | OPT_N);
	lcd_write_command(lcd, CLEAR_DISPLAY); // Clear screen
	lcd_write_command(lcd, DISPLAY_ON_OFF_CONTROL | OPT_D); // Lcd-on, cursor-off, no-blink
	lcd_write_command(lcd, ENTRY_MODE_SET | OPT_INC); // Increment cursor
}

//Write a number on the current positioin
void Lcd_number(Lcd_HandleTypeDef * lcd, int number){
	char buffer[11];
	sprintf(buffer, "%d", number); //esto toma una cadena de caracteres y los guarda en un buffer
	Lcd_string(lcd, buffer); //escribe un string en la posición actual
}

//Writes a character in current position
void Lcd_string(Lcd_HandleTypeDef * lcd, char * string){
	for(uint8_t i = 0; i < strlen(string); i++){ //vamos poniendo letra a letra del string en el display
		lcd_write_data(lcd, string[i]);
	}
}


//Set cursor
void Lcd_cursor(Lcd_HandleTypeDef * lcd, uint8_t row, uint8_t col){
	//#ifdef LCD16xN
	lcd_write_command(lcd, SET_DDRAM_ADDR + ROW_16[row] + col);
	//#endif
}

//Clear the screen
void Lcd_clear(Lcd_HandleTypeDef * lcd) {
	lcd_write_command(lcd, CLEAR_DISPLAY);
}

/* ESTO NO SÉ PARA QUÉ ESTÁ
void Lcd_define_char(Lcd_HandleTypeDef * lcd, uint8_t code, uint8_t bitmap[]){
	lcd_write_command(lcd, SETCGRAM_ADDR + (code << 3));
	for(uint8_t i=0;i<8;++i){
		lcd_write_data(lcd, bitmap[i]);
	}
}*/

//VER CÓMO ADAPTAR ESTO
//Send command byte
void lcd_write_command(Lcd_HandleTypeDef * lcd, uint8_t command){
	HAL_GPIO_WritePin(lcd->rs_port, lcd->rs_pin, LCD_COMMAND_REG); // Write to command register
	if(lcd->mode == LCD_4_BIT_MODE){
		lcd_write(lcd, (command >> 4), LCD_NIB);
		lcd_write(lcd, command & 0x0F, LCD_NIB);
	}
	else{
		lcd_write(lcd, command, LCD_BYTE);
	}
}

//Send data byte
void lcd_write_data(Lcd_HandleTypeDef * lcd, uint8_t data){
	HAL_GPIO_WritePin(lcd->rs_port, lcd->rs_pin, LCD_DATA_REG); // Write to data register
	if(lcd->mode == LCD_4_BIT_MODE){
		lcd_write(lcd, data >> 4, LCD_NIB);
		lcd_write(lcd, data & 0x0F, LCD_NIB);}
	else{
		lcd_write(lcd, data, LCD_BYTE);
	}
}



