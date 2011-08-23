#include "lcd.h"

#include "utils.h"

#include <util/delay.h>

uint8_t lcd_cursor = 0;

void _lcd_en_on()
{
	SET(LCD_PORT, LCD_EN);
}

void _lcd_en_off()
{
	CLR(LCD_PORT, LCD_EN);
}

void _lcd_en_pulse() 
{
	_delay_loop_1(5);
	_lcd_en_on();
	_delay_loop_1(5);
	_lcd_en_off();
	_delay_loop_1(5);
}

void _lcd_func_single(uint8_t rs, uint8_t rw, uint8_t byte)
{ 
	uint8_t n = (byte & 0xF) << LCD_DB4;
	n |= (rs << LCD_RS) | (rw << LCD_RW);
	
	LCD_PORT = n;
	_lcd_en_pulse();
	_delay_ms(2);
}

void _lcd_func(uint8_t rs, uint8_t rw, uint8_t byte)
{
	// High
	_lcd_func_single(rs, rw, byte >> 4);
	
	// Low
	_lcd_func_single(rs, rw, byte);
}


void lcd_init()
{
	LCD_DDR = 0xff;
	
	_delay_ms(15);
	
	_lcd_func_single(0, 0, 0x3);
	_lcd_func_single(0, 0, 0x3);
	_lcd_func_single(0, 0, 0x3);
	_lcd_func_single(0, 0, 0x2);
	_lcd_func(0, 0, 0x28);
	_lcd_func(0, 0, 0x08);
	_lcd_func(0, 0, 0x01);
	_lcd_func(0, 0, 0x06);
	
	lcd_display(LCD_DISPLAY_ON, LCD_CURSOR_OFF, LCD_BLINK_OFF);
}

void lcd_clear()
{
	_lcd_func(0, 0, 0x1);
}

void lcd_home()
{
	_lcd_func(0, 0, 0x02);
	lcd_cursor = LCD_FIRST_LINE;
}

void lcd_set_cursor(const uint8_t addr)
{
	uint8_t n = addr | 0x80;
	_lcd_func(0, 0, n);
	
	lcd_cursor = addr;
}

uint8_t lcd_get_cursor()
{
	return lcd_cursor;
}

void lcd_write(uint8_t c) {
	_lcd_func(1, 0, c);
	lcd_cursor++;
	if (lcd_cursor == LCD_FIRST_LINE + LCD_WIDTH) {
		lcd_set_cursor(LCD_SECOND_LINE);	
	} else if (lcd_cursor == LCD_SECOND_LINE + LCD_WIDTH) {
		lcd_set_cursor(LCD_FIRST_LINE);
	}
}

void lcd_write(const char* str) {
	const char* p = str;
	while (*p) {
		lcd_write(*p);
		p++;
	}
}

void lcd_display(uint8_t disp, uint8_t cursor, uint8_t blink) {
	uint8_t n = 0x8;
	n |= (disp << 2) | (cursor << 1) | (blink << 0);
	_lcd_func(0, 0, n);
}

