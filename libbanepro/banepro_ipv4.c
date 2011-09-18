#include <avr/io.h>
#include <string.h>

#include "banepro_ipv4.h"
#include "banepro_utils.h"

#if BANEPRO_ENABLE_IPV4

uint8_t banepro_ipv4_format_header(struct banepro_ipv4_info* info, uint8_t* buf) {
	uint16_t checksum;
	
	/* version/IHL, type of service, length */
	buf[0] = 0x40 | ((info->header_len / 4) & 0xf);
	buf[1] = 0;
	buf[2] = (info->total_len >> 8) & 0xff;
	buf[3] = info->total_len & 0xff;
	
	/* ID */
	buf[4] = 0;
	buf[5] = 0;
	
	/* flags and fragment offset */
	buf[6] = 0x40; /* don't fragment */
	buf[7] = 0;
	
	/* TTL */
	buf[8] = info->ttl;
	
	/* transport protocol */
	switch (info->proto) {
		case BANEPRO_IPV4_PROTO_ICMP:
		buf[9] = 1;
		break;
		
		case BANEPRO_IPV4_PROTO_TCP:
		buf[9] = 6;
		break;
		
		case BANEPRO_IPV4_PROTO_UDP:
		buf[9] = 17;
		break;
		
		default:
		return 0;
		break;
	}
	
	/* addresses */
	memcpy(buf + 12, info->src_addr, 4);
	memcpy(buf + 16, info->dst_addr, 4);
	
	/* checksum */
	if (info->checksum != 0) {
		buf[10] = (info->checksum >> 8) & 0xff;
		buf[11] = info->checksum & 0xff;
	} else {
		buf[10] = 0;
		buf[11] = 0;
		checksum = banepro_u_checksum(buf, info->header_len);
		buf[10] = (checksum >> 8) & 0xff;
		buf[11] = checksum & 0xff;
	}
	
	return 20;
}

void banepro_ipv4_analyse(uint8_t* packet, struct banepro_ipv4_info* info) {
	/* header length (given length is in 4-byte blocks */
	info->header_len = (packet[0] & 0x0f) * 4;
	
	/* total length */
	info->total_len = packet[2] * 256;
	info->total_len += packet[3];
	
	/* TTL */
	info->ttl = packet[8];
	
	/* transport protocol */
	info->proto = BANEPRO_IPV4_PROTO_UNKNOWN;
	switch (packet[9]) {
		case 1:
		info->proto = BANEPRO_IPV4_PROTO_ICMP;
		break;
		
		case 6:
		info->proto = BANEPRO_IPV4_PROTO_TCP;
		break;
		
		case 17:
		info->proto = BANEPRO_IPV4_PROTO_UDP;
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

#endif /* BANEPRO_ENABLE_IPV4 */
