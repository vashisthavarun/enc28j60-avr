#include <avr/io.h>
#include <stdio.h>

#include "m16_rs232.h"

static uint8_t g_initialized = 0;

static int stdio_put(char c, FILE* file) {
	m16_rs232_send((uint8_t) c);
	
	return 0;
}

static int stdio_get(FILE* file) {
	return (int) m16_rs232_recv();
}

void m16_rs232_init_stdio(void) {
	m16_rs232_init();
	fdevopen(stdio_put, stdio_get);
}

void m16_rs232_init(void) {
	if (!g_initialized) {
		UBRRL = M16_RS232_SPEED;
		UCSRB = _BV(RXEN) | _BV(TXEN);
		UCSRC = _BV(URSEL) | _BV(UCSZ1) | _BV(UCSZ0);
		g_initialized = 1;
	}
}

void m16_rs232_send(uint8_t b) {
	while (!(UCSRA & _BV(UDRE)));
	UDR = b;
}

uint8_t m16_rs232_recv(void) {
	while (!(UCSRA & _BV(RXC)));
	
	return UDR;
}
