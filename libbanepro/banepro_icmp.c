#include <avr/io.h>
#include <string.h>

#include "banepro_icmp.h"
#include "banepro_utils.h"
#include "banepro_config.h"

#if BANEPRO_ENABLE_ICMP

void banepro_icmp_analyse(uint8_t* packet, struct banepro_icmp_info* info) {
	/* type */
	info->type = BANEPRO_ICMP_TYPE_UNKNOWN;
	switch (packet[0]) {
		case 0:
		info->type = BANEPRO_ICMP_TYPE_ECHO_REPLY;
		break;
		
		case 8:
		info->type = BANEPRO_ICMP_TYPE_ECHO_REQUEST;
		break;
		
		default:
		break;
	}
	
	/* code */
	info->code = packet[1];
	
	/* checksum */
	info->checksum = packet[2] * 256;
	info->checksum += packet[3];
	
	/* quench, rest of header */
	memcpy(info->quench, packet + 4, 4);
}

uint8_t banepro_icmp_format_header(struct banepro_icmp_info* info, uint8_t* buf,
uint8_t compute_chk, uint8_t* data, uint16_t data_len) {
	uint16_t chk, chk2;
	
	/* type */
	switch (info->type) {
		case BANEPRO_ICMP_TYPE_ECHO_REPLY:
		buf[0] = 0;
		break;
		
		case BANEPRO_ICMP_TYPE_ECHO_REQUEST:
		buf[0] = 8;
		break;
		
		default:
		return 0;
		break;
	}
	
	/* code */
	buf[1] = info->code;
	
	/* quench */
	memcpy(buf + 4, info->quench, 4);
	
	/* checksum */
	if (compute_chk) {
		buf[2] = 0;
		buf[3] = 0;
		chk = banepro_u_checksum(buf, 8); /* header checksum */
		chk2 = banepro_u_checksum(data, data_len); /* data checksum */
		info->checksum = chk + chk2;
		if (info->checksum < chk) {
			/* precedent sum will never be over chk2 neither */ 
			info->checksum += 1; /* carry, if any */
		}
	}
	buf[2] = (info->checksum >> 8) & 0xff;
	buf[3] = (info->checksum) & 0xff;

	/* always 8 */	
	return 8;
}

#endif /* BANEPRO_ENABLE_ICMP */
