#ifndef _ENC28J60_FW_H
#define _ENC28J60_FW_H

#include <avr/io.h>

#include "enc28j60_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * MAC address type; byte index 0 within the array is the most significative
 * one in the MAC address; thus, this does not follow the ENC28J60 scheme where
 * MAADR0 is the least significant byte of the address; i.e. the convention
 * within this framework is:
 *	for the MAC address i:j:k:l:m:n, we have
 *		mac_addr[0] = i;
 *		mac_addr[1] = j;
 *		mac_addr[2] = k;
 *		mac_addr[3] = l;
 *		mac_addr[4] = m;
 *		mac_addr[5] = n;
 */
typedef uint8_t e28j60fw_mac_address_t [6];

/**
 * Reception information.
 */
struct e28j60fw_rx_info {
	uint16_t next_packet_ptr;	/* Next packet pointer */
	uint16_t status_vector_h;	/* Status vector high bytes */
	uint16_t size;			/* Packet size including padding */
};

/**
 * Transmission information.
 */
struct e28j60fw_tx_info {
	uint16_t rx_size;		/* RX buffer size */
	uint16_t len;			/* Number of bytes to send */
};

/**
 * Switches the active register bank.
 * 
 * @param bank	Bank number (0..3)
 */
void e28j60fw_switch_bank(uint8_t bank);

/**
 * Returns current register bank's number.
 *
 * @return	Current register bank's number.
 */
uint8_t e28j60fw_get_current_bank(void);

/**
 * Reads an 8-bit control register - this function takes care of switching
 * the current register bank according to the given register.
 * 
 * @param reg	Register to read from (use driver definitions)
 * @return	Register value
 */
uint8_t e28j60fw_read_ctrl_reg_8(uint8_t reg);

/**
 * TODO
 */
uint16_t e28j60fw_read_ctrl_reg_16(uint8_t reg_high, uint8_t reg_low);

/**
 * Writes to an 8-bit control register - this function takes care of switching
 * the current register bank according to the given register.
 * 
 * @param reg		Register to write to (use driver definitions)
 * @param value		Value to write
 */
void e28j60fw_write_ctrl_reg_8(uint8_t reg, uint8_t val);

/**
 * Writes to a 16-bit control register - this function takes care of switching
 * the current register bank according to the given registers.
 * 
 * @param reg_high	High-byte register to write to (use bit definitions)
 * @param reg_low	Low-byte register to write to (use bit definitions)
 * @param value		Value to write
 */
void e28j60fw_write_ctrl_reg_16(uint8_t reg_high, uint8_t reg_low,
uint16_t value);

/**
 * Sets specific bits of a register.
 *
 * @param reg		Register (use driver definitions)
 * @param or_mask	Logical OR mask to apply to current register value
 */
void e28j60fw_bitfield_set(uint8_t reg, uint8_t or_mask);

/**
 * Clears specific bits of a register.
 *
 * @param reg		Register (use driver definitions)
 * @param inv_and_mask	Logical NOT AND mask to apply to current register value
 */
void e28j60fw_bitfield_clr(uint8_t reg, uint8_t inv_and_mask);

/**
 * Reads from a PHY register.
 *
 * @param phy_reg	PHY register to read from (use driver definitions)
 * @return		PHY register value
 */
uint16_t e28j60fw_read_phy_reg(uint8_t phy_reg);

/**
 * Writes to a PHY register.
 *
 * @param phy_reg	PHY register to write to (use driver definitions)
 * @param value		Value to be written
 */
void e28j60fw_write_phy_reg(uint8_t phy_reg, uint16_t value);

/**
 * Sets the device's MAC address - see documentation to understand when it's
 * appropriate to call this.
 *
 * @param mac_address		New MAC address (see typedef comment)
 */
void e28j60fw_set_mac_address(e28j60fw_mac_address_t mac_address);

/**
 * Verifies if a new packet is available.
 *
 * @return	true if a new packet is available
 */
uint8_t e28j60fw_has_new_packet(void);

/**
 * Verifies if all packets are sent.
 *
 * @return	true if all packets are gone
 */
uint8_t e28j60fw_all_packets_sent(void);

/**
 * Sets the RX/TX buffers sizes.
 *
 * @param rx_size	RX buffer size (TX is (8 kIB - RX size))
 */
void e28j60fw_set_rxtx_buf_size(uint16_t rx_size);

/**
 * Easy initialization - half duplex.
 *
 * @param mac_address		MAC address
 * @param rx_size		RX buffer size (bytes)
 * @param max_pkt_size		Maximum packets size
 */
void e28j60fw_easy_init(e28j60fw_mac_address_t mac_address, uint16_t rx_size,
uint16_t max_pkt_size);

/**
 * Handles the beginning of a reception - following this call, all subsequent
 * RBM will read the actual packet.
 *
 * @param info	Packet info structure to be filled
 */
void e28j60fw_handle_rx_beg(struct e28j60fw_rx_info* rx_info);

/**
 * Handles the end of a reception - after this call, a new packet should be
 * verified and e28j60fw_handle_rx_beg should be called again.
 *
 * @param info	Packet info structure previously filled by caller
 */
void e28j60fw_handle_rx_end(struct e28j60fw_rx_info* info);

/**
 * Prepares a transmission (updates the write pointer and some registers).
 *
 * @param info		Properly filled transmission info
 */
void e28j60fw_prepare_tx(struct e28j60fw_tx_info* info);

/**
 * Sends bytes written in the buffer.
 *
 * @param info		Properly filled transmission info
 */
void e28j60fw_transmit(struct e28j60fw_tx_info* info);

/**
 * Reads a byte from the receive buffer (alias of e28j60_rbm for nomenclature).
 */
#define e28j60fw_read_byte	e28j60_rbm

/**
 * Writes a byte to the transmit buffer (alias of e28j60_wbm for nomenclature).
 */
#define e28j60fw_write_byte	e28j60_wbm

#ifdef __cplusplus
}
#endif

#endif /* _ENC28J60_FW_H */
