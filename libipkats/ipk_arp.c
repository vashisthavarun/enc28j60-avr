#include <avr/io.h>
#include <string.h>

#include "banepro_arp.h"
#include "banepro_ethernet.h"
#include "banepro_ipv4.h"
#include "ipk.h"
#include "ipk_config.h"
#include "ipk_arp.h"

/*
	ARP table.

	Cell 0 always contains the default gateway record; the IPv4 part
	contains its network prefix and the Ethernet part its MAC address.
	The other cells contain an IPv4 address to MAC address association.
	They follow an LRU replacement policy.
*/
static struct ipk_arp_table_record g_table [IPK_CFG_ARP_TABLE_SIZE];

void ipk_arp_init(struct ipk_conf* ipk_conf) {
	uint8_t x;
	
	for (x = 0; x < IPK_CFG_ARP_TABLE_SIZE; ++x) {
		g_table[x].valid_age = 0;
	}
	memcpy(g_table[0].ipv4_addr, ipk_conf->gateway_addr, 4);
	g_table[0].ipv4_addr[0] &= ipk_conf->subnet_mask[0];
	g_table[0].ipv4_addr[1] &= ipk_conf->subnet_mask[1];
	g_table[0].ipv4_addr[2] &= ipk_conf->subnet_mask[2];
	g_table[0].ipv4_addr[3] &= ipk_conf->subnet_mask[3];
}

enum ipk_arp_lu_ret_t ipk_arp_lookup(banepro_ipv4_addr ipv4_addr,
banepro_eth_mac_addr mac_addr, struct ipk_conf* ipk_conf) {
	uint8_t x;
	banepro_ipv4_addr tmp_ipv4_addr;
	
	/* check if IPv4 address is outside network */
	memcpy(tmp_ipv4_addr, ipv4_addr, 4);
	tmp_ipv4_addr[0] &= ipk_conf->subnet_mask[0];
	tmp_ipv4_addr[1] &= ipk_conf->subnet_mask[1];
	tmp_ipv4_addr[2] &= ipk_conf->subnet_mask[2];
	tmp_ipv4_addr[3] &= ipk_conf->subnet_mask[3];
	if (BANEPRO_IPV4_CMP(tmp_ipv4_addr, g_table[0].ipv4_addr)) {
		memcpy(mac_addr, g_table[0].mac_addr, 6);
			
		return IPK_ARP_LU_RET_FOUND;
	}
	
	/* lookup the table */
	for (x = 1; x < IPK_CFG_ARP_TABLE_SIZE; ++x) {
		if (BANEPRO_IPV4_CMP(ipv4_addr, g_table[x].ipv4_addr)) {
			memcpy(mac_addr, g_table[x].mac_addr, 6);
			
			return IPK_ARP_LU_RET_FOUND;
		}
	}
	
	/* send ARP request */
	/* TODO */
	
	
	return IPK_ARP_LU_RET_WAITING_FOR_REPLY;	
}
