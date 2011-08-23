#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include "utils.h"
#include "lcd.h"
#include "enc28j60_driver.h"
#include "enc28j60_fw.h"


#define BEEP_PORT PORTB
#define BEEP_DDR DDRB
#define BEEP_BIT_A 0
#define BEEP_BIT_B 1

void beep_init()
{
	SET(BEEP_DDR, BEEP_BIT_A);
	SET(BEEP_DDR, BEEP_BIT_B); 
}

void init()
{
	lcd_init();
	beep_init();
	enc_init();

	sei();
}

void beep_high()
{
	for (uint8_t i = 0; i < 40; i++) {
		SET(BEEP_PORT, BEEP_BIT_A);
		CLR(BEEP_PORT, BEEP_BIT_B);
		_delay_ms(0.5);
		CLR(BEEP_PORT, BEEP_BIT_A);
		CLR(BEEP_PORT, BEEP_BIT_B);
		_delay_ms(0.5);
	}
}

void beep_low() 
{
	for (uint8_t i = 0; i < 10; i++) {
		SET(BEEP_PORT, BEEP_BIT_A);
		CLR(BEEP_PORT, BEEP_BIT_B);
		_delay_ms(2);
		CLR(BEEP_PORT, BEEP_BIT_A);
		CLR(BEEP_PORT, BEEP_BIT_B);
		_delay_ms(2);
	}
}



void write_bin(uint8_t val)
{
	char buf[9];
	utoa(val, buf, 2);
	uint8_t len = strlen(buf);
	
	for (uint8_t i = 0; i < (8 - len); i++) {
		lcd_write('0');
	}
	lcd_write(buf);
}

void write_bank()
{
	uint8_t c = lcd_get_cursor();
	lcd_set_cursor(LCD_SECOND_LINE);
	uint8_t bank = enc_current_bank();
	lcd_write("Bank ");
	lcd_write('0' + bank);
	lcd_set_cursor(c);
}

int main()
{
	uint16_t v16;
	uint8_t v8;
	// C'est pour me laisser le temps de changer mes switchs
	beep_low();
	_delay_ms(3000);
	beep_low();
	
	init();
	
	
	enc_bitfield_clr(ENC_MACON2, (1 << ENC_MARST));
	enc_bitfield_set(ENC_MACON3, (1 << ENC_PADCFG0) | (1 << ENC_PADCFG1) | (1 << ENC_TXCRCEN));
	uint16_t mamxfl = 1000;
	enc_write_control_register_8(ENC_MAMXFLL, ENC_LOW(mamxfl));
	enc_write_control_register_8(ENC_MAMXFLH, ENC_HIGH(mamxfl));
	enc_write_control_register_8(ENC_MABBIPG, 0x12);
	enc_write_control_register_8(ENC_MAIPGL, 0x12);
	enc_write_control_register_8(ENC_MAIPGH, 0x0C);
	enc_write_control_register_8(ENC_MAADR0, 0xAA);
	enc_write_control_register_8(ENC_MAADR1, 0xBB);
	enc_write_control_register_8(ENC_MAADR2, 0xCC);
	enc_write_control_register_8(ENC_MAADR3, 0xDD);
	enc_write_control_register_8(ENC_MAADR4, 0xEE);
	enc_write_control_register_8(ENC_MAADR5, 0xFF);
	
	enc_wbm(0);
	enc_wbm(0x01);
	enc_wbm(0x02);
	enc_wbm(0x03);
	enc_wbm(0x04);
	enc_wbm(0x05);
	enc_write_control_register_8(ENC_ETXSTL, 0);
	enc_write_control_register_8(ENC_ETXSTH, 0);
	enc_write_control_register_8(ENC_ETXNDL, 5);
	enc_write_control_register_8(ENC_ETXNDH, 0);
	
	for (;;) 
	{
	
		enc_bitfield_clr(ENC_EIR, (1 << ENC_TXIF));
		enc_bitfield_clr(ENC_EIE, (1 << ENC_TXIE));
		enc_bitfield_set(ENC_ECON1, (1 << ENC_TXRTS));
	
		for (;;)
		{
			uint8_t buf;
			_delay_ms(1);
			buf = enc_read_control_register_8(ENC_ECON1);
			if (!(buf & (1 << ENC_TXRTS))) {
				break;
			}
		
		}
		beep_high();
	
		_delay_ms(1000);
	}

	
	for(;;);
	return 0;
}
