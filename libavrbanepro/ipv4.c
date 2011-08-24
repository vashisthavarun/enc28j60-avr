#include <avr/io.h>
#include <string.h>

#include "ipv4.h"

void proto_ipv4_analyse(uint8_t* packet, struct proto_ipv4_info* info) {
	/* header length */
	info->header_len = packet[0] & 0x0f;
	
	/* total length */
	info->total_len = packet[2] * 256;
	info->total_len += packet[3];
	
	/* TTL */
	info->ttl = packet[8];
	
	/* transport protocol */
	info->proto = PROTO_IPV4_PROTO_UNKNOWN;
	switch (packet[9]) {
		case 1:
		info->proto = PROTO_IPV4_PROTO_ICMP;
		break;
		
		case 6:
		info->proto = PROTO_IPV4_PROTO_TCP;
		break;
		
		case 17:
		info->proto = PROTO_IPV4_PROTO_UDP;
		break;
		
		default:
		break;
	}
	
	/* checksum */
	info->checksum = packet[10] * 256;
	info->checksum += packet[11];
	
	/* addresses */
	memcpy(info->src_addr, packet + 12, 4);
	memcpy(info->dst_addr, packet + 16, 4);
	
	/* data start */
	info->data_start = packet + info->header_len;
}
