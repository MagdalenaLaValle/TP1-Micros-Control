#include "my_lib.h"
#include "LCD.h"

extern I2C_HandleTypeDef hi2c1;

// Send a command to the LCD
void lcd_send_cmd(uint8_t cmd)
{
    uint8_t data_u = cmd & 0xF0;
    uint8_t data_l = (cmd << 4) & 0xF0;
    uint8_t data_t[4];

    // High nibble
    data_t[0] = data_u | 0x0C;  // EN = 1, RS = 0
    data_t[1] = data_u | 0x08;  // EN = 0, RS = 0
    // Low nibble
    data_t[2] = data_l | 0x0C;  // EN = 1, RS = 0
    data_t[3] = data_l | 0x08;  // EN = 0, RS = 0

    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, data_t, 4, HAL_MAX_DELAY);
}

// Send a data byte (character) to the LCD
void lcd_send_data(uint8_t data)
{
    uint8_t data_u = data & 0xF0;
    uint8_t data_l = (data << 4) & 0xF0;
    uint8_t data_t[4];

    // High nibble
    data_t[0] = data_u | 0x0D;  // EN = 1, RS = 1
    data_t[1] = data_u | 0x09;  // EN = 0, RS = 1
    // Low nibble
    data_t[2] = data_l | 0x0D;  // EN = 1, RS = 1
    data_t[3] = data_l | 0x09;  // EN = 0, RS = 1

    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDRESS_LCD, data_t, 4, HAL_MAX_DELAY);
}

// Initialize the LCD in 4-bit mode
void lcd_init(void)
{
    HAL_Delay(50);           // Wait >40ms after power-on
    lcd_send_cmd(0x30);
    HAL_Delay(5);            // Wait >4.1ms
    lcd_send_cmd(0x30);
    HAL_Delay(1);            // Wait >100us
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20);      // Set to 4-bit mode
    HAL_Delay(10);

    // Function set: 4-bit, 2 line, 5x8 font
    lcd_send_cmd(0x28);
    HAL_Delay(1);
    // Display ON, Cursor OFF, Blink OFF
    lcd_send_cmd(0x0C);
    HAL_Delay(1);
    // Clear display
    lcd_send_cmd(0x01);
    HAL_Delay(2);
    // Entry mode: Increment cursor, no shift
    lcd_send_cmd(0x06);
    HAL_Delay(1);
}

// Send a string to the LCD
void lcd_send_string(char *str)
{
    while (*str)
    {
        lcd_send_data((uint8_t)*str++);
        HAL_Delay(1);
    }
}

// Position cursor: row = 0 or 1, col = 0..15
void lcd_put_cur(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(addr);
    HAL_Delay(1);
}





