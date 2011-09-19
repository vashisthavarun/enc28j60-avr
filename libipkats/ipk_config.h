#ifndef _IPK_CONFIG_H
#define _IPK_CONFIG_H

/* RX buffer size (TX buffer size will be (8 kiB - RX buffer size)). */
#define IPK_CFG_RX_BUFFER_SIZE		6144

/* Maximum packet size. */
#define IPK_CFG_MAX_PACKET_SIZE		500

/* ARP table size (number of records; at least 2). */
#define IPK_CFG_ARP_TABLE_SIZE		3

#endif /* _IPK_CONFIG_H */
