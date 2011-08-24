#ifndef _ARP_H
#define _ARP_H

#include <avr/io.h>

/* Maximum hardware/protocol address length in ARP packets (bytes) */
#define PROTO_ARP_MAX_ADDR_LEN		8

/* Hardware types definitions */
#define PROTO_ARP_HWTYPE_UNKNOWN	0
#define PROTO_ARP_HWTYPE_ETH		1

/* Protocol types definitions */
#define PROTO_ARP_PTYPE_UNKNOWN		0
#define PROTO_ARP_PTYPE_IP		1

/* ARP operations definitions */
#define PROTO_ARP_OP_UNKNOWN		0
#define PROTO_ARP_OP_REQUEST		1
#define PROTO_ARP_OP_REPLY		2

/* Information structure for ARP */
struct proto_arp_info {
	uint8_t is_valid;			/* 1 if structure is valid */
	uint8_t hw_type;			/* hardware type */
	uint8_t proto_type;			/* protocol type */
	uint8_t hw_addr_len;			/* hardware address length */
	uint8_t proto_addr_len;			/* protocol address length */
	uint8_t op;				/* ARP operation */
	uint8_t sha [PROTO_ARP_MAX_ADDR_LEN];	/* source hardware address */
	uint8_t spa [PROTO_ARP_MAX_ADDR_LEN];	/* source protocol address */
	uint8_t tha [PROTO_ARP_MAX_ADDR_LEN];	/* target hardware address */
	uint8_t tpa [PROTO_ARP_MAX_ADDR_LEN];	/* target protocol address */
};

/**
 * Analyses an ARP packet and gives information about it.
 *
 * @param packet	ARP packet (pointing to first byte of hardware type)
 * @param info		Information structure to be filled
 */
void proto_arp_analyse(uint8_t* packet, struct proto_arp_info* info);

/**
 * In-place ARP reply.
 *
 * @param info		Information structure (valid, ARP analysis result)
 * @param my_hw_addr	Hardware address to reply with
 */
void proto_arp_inplace_reply(struct proto_arp_info* info, uint8_t* my_hw_addr);

/**
 * Formats an ARP packet using an information structure.
 *
 * @param info		Information structure
 * @param buf		Buffer where to put formatted packet (big enough)
 * @return		Formatted packet length
 */
uint8_t proto_arp_format_packet(struct proto_arp_info* info, uint8_t* buf);

#endif /* _ARP_H */
