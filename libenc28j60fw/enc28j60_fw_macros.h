#ifndef _ENC28J60_FW_MACROS_H
#define _ENC28J60_FW_MACROS_H

#include "enc28j60defs.h"

/*
       _   _ _ _ _   _          
 _   _| |_(_) (_) |_(_) ___ ___ 
| | | | __| | | | __| |/ _ | __|
| |_| | |_| | | | |_| |  __|__ \
 \__,_|\__|_|_|_|\__|_|\___|___/

*/

/**
 * Returns the bank of a given register.
 *
 * @param reg		Register (use bit definitions)
 * @return		Bank
 */
#define E28J60FW_BANK_OF(reg)	(((reg) >> E28J60_REG_BANK_SHIFT) & 0x3)

/**
 * Returns the high-byte of a 16-bit value.
 *
 * @param value16	16-bit value
 * @return		High-byte
 */
#define E28J60FW_HIGH(value16)	(((value16) >> 8) & 0xff)

/**
 * Returns the low-byte of a 16-bit value.
 *
 * @param value16	16-bit value
 * @return		Low-byte
 */
#define E28J60FW_LOW(value16)	((value16) & 0xff)


/*
 _        __       
(_)_ __  / _| ___  
| | '_ \| |_ / _ \ 
| | | | |  _| (_) |
|_|_| |_|_|  \___/ 

*/

/**
 * According to a status vector's high bytes, returns if the packet is a
 * broadcast one.
 *
 * @param status_vect_h		High bytes of status vector (16-bit)
 * @return			1 if broadcast packet, 0 otherwise
 */
#define E28J60FW_IS_BROADCAST_PACKET(status_vect_h) \
	(((status_vect_h) & 0x0200) > 0)

#endif /* _ENC28J60_FW_MACROS_H */
