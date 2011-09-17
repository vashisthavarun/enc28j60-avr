#ifndef _M16_RS232_H
#define _M16_RS232_H

#include <avr/io.h>
#include <stdio.h>

#define M16_RS232_SPEED		16	/* UBRR value (see µC manual) */

/**
 * Sets stdio to/from RS-232.
 */ 
void m16_rs232_init_stdio(void);

/**
 * Initializes the RS-232 module.
 */
void m16_rs232_init(void);

/**
 * Sends a byte using RS-232.
 *
 * @param b	Byte
 */
void m16_rs232_send(uint8_t b);

/**
 * Receives a byte using RS-232.
 *
 * @return	Byte
 */
uint8_t m16_rs232_recv(void);

#endif /* _M16_RS232_H */
