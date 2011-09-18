#include <avr/io.h>
#include <string.h>

#include "ethernet.h"

static uint8_t _get_ethertype(uint8_t* val) {
	uint8_t ret = PROTO_ETH_TYPE_UNKNOWN;
	
	switch (val[0]) {
		case 8:
		switch (val[1]) {
			case 0:
			ret = PROTO_ETH_TYPE_IP;
			break;
			
			case 6:
			ret = PROTO_ETH_TYPE_ARP;
			break;
			
			default:
			break;
		}
		break;
		
		default:
		break;
	}
	
	return ret;
}

void proto_eth_analyse(uint8_t* packet, struct proto_eth_info* info) {	
	/* addresses */
	memcpy(info->dst_addr, packet, 6);
	memcpy(info->src_addr, packet + 6, 6);
	
	/* Ethernet version, network type or length, data start */
	if (packet[12] >= 6) {
		info->is_ii = 1;
		info->net_type = _get_ethertype(packet + 12);
		info->data_start = packet + 14;
	} else {
		info->is_ii = 0;
		info->len = packet[12] * 256;
		info->len += packet[13];
		if (packet[14] == 0xaa || packet[14] == 0xab ||
		packet[15] == 0xaa || packet[15] == 0xab) {
			/* means SNAP */
			info->net_type = _get_ethertype(packet + 20);
			info->data_start = packet + 22;
		} else {
			info->net_type = PROTO_ETH_TYPE_UNKNOWN;
			info->data_start = packet + 17;
		}
	}
}

uint8_t proto_eth_format_header(struct proto_eth_info* info, uint8_t* buf) {
	uint8_t* ori = buf;
	
	if (!info->is_ii) {
		return 0;
	}
	
	/* addresses */
	memcpy(buf, info->dst_addr, 6);
	buf += 6;
	memcpy(buf, info->src_addr, 6);
	buf += 6;
	
	/* Ethertype */
	switch (info->net_type) {		
		case PROTO_ETH_TYPE_IP:
		buf[0] = 8;
		buf[1] = 0;
		break;
		
		case PROTO_ETH_TYPE_ARP:
		buf[0] = 8;
		buf[1] = 6;
		break;
		
		default:
		return 0;
		break;
	}
	buf += 2;
	
	return (uint8_t) (buf - ori);
}

