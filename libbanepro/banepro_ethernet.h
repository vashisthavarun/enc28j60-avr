#ifndef _BANEPRO_ETHERNET_H
#define _BANEPRO_ETHERNET_H

#include <avr/io.h>

#include "banepro_config.h"

#if BANEPRO_ENABLE_ETHERNET

/* EtherType definitions (our own definitions) */
#define BANEPRO_ETH_TYPE_UNKNOWN		0
#define BANEPRO_ETH_TYPE_IP			1
#define BANEPRO_ETH_TYPE_ARP			2

/* Ethernet definitions */
#define BANEPRO_ETH_MAC_ADDR_LEN		6

/* MAC address */
typedef uint8_t banepro_eth_mac_addr [BANEPRO_ETH_MAC_ADDR_LEN];

/* Information structure for Ethernet (both II and 802.3) */
struct banepro_eth_info {
	banepro_eth_mac_addr dst_addr;	/* destination MAC address */
	banepro_eth_mac_addr src_addr;	/* source MAC address */
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
void banepro_eth_analyse(uint8_t* packet, struct banepro_eth_info* info);

/**
 * Formats an Ethernet II packet header using an information structure.
 *
 * @param info		Information structure (is_ii must be set to 1)
 * @param buf		Buffer where to put formatted packet header (big enough)
 * @return		Formatted packet header length (0 if error)
 */
uint8_t banepro_eth_format_header(struct banepro_eth_info* info, uint8_t* buf);

#endif /* BANEPRO_ENABLE_ETHERNET */

#endif /* _BANEPRO_ETHERNET_H */
