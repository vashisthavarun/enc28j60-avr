#ifndef _ICMP_H
#define _ICMP_H

#include <avr/io.h>

/* IP transport protocols */
#define PROTO_ICMP_TYPE_UNKNOWN		0
#define PROTO_ICMP_TYPE_ECHO_REPLY	1
#define PROTO_ICMP_TYPE_ECHO_REQUEST	2

/* ICMP header quench */
typedef uint8_t proto_icmp_quench [4];

/* Information structure for ICMP */
struct proto_icmp_info {
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	proto_icmp_quench quench;
};

/**
 * Analyses an ICMP packet and gives information about it.
 *
 * @param packet	ICMP packet (pointing to type)
 * @param info		Information structure to be filled
 */
void proto_icmp_analyse(uint8_t* packet, struct proto_icmp_info* info);

/**
 * Formats an ICMP packet header using an information structure.
 *
 * @param info		Information structure (set checksum to 0 for it to
 *			be autocomputed - data and data_len can be NULL and 0)
 * @param buf		Buffer where to put formatted packet header (big enough)
 * @param data		Data so the checksum can be computed
 * @param data_len	Length of data (bytes)
 * @return		Formatted packet header length (0 if error)
 */
uint8_t proto_icmp_format_header(struct proto_icmp_info* info, uint8_t* buf,
uint8_t* data, uint16_t data_len);

#endif /* _ICMP_H */
