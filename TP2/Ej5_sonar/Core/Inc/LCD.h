#ifndef INC_LCD_H_
#define INC_LCD_H_


#define PCF_Address 0b0100111

#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
#define ENTRY_MODE_SET 0x04
#define OPT_S 0x01 // Shift entire display to right
#define OPT_INC 0x02 // Cursor increment
#define DISPLAY_ON_OFF_CONTROL 0x08
#define OPT_D 0x04 // Turn on display
#define OPT_C 0x02 // Turn on cursor
#define OPT_B 0x01 // Turn on cursor blink
#define CURSOR_DISPLAY_SHIFT 0x10 // Move and shift cursor
#define ClearDisplay 0b01

#define SetDisplay  0x0C //0b01100


#define DELAY(X) HAL_Delay(X)


#endif /* INC_LCD_H_ */
