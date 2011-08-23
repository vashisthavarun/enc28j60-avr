#include <util/delay.h>

#include "enc28j60_fw.h"
#include "enc28j60_fw_macros.h"

/**
 * @todo	Make this static variable part of a configuration structure to
 *		be passed as an argument of each framework function in order to
 *		support multiple devices controlled by a single MCU.
 */
static uint8_t _current_bank = 0;

void enc_switch_bank(uint8_t bank)
{
	/* Calculate bitwise difference between current and new bank: */
	uint8_t diff = _current_bank ^ bank;
	
	/* Update bit 0 if necessary: */
	if (diff & 0x01) {
		if (bank & 0x01) {
			enc_bfs(ENC_ECON1, 0x01);
		} else {
			enc_bfc(ENC_ECON1, 0x01);
		}
	}

	/* Update bit 1 if necessary: */
	if (diff & 0x02) {
		if (bank & 0x02) {
			enc_bfs(ENC_ECON1, 0x02);
		} else {
			enc_bfc(ENC_ECON1, 0x02);
		}
	}
	
	/* Update the current bank */
	_current_bank = bank;
}

uint8_t enc_get_current_bank(void)
{
	return _current_bank;
}

uint8_t enc_read_control_register_8(uint8_t reg)
{
	enc_switch_bank(ENC_BANK_OF(reg));
	
	return enc_rcr(reg);
}

void enc_write_control_register_8(uint8_t reg, uint8_t value)
{
	enc_switch_bank(ENC_BANK_OF(reg));
	
	enc_wcr(reg, value);
}

void enc_bitfield_set(uint8_t reg, uint8_t or_mask)
{
	enc_switch_bank(ENC_BANK_OF(reg));
	
	enc_bfs(reg, or_mask);
}
void enc_bitfield_clr(uint8_t reg, uint8_t inv_and_mask)
{
	enc_switch_bank(ENC_BANK_OF(reg));
	
	enc_bfc(reg, inv_and_mask);
}

static void _enc_wait_for_phy_op()
{
	uint8_t buf;
	for(;;) {
		_delay_us(11);
		buf = enc_read_control_register_8(ENC_MISTAT);
		if (!(buf & (1 << ENC_BUSY))) {
			break;
		}
	}
}

uint16_t enc_read_phy_register(uint8_t phy_reg)
{
	uint16_t ret = 0;
	
	/* Set which register to read */
	enc_write_control_register_8(ENC_MIREGADR, phy_reg);
	
	/* Start the phy read operation */
	enc_bitfield_set(ENC_MICMD, (1 << ENC_MIIRD));
	
	/* Wait until the data is available */
	_enc_wait_for_phy_op();

	/* Stop the phy read operation */
	enc_bitfield_clr(ENC_MICMD, (1 << ENC_MIIRD));
	
	/* Retrieve high and low bytes */
	ret = enc_read_control_register_8(ENC_MIRDH);
	ret = ret << 8;
	ret = ret + enc_read_control_register_8(ENC_MIRDL); 
	
	return ret;	
}

void enc_write_phy_register(uint8_t phy_reg, uint16_t value)
{
	uint8_t high, low;
	
	/* Set which register to write */
	enc_write_control_register_8(ENC_MIREGADR, phy_reg);
	
	high = ENC_HIGH(value);
	low = ENC_LOW(value);
	
	/* Order is important here */
	/* Write low byte */
	enc_write_control_register_8(ENC_MIWRL, low);
	
	/* Write high byte and start operation */
	enc_write_control_register_8(ENC_MIWRH, high);
	
	/* Wait for op to complete */
	_enc_wait_for_phy_op();
}

