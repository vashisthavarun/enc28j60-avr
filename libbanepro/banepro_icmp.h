#ifndef _BANEPRO_ICMP_H
#define _BANEPRO_ICMP_H

#include <avr/io.h>

#include "banepro_config.h"

#if BANEPRO_ENABLE_ICMP

/* IP transport protocols (our own definitions) */
#define BANEPRO_ICMP_TYPE_UNKNOWN		0
#define BANEPRO_ICMP_TYPE_ECHO_REPLY		1
#define BANEPRO_ICMP_TYPE_ECHO_REQUEST		2

/* ICMP header quench type */
typedef uint8_t banepro_icmp_quench [4];

/* Information structure for ICMP */
struct banepro_icmp_info {
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	banepro_icmp_quench quench;
};

/**
 * Analyses an ICMP packet and gives information about it.
 *
 * @param packet	ICMP packet (pointing to type)
 * @param info		Information structure to be filled
 */
void banepro_icmp_analyse(uint8_t* packet, struct banepro_icmp_info* info);

/**
 * Formats an ICMP packet header using an information structure.
 *
 * @param info		Information structure
 * @param buf		Buffer where to put formatted packet header (big enough)
 * @param compute_chk	1 to compute checksum, else data and data_len may be 0
 * @param data		Data so the checksum can be computed
 * @param data_len	Length of data (bytes)
 * @return		Formatted packet header length (0 if error)
 */
uint8_t banepro_icmp_format_header(struct banepro_icmp_info* info,
uint8_t* buf, uint8_t compute_chk, uint8_t* data, uint16_t data_len);

#endif /* BANEPRO_ENABLE_ICMP */

#endif /* _BANEPRO_ICMP_H */
