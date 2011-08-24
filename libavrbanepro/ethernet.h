#ifndef _ETHERNET_H
#define _ETHERNET_H

#include <avr/io.h>

/* Ethertype definitions */
#define PROTO_ETH_TYPE_UNKNOWN		0
#define PROTO_ETH_TYPE_IP		1
#define PROTO_ETH_TYPE_ARP		2

/* Ethernet definitions */
#define PROTO_ETH_MAC_ADDR_LEN		6

/* MAC address */
typedef uint8_t proto_eth_mac_addr [6];

/* Information structure for Ethernet (both II and 802.3) */
struct proto_eth_info {
	proto_eth_mac_addr dst_addr;	/* destination MAC address */
	proto_eth_mac_addr src_addr;	/* source MAC address */
	uint8_t is_ii;			/* 1 if Ethernet II, 0 if 802.3 */
	uint16_t len;			/* length in bytes (if 802.3) */
	uint8_t net_type;		/* ethertype (few are defined) */
	uint8_t* data_start;		/* data start pointer */
};

/**
 * Analyses an Ethernet packet and gives information about it.
 *
 * @param packet	Ethernet packet (pointing to first byte of dest. addr.)
 * @param info		Information structure to be filled
 */
void proto_eth_analyse(uint8_t* packet, struct proto_eth_info* info);

/**
 * Formats an Ethernet II packet header using an information structure.
 *
 * @param info		Information structure (is_ii must be set to 1)
 * @param buf		Buffer where to put formatted packet header (big enough)
 * @return		Formatted packet header length (0 if error)
 */
uint8_t proto_eth_format_header(struct proto_eth_info* info, uint8_t* buf);

#endif /* _ETHERNET_H */
