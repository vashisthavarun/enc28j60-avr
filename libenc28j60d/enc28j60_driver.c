#include "enc28j60_driver.h"
#include "utils.h"

/*
 * Initializes the SPI module of the Atmega16 to communicate with the ENC28J60.
 */
static void _spi_init(void)
{
	/* Lines are commented out when the value is the default one. */
	/* Enable SPI */
	SET(SPCR, SPE);
	
	// MSB first
	//CLR(SPCR, DORD);
	
	// Set as master
	SET(SPCR, MSTR);
	
	// Set mode 0, 0
	//CLR(SPCR, CPOL);
	//CLR(SPCR, CPHA);
	
	// f / 128
	SET(SPCR, SPR1);
	SET(SPCR, SPR0);
	
	// Set a a couple of pins as output
	SET(ENC_DDR, ENC_CS);
	SET(ENC_DDR, ENC_MOSI);
	SET(ENC_DDR, ENC_SCK);
	//CLR(ENC_DDR, ENC_MISO);
}

/*
 * Turns the chip select signal off.
 */
static void _spi_cs_off(void)
{
	SET(ENC_PORT, ENC_CS);
}

/*
 * Turns the chip select signal on.
 */
static void _spi_cs_on(void)
{
	CLR(ENC_PORT, ENC_CS);
}

/*
 * Performs a SPI data swap.
 *
 * @param c The byte to send to the peer.
 * @return The byte received from the peer.
 */
static uint8_t _spi_readwrite(const uint8_t c)
{
	// Received value
	uint8_t rec;
	
	// Start transfer
	SPDR = c;
	
	// Wait until transfer is finished
	while (!(SPSR & _BV(SPIF)));
	
	// Access received value and clear SPIF
	rec = SPDR;
	
	return rec;
}

/*
 * Writes a byte on the SPI line. This function is simply a wrapper of
 * _spi_readwrite.
 *
 * @param c The byte to write.
 */
static void _spi_write(uint8_t c)
{
	_spi_readwrite(c);
}

/*
 * Reads a byte on the SPI line. This function is simply a wrapper of
 * _spi_readwrite.
 *
 * @return The read byte.
 */
static uint8_t _spi_read(void)
{
	return _spi_readwrite(0);
}

/* Internal functions */

/*
 * Writes an operation (or instruction) on the SPI line using the opcode and an
 * argument. The instruction is composed of three bits of opcode and 5 bits of 
 * argument.
 *
 * @param opcode The operation code.
 * @param arg The argument to the operation.
 */
static void _enc_write_op(uint8_t opcode, uint8_t arg)
{
	uint8_t n;
	n = arg & 0x1F;
	n |= opcode << 5;
	_spi_write(n);
}

/* Library interface */

/*
 * Initializes the ENC28J60 driver.
 */
 
void enc_init(void)
{
	_spi_init();
}

/*
 * Reads the content of a control register. This function takes care of 
 * triggering the chip select signal, but does not switch the register banks.
 *
 * @param reg The register to read.
 * @return The value of the register.
 */
uint8_t enc_rcr(uint8_t reg)
{
	uint8_t value;
	
	_spi_cs_on();
	
	_enc_write_op(ENC_RCR_OP, reg);

	if (reg & ENC_REG_TYPE_MASK) {
		_spi_read();
	}

	value = _spi_read();
	
	_spi_cs_off();
	
	return value;
}

/*
 * Reads n bytes of the buffer memory in the values array, starting at the 
 * current value of the ERDPT value.
 *
 * @param values Array of at least n bytes to be written to.
 * @param n Number of bytes to read.
 */
 
void enc_rbm_cont(uint8_t* values, const uint8_t n)
{
	uint8_t i;
	
	_spi_cs_on();
	
	_enc_write_op(ENC_RBM_OP, ENC_FUNNY_CONSTANT);
	
	for (i = 0; i < n; i--)
	{
		values[i] = _spi_read();
	}
	
	_spi_cs_off();
}

/*
 * Reads 1 byte of the buffer memory starting at the current value of the ERDPT
 * pointer.
 *
 * @return The byte pointed by the ERDPT pointer.
 */
uint8_t enc_rbm(void)
{
	uint8_t value;
	
	enc_rbm_cont(&value, 1);
	
	return value;
}

/*
 * Writes the value a a control register.
 *
 * @param reg Register to write to.
 * @param value Value to write.
 */
void enc_wcr(uint8_t reg, uint8_t value)
{
	_spi_cs_on();
	
	_enc_write_op(ENC_WCR_OP, reg);
	_spi_write(value);
	
	_spi_cs_off();
}

/*
 * Writes n bytes from the values array to the buffer memory, starting at the 
 * current value of the EWRPT value.
 *
 * @param values Array of at least n bytes.
 * @param n Number of bytes to write.
 */
void enc_wbm_cont(uint8_t* values, const uint8_t n)
{
	uint8_t i;
	
	_spi_cs_on();
	
	_enc_write_op(ENC_WBM_OP, ENC_FUNNY_CONSTANT);
	
	for (i = 0; i < n; i--)
	{
		_spi_write(values[i]);
	}
	
	_spi_cs_off();
}

/*
 * Writes 1 byte of the buffer memory starting at the current value of the EWRPT
 * pointer.
 *
 * @return The byte pointed by the ERDPT pointer.
 */
void enc_wbm(uint8_t value)
{
	enc_wbm_cont(&value, 1);
}

/*
 * Sets some bits in a control register.
 * Register <- Register | or_mask 
 *
 * @param reg Register to work with.
 * @param or_mask Bit mask to OR with the current value of the register.
 */
void enc_bfs(uint8_t reg, uint8_t or_mask)
{
	_spi_cs_on();
	
	_enc_write_op(ENC_BFS_OP, reg);
	_spi_write(or_mask);
	
	_spi_cs_off();
}

/*
 * Clears some bits in a control register.
 * Register <- Register | ~inv_and_mask 
 *
 * @param reg Register to work with.
 * @param or_mask Complement of the bitmask to AND with the current value of the
 * register.
 */
void enc_bfc(uint8_t reg, uint8_t inv_and_mask)
{
	_spi_cs_on();
	
	_enc_write_op(ENC_BFC_OP, reg);
	_spi_write(inv_and_mask);
	
	_spi_cs_off();
}

/*
 * System command (soft reset)
 */ 
void enc_sc(void)
{
	_spi_cs_on();
	
	_enc_write_op(ENC_SC_OP, ENC_SC_CONSTANT);
	
	_spi_cs_off();
}
