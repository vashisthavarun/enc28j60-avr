#include <avr/io.h>
#include <string.h>

#include "icmp.h"
#include "utils.h"

void proto_icmp_analyse(uint8_t* packet, struct proto_icmp_info* info) {
	/* type */
	info->type = PROTO_ICMP_TYPE_UNKNOWN;
	switch (packet[0]) {
		case 0:
		info->type = PROTO_ICMP_TYPE_ECHO_REPLY;
		break;
		
		case 8:
		info->type = PROTO_ICMP_TYPE_ECHO_REQUEST;
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

uint8_t proto_icmp_format_header(struct proto_icmp_info* info, uint8_t* buf,
uint8_t* data, uint16_t data_len) {
	uint16_t checksum;
	
}
