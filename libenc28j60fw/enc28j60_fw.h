#ifndef _ENC28J60_FW_H
#define _ENC28J60_FW_H

#include <avr/io.h>

#include "enc28j60_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Base operations: */

/**
 * Switches the active register bank.
 * 
 * @param bank	Bank number (0..3)
 */
void enc_switch_bank(uint8_t bank);

/**
 * Returns current register bank's number.
 *
 * @return	Current register bank's number.
 */
uint8_t enc_get_current_bank(void);

/**
 * Reads from a simple control register - this function takes care of switching
 * the current register bank according to the given register.
 * 
 * @param reg	Register to read from (use driver definitions)
 * @return	Register value
 */
uint8_t enc_read_control_register_8(uint8_t reg);

/**
 * To be implemented.
 */
uint16_t enc_read_control_register_16(uint8_t reg_high, uint8_t reg_low);

/**
 * Writes to a simple control register - this function takes care of switching
 * the current register bank according to the given register.
 * 
 * @param reg	Register to write to (use driver definitions)
 * @param value	Value to be written
 */
void enc_write_control_register_8(uint8_t reg, uint8_t val);

/**
 * To be implemented.
 */
void enc_write_control_register_16(uint8_t reg_high, uint8_t reg_low,
	uint16_t value);

/**
 * Sets specific bits of a register.
 *
 * @param reg		Register (use driver definitions)
 * @param or_mask	Logical OR mask to apply to current register value
 */
void enc_bitfield_set(uint8_t reg, uint8_t or_mask);

/**
 * Clears specific bits of a register.
 *
 * @param reg		Register (use driver definitions)
 * @param inv_and_mask	Logical NOT AND mask to apply to current register value
 */
void enc_bitfield_clr(uint8_t reg, uint8_t inv_and_mask);

/**
 * Reads from a PHY register.
 *
 * @param phy_reg	PHY register to read from (use driver definitions)
 * @return		PHY register value
 */
uint16_t enc_read_phy_register(uint8_t phy_reg);

/**
 * Writes to a PHY register.
 *
 * @param phy_reg	PHY register to write to (use driver definitions)
 * @param value		Value to be written
 */
void enc_write_phy_register(uint8_t phy_reg, uint16_t value);

#ifdef __cplusplus
}
#endif

#endif /* _ENC28J60_FW_H */
