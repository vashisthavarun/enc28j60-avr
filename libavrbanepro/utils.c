#include <avr/io.h>

#include "utils.h"

uint16_t proto_u_checksum(uint8_t* buf, uint16_t buf_len) {
	uint32_t sum = 0;
	uint8_t x;
	uint16_t* buf16 = (uint16_t*) buf;
	uint16_t ret;
	
	/* add 2's complement */
	for (x = 0; x < (buf_len / 2); ++x) {
		sum += buf16[x];
	}
	
	/* add the carries (gives us 16-bit 1's complement sum) */
	ret = sum & 0xffff;
	ret += ((sum >> 8) & 0xffff);
	
	/* return sum's 1's complement */
	return ~ret;
}
