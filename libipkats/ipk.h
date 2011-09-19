#ifndef _IPK_H
#define _IPK_H

#include <avr/io.h>

#include "banepro_ethernet.h"
#include "banepro_ipv4.h"

/* Init. options. */
#define IPK_INIT_OPT_COPY_CONF		1	/* Copy configuration struct. */

/* Return type for RX handler. */
enum ipk_rx_handler_ret_t {
	IPK_RXH_RET_OK,
	IPK_RXH_RET_EMPTY
};

/* ipkats callback function types. */
typedef void (* ipk_udp_cb_t)(void*);
typedef void (* ipk_send_cb_t)(void*);
typedef void (* ipk_rx_error_cb_t)(void*);

/* Configuration structure for ipkats. */
struct ipk_conf {
	banepro_eth_mac_addr mac_address;	/* MAC address */
	banepro_ipv4_addr ipv4_address;		/* device IPv4 address */
	banepro_ipv4_addr subnet_mask;		/* subnet mask */
	banepro_ipv4_addr gateway_addr;		/* default gateway IPv4 addr. */
	ipk_udp_cb_t udp_cb;				/* UDP callback */
	void* udp_cb_param;				/* UDP CB param. */
	ipk_send_cb_t send_cb;				/* Send callback */
	void* send_cb_param;				/* Send CB param. */
	ipk_rx_error_cb_t rx_error_cb;			/* Lost packet CB */
	void* rx_error_cb_param;			/* RX error CB param. */
};

/**
 * Initializes ipkats (thus initializing the ENC28J60.
 *
 * @param ipk_conf	ipkats configuration structure (properly filled)
 * @param options	Bitwise OR options (0 if none)
 * @return		0 if okay, > 0 otherwise
 */
uint8_t ipk_init(struct ipk_conf* ipk_conf, uint8_t options);

#endif /* _IPK_H */
