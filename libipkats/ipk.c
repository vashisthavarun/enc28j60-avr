#include <avr/io.h>
#include <string.h>

#include "banepro_ethernet.h"
#include "banepro_arp.h"
#include "banepro_ipv4.h"
#include "banepro_icmp.h"
#include "enc28j60_fw.h"
#include "ipk.h"
#include "ipk_config.h"

/* Saved instance configuration. */
static struct ipk_conf* g_ipk_conf = NULL;

uint8_t ipk_init(struct ipk_conf* ipk_conf, uint8_t options) {
	/* save configuration */
	if (options & IPK_INIT_OPT_COPY_CONF) {
		memcpy(&g_ipk_conf, ipk_conf, sizeof(g_ipk_conf));
	} else {
		g_ipk_conf = ipk_conf;
	}
	
	/* initialize the device */
	e28j60fw_easy_init(g_ipk_conf->mac_address, IPK_CFG_MAX_PACKET_SIZE,
		IPK_CFG_RX_BUFFER_SIZE);
	
	return 0;
}
