#include <avr/io.h>
#include <stdio.h>

#include "banepro_utils.h"
#include "banepro_config.h"

uint16_t banepro_u_checksum(uint8_t* buf, uint16_t buf_len) {
	uint16_t sum = 0, tmp = 0;
	uint8_t x;
	
	/* add words and carries if any */
	for (x = 0; x < buf_len; x += 2) {
		tmp += (buf[x] * 256 + buf[x + 1]);
		if (tmp < sum) {
			tmp += 1; /* carry */
		}
		sum = tmp;
	}

	/* sum's 1's complement */
	return ~sum;
}

