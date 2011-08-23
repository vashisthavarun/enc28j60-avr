#pragma once

#include <avr/io.h>

#define LCD_PORT PORTA
#define LCD_DDR DDRA

#define LCD_RS  0
#define LCD_RW  1
#define LCD_EN  2
#define LCD_DB4 4
#define LCD_DB5 5
#define LCD_DB6 6
#define LCD_DB7 7

#define LCD_WIDTH 8
#define LCD_FIRST_LINE 0x00
#define LCD_SECOND_LINE 0x40

#define LCD_DISPLAY_OFF 0
#define LCD_DISPLAY_ON 1
#define LCD_CURSOR_OFF 0
#define LCD_CURSOR_ON 1
#define LCD_BLINK_OFF 0
#define LCD_BLINK_ON 1

void lcd_init();
void lcd_clear();
void lcd_home();
void lcd_set_cursor(const uint8_t addr);
uint8_t lcd_get_cursor();
void lcd_write(uint8_t c);
void lcd_write(const char* str);
void lcd_display(uint8_t disp, uint8_t cursor, uint8_t blink);
