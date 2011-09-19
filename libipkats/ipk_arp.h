#ifndef _IPK_ARP_H
#define _IPK_ARP_H

#include <avr/io.h>

#include "banepro_ipv4.h"
#include "ipk.h"
#include "ipk_config.h"

/* Return type for ARP lookup. */
enum ipk_arp_lu_ret_t {
	IPK_ARP_LU_RET_FOUND,
	IPK_ARP_LU_RET_WAITING_FOR_REPLY
};

/* ARP table record. */
struct ipk_arp_table_record {
	banepro_ipv4_addr ipv4_addr;	/* IPv4 address */
	banepro_eth_mac_addr mac_addr;	/* MAC address */
	uint8_t valid_age;		/* Valid bit (7) and age bits (6-0) */
};

/**
 * Initializes the ARP module (no lookup is done here).
 *
 * @param ipk_conf	ipkats configuration
 */
void ipk_arp_init(struct ipk_conf* ipk_conf);

/**
 * Performs an ARP lookup (will first look up the table, and then issue an
 * ARP request if nothing found).
 *
 * @param ipv4_addr	IPv4 address to look up
 * @param mac_addr	Resulting MAC address, if any
 * @param ipk_conf	ipkats configuration
 * @return		Return code
 */
enum ipk_arp_lu_ret_t ipk_arp_lookup(banepro_ipv4_addr ipv4_addr,
banepro_eth_mac_addr mac_addr, struct ipk_conf* ipk_conf);

#endif /* _IPK_ARP_H */
