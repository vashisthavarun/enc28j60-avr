#include <avr/io.h>
#include <util/delay.h>

#include "enc28j60_fw.h"
#include "enc28j60_fw_macros.h"

/**
 * @todo	Make this static variable part of a configuration structure to
 *		be passed as an argument of each framework function in order to
 *		support multiple devices controlled by a single MCU.
 */
static uint8_t g_current_bank = 0;

/**
 * Waits for a PHY operation.
 */
static void _wait_for_phy_op(void) {
	uint8_t buf;
	for(;;) {
		_delay_us(11);
		buf = e28j60fw_read_ctrl_reg_8(E28J60_MISTAT);
		if (!(buf & _BV(E28J60_BUSY))) {
			break;
		}
	}
}

void e28j60fw_switch_bank(uint8_t bank) {
	/* Calculate bitwise difference between current and new bank: */
	uint8_t diff = g_current_bank ^ bank;
	
	/* Update bit 0 if necessary: */
	if (diff & 0x01) {
		if (bank & 0x01) {
			e28j60_bfs(E28J60_ECON1, 0x01);
		} else {
			e28j60_bfc(E28J60_ECON1, 0x01);
		}
	}

	/* Update bit 1 if necessary: */
	if (diff & 0x02) {
		if (bank & 0x02) {
			e28j60_bfs(E28J60_ECON1, 0x02);
		} else {
			e28j60_bfc(E28J60_ECON1, 0x02);
		}
	}
	
	/* Update the current bank */
	g_current_bank = bank;
}

uint8_t e28j60fw_get_current_bank(void) {
	return g_current_bank;
}

uint8_t e28j60fw_read_ctrl_reg_8(uint8_t reg) {
	e28j60fw_switch_bank(E28J60FW_BANK_OF(reg));
	
	return e28j60_rcr(reg);
}

void e28j60fw_write_ctrl_reg_8(uint8_t reg, uint8_t value) {
	e28j60fw_switch_bank(E28J60FW_BANK_OF(reg));
	
	e28j60_wcr(reg, value);
}

void e28j60fw_bitfield_set(uint8_t reg, uint8_t or_mask) {
	e28j60fw_switch_bank(E28J60FW_BANK_OF(reg));
	
	e28j60_bfs(reg, or_mask);
}
void e28j60fw_bitfield_clr(uint8_t reg, uint8_t inv_and_mask) {
	e28j60fw_switch_bank(E28J60FW_BANK_OF(reg));
	
	e28j60_bfc(reg, inv_and_mask);
}

uint16_t e28j60fw_read_phy_reg(uint8_t phy_reg) {
	uint16_t ret = 0;
	
	/* Set which register to read */
	e28j60fw_write_ctrl_reg_8(E28J60_MIREGADR, phy_reg);
	
	/* Start the phy read operation */
	e28j60fw_bitfield_set(E28J60_MICMD, _BV(E28J60_MIIRD));
	
	/* Wait until the data is available */
	_wait_for_phy_op();

	/* Stop the phy read operation */
	e28j60fw_bitfield_clr(E28J60_MICMD, _BV(E28J60_MIIRD));
	
	/* Retrieve high and low bytes */
	ret = e28j60fw_read_ctrl_reg_8(E28J60_MIRDH);
	ret = ret << 8;
	ret += e28j60fw_read_ctrl_reg_8(E28J60_MIRDL); 
	
	return ret;	
}

void e28j60fw_write_phy_reg(uint8_t phy_reg, uint16_t value) {
	uint8_t high, low;
	
	/* Set which register to write */
	e28j60fw_write_ctrl_reg_8(E28J60_MIREGADR, phy_reg);
	
	high = E28J60FW_HIGH(value);
	low = E28J60FW_LOW(value);
	
	/* Order is important here */
	/* Write low byte */
	e28j60fw_write_ctrl_reg_8(E28J60_MIWRL, low);
	
	/* Write high byte and start operation */
	e28j60fw_write_ctrl_reg_8(E28J60_MIWRH, high);
	
	/* Wait for op to complete */
	_wait_for_phy_op();
}

void e28j60fw_write_ctrl_reg_16(uint8_t reg_high, uint8_t reg_low,
uint16_t value) {
	/* Datasheet says to write low-byte first most of the time... */
	e28j60fw_write_ctrl_reg_8(reg_low, E28J60FW_LOW(value));
	e28j60fw_write_ctrl_reg_8(reg_high, E28J60FW_HIGH(value));
}

void e28j60fw_set_mac_address(e28j60fw_mac_address_t mac_address) {
	/* Here is the odd thing: MAADR0 contains the LSB and the framework
	convention for e28j60fw_mac_address_t is that mac_address[0] contains
	the MSB */
	e28j60fw_write_ctrl_reg_8(E28J60_MAADR0, mac_address[5]);
	e28j60fw_write_ctrl_reg_8(E28J60_MAADR1, mac_address[4]);
	e28j60fw_write_ctrl_reg_8(E28J60_MAADR2, mac_address[3]);
	e28j60fw_write_ctrl_reg_8(E28J60_MAADR3, mac_address[2]);
	e28j60fw_write_ctrl_reg_8(E28J60_MAADR4, mac_address[1]);
	e28j60fw_write_ctrl_reg_8(E28J60_MAADR5, mac_address[0]);
}

uint8_t e28j60fw_has_new_packet(void) {
	uint8_t buf;
	
	buf = e28j60fw_read_ctrl_reg_8(E28J60_EIR);
	return (buf & _BV(E28J60_PKTIF)) > 0;
}

uint8_t e28j60fw_all_packets_sent(void) {
	uint8_t buf;
	
	buf = e28j60fw_read_ctrl_reg_8(E28J60_ECON1);
	return (buf & _BV(E28J60_TXRTS)) > 0;
}

void e28j60fw_set_rxtx_buf_size(uint16_t rx_size) {
	e28j60fw_write_ctrl_reg_16(E28J60_ERXSTH, E28J60_ERXSTL, 0);
	e28j60fw_write_ctrl_reg_16(E28J60_ERXNDH, E28J60_ERXNDL, rx_size);
	e28j60fw_write_ctrl_reg_16(E28J60_ERXRDPTH, E28J60_ERXRDPTL, 0);
}

void e28j60fw_easy_init(e28j60fw_mac_address_t mac_address, uint16_t rx_size,
uint16_t max_pkt_size) {
	/* initialize RX/TX buffers size */
	e28j60fw_set_rxtx_buf_size(rx_size);
	
	/* receive filters: unicast, broadcast and good CRC */
	/*e28j60fw_write_ctrl_reg_8(E28J60_ERXFCON, _BV(E28J60_UCEN) |
		_BV(E28J60_CRCEN) | _BV(E28J60_BCEN));*/
	
	/* MAC init. phase 1 */
	e28j60fw_bitfield_clr(E28J60_MACON2, _BV(E28J60_MARST));
	
	/* MAC init. phase 2 */
	e28j60fw_bitfield_set(E28J60_MACON1, _BV(E28J60_MARXEN));
	
	/* MAC init. phase 3 */
	e28j60fw_bitfield_set(E28J60_MACON3, _BV(E28J60_PADCFG0) |
		_BV(E28J60_PADCFG1) | _BV(E28J60_TXCRCEN));
	
	/* MAC init. phase 5 */
	e28j60fw_write_ctrl_reg_8(E28J60_MAMXFLL, E28J60FW_LOW(max_pkt_size));
	e28j60fw_write_ctrl_reg_8(E28J60_MAMXFLH, E28J60FW_HIGH(max_pkt_size));
	
	/* MAC init. phase 6 */
	e28j60fw_write_ctrl_reg_8(E28J60_MABBIPG, 0x12);
	
	/* MAC init. phase 7 */
	e28j60fw_write_ctrl_reg_8(E28J60_MAIPGL, 0x12);
	
	/* MAC init. phase 8 */
	e28j60fw_write_ctrl_reg_8(E28J60_MAIPGH, 0x0c);
	
	/* MAC address */
	e28j60fw_set_mac_address(mac_address);
	
	/* enable reception and ERDPT autoincrement upon RBM */
	e28j60fw_bitfield_set(E28J60_ECON1, _BV(E28J60_RXEN));
	e28j60fw_bitfield_set(E28J60_ECON2, _BV(E28J60_AUTOINC));
}

void e28j60fw_handle_rx_beg(struct e28j60fw_rx_info* info) {
	uint8_t pkt_start_l, pkt_start_h;

	/* ERXRDPT to ERDPT if previous packet wasn't all read */
	pkt_start_l = e28j60fw_read_ctrl_reg_8(E28J60_ERXRDPTL);
	pkt_start_h = e28j60fw_read_ctrl_reg_8(E28J60_ERXRDPTH);
	e28j60fw_write_ctrl_reg_8(E28J60_ERDPTL, pkt_start_l);
	e28j60fw_write_ctrl_reg_8(E28J60_ERDPTH, pkt_start_h);
	
	/* read next packet pointer value */
	info->next_packet_ptr = e28j60_rbm();
	info->next_packet_ptr |= (e28j60_rbm() << 8);
	
	/* read real packet size (including padding) */
	info->size = e28j60_rbm();
	info->size |= (e28j60_rbm() << 8);
	
	/* rest of status vector */
	info->status_vector_h = e28j60_rbm();
	info->status_vector_h |= (e28j60_rbm() << 8);
}

void e28j60fw_handle_rx_end(struct e28j60fw_rx_info* info) {
	e28j60fw_write_ctrl_reg_8(E28J60_ERXRDPTL,
		E28J60FW_LOW(info->next_packet_ptr));
	e28j60fw_write_ctrl_reg_8(E28J60_ERXRDPTH,
		E28J60FW_HIGH(info->next_packet_ptr));
	e28j60fw_bitfield_set(E28J60_ECON2, _BV(E28J60_PKTDEC));
}

void e28j60fw_prepare_tx(struct e28j60fw_tx_info* info) {
	e28j60fw_write_ctrl_reg_8(E28J60_ETXSTL, E28J60FW_LOW(info->rx_size));
	e28j60fw_write_ctrl_reg_8(E28J60_ETXSTH, E28J60FW_HIGH(info->rx_size));
	e28j60fw_write_ctrl_reg_8(E28J60_EWRPTL, E28J60FW_LOW(info->rx_size));
	e28j60fw_write_ctrl_reg_8(E28J60_EWRPTH, E28J60FW_HIGH(info->rx_size));
	e28j60_wbm(0); /* per packet control byte */
}

void e28j60fw_transmit(struct e28j60fw_tx_info* info) {
	uint16_t tx_end_ptr;
	
	tx_end_ptr = info->rx_size + info->len;
	e28j60fw_write_ctrl_reg_8(E28J60_ETXNDL, E28J60FW_LOW(tx_end_ptr));
	e28j60fw_write_ctrl_reg_8(E28J60_ETXNDH, E28J60FW_HIGH(tx_end_ptr));
	e28j60fw_bitfield_clr(E28J60_EIR, _BV(E28J60_TXIF));
	e28j60fw_bitfield_clr(E28J60_EIE, _BV(E28J60_TXIE));
	e28j60fw_bitfield_set(E28J60_ECON1, _BV(E28J60_TXRTS));
}
