#ifndef _ENC28J60_FW_MACROS_H
#define _ENC28J60_FW_MACROS_H

#include "enc28j60defs.h"

#define E28J60FW_BANK_OF(reg)	((reg >> E28J60_REG_BANK_SHIFT) & 0x3)
#define E28J60FW_HIGH(value16)	((value16 >> 8) & 0xff)
#define E28J60FW_LOW(value16)	(value16 & 0xff)

#endif /* _ENC28J60_FW_MACROS_H */
