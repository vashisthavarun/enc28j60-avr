#include <avr/io.h>
#include <string.h>

#include "arp.h"

void proto_arp_analyse(uint8_t* packet, struct proto_arp_info* info) {
	uint8_t hw_len, proto_len;
	
	/* assume a valid packet */
	info->is_valid = 1;
	
	/* types */
	info->hw_type = PROTO_ARP_HWTYPE_UNKNOWN;
	switch (packet[0]) {
		case 0:
		switch (packet[1]) {
			case 1:
			info->hw_type = PROTO_ARP_HWTYPE_ETH;
			break;
			
			default:
			info->is_valid = 0;
			break;
		}
		break;
		
		default:
		info->is_valid = 0;
		break;
	}
	info->proto_type = PROTO_ARP_PTYPE_UNKNOWN;
	switch (packet[2]) {
		case 8:
		switch (packet[3]) {
			case 0:
			info->hw_type = PROTO_ARP_PTYPE_IP;
			break;
			
			default:
			info->is_valid = 0;
			break;
		}
		break;
		
		default:
		info->is_valid = 0;
		break;
	}
		
	/* lengths */
	info->hw_addr_len = packet[4];
	info->proto_addr_len = packet[5];
	if (info->hw_addr_len > PROTO_ARP_MAX_ADDR_LEN ||
	info->proto_addr_len > PROTO_ARP_MAX_ADDR_LEN) {
		info->is_valid = 0;
	}
	
	/* cache */
	hw_len = info->hw_addr_len;
	proto_len = info->proto_addr_len;
	
	/* operation */
	info->op = PROTO_ARP_OP_UNKNOWN;
	switch (packet[6]) {
		case 0:
		switch (packet[7]) {
			case 1:
			info->op = PROTO_ARP_OP_REQUEST;
			break;
			
			case 2:
			info->op = PROTO_ARP_OP_REPLY;
			break;
			
			default:
			info->is_valid = 0;
			break;
		}
		break;
		
		default:
		info->is_valid = 0;
		break;
	}
	
	/* sender addresses */
	memcpy(info->sha, packet + 8, hw_len);
	memcpy(info->spa, packet + 8 + hw_len, proto_len);
	
	/* target addresses */
	memcpy(info->tha, packet + 8 + hw_len + proto_len, hw_len);
	memcpy(info->tpa, packet + 8 + (2 * hw_len) + proto_len, proto_len);
}

void proto_arp_inplace_reply(struct proto_arp_info* info, uint8_t* my_hw_addr) {
	uint8_t buf [PROTO_ARP_MAX_ADDR_LEN];
	uint8_t hw_len, proto_len;
	
	/* cache */
	hw_len = info->hw_addr_len;
	proto_len = info->proto_addr_len;
	
	/* reply operation */
	info->op = PROTO_ARP_OP_REPLY;
	
	/* swap sender/target addresses */
	memcpy(info->tha, info->sha, hw_len);
	memcpy(info->sha, my_hw_addr, hw_len);
	memcpy(buf, info->spa, proto_len);
	memcpy(info->spa, info->tpa, proto_len);
	memcpy(info->tpa, buf, proto_len);
}

uint8_t proto_arp_format_packet(struct proto_arp_info* info, uint8_t* buf) {
	uint8_t hw_len, proto_len;
	uint8_t* ori = buf;
	
	/* cache */
	hw_len = info->hw_addr_len;
	proto_len = info->proto_addr_len;
	
	/* hardware type */
	switch (info->hw_type) {
		case PROTO_ARP_HWTYPE_ETH:
		buf[0] = 0;
		buf[1] = 1;
		break;
		
		default:
		break;
	}
	
	/* protocol type */
	switch (info->proto_type) {
		case PROTO_ARP_PTYPE_IP:
		buf[2] = 8;
		buf[3] = 0;
		break;
		
		default:
		break;
	}
	
	/* lengths */
	buf[4] = hw_len;
	buf[5] = proto_len;
	
	/* operation */
	buf[6] = 0;
	switch (info->op) {
		case PROTO_ARP_OP_REQUEST:
		buf[7] = 1;
		break;
		
		case PROTO_ARP_OP_REPLY:
		buf[7] = 2;
		break;
		
		default:
		break;
	}
	buf += 8;
	
	/* sender addresses */
	memcpy(buf, info->sha, hw_len);
	buf += hw_len;
	memcpy(buf, info->spa, proto_len);
	buf += proto_len;
	
	/* target addresses */
	memcpy(buf, info->tha, hw_len);
	buf += hw_len;
	memcpy(buf, info->tpa, proto_len);
	buf += proto_len;
	
	return (uint8_t) (buf - ori);
}
