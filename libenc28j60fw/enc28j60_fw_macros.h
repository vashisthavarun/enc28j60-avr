#ifndef _ENC28J60_FW_MACROS_H
#define _ENC28J60_FW_MACROS_H

#define ENC_BANK_OF(reg)	((reg >> ENC_REG_BANK_SHIFT) & 0x3)
#define ENC_HIGH(value16)	((value16 >> 8) & 0xff)
#define ENC_LOW(value16)	(value16 & 0xff)

#endif /* _ENC28J60_FW_MACROS_H */
