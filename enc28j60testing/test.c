#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "enc28j60_driver.h"
#include "enc28j60defs.h"
#include "enc28j60_fw.h"
#include "m16_rs232.h"
#include "testcases.h"

static void init_spi(void) {
	SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPR1) | _BV(SPR0);
	DDRB |= _BV(PB4) | _BV(PB5) | _BV(PB7);
}

int main(void) {
	m16_rs232_init_stdio();
	init_spi();
	
	/* avoid OST */
	_delay_ms(500.0);

	/* use case */
	printf("launching test case\n--------\n");
	testcase_arp_reply();
	
	for (;;);
	
	return 0;
}
