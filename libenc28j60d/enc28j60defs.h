#ifndef _ENC28J60DEFS_H
#define _ENC28J60DEFS_H

/*
 * SPI instructions definitions
 */

#define ENC_RCR_OP 0
#define ENC_RBM_OP 1
#define ENC_WCR_OP 2
#define ENC_WBM_OP 3
#define ENC_BFS_OP 4
#define ENC_BFC_OP 5
#define ENC_SC_OP 6

#define ENC_FUNNY_CONSTANT 0x1A
#define ENC_SC_CONSTANT 0x1F

/*
 * Register definitions
 */

/*
 * Control registers encoding:
 * tbbaaaaa
 * t : 1 if it is a MAC or MII register, 0 otherwise
 * bb : bank where the register is found
 * aaaaa : address of the register
 */

#define ENC_REG_TYPE_SHIFT 7
#define ENC_REG_TYPE_MASK (1 << ENC_REG_TYPE_SHIFT)
#define ENC_REG_BANK_SHIFT 5
 
/* General */
#define ENC_EIE		0x1B // 0 00 11011
#define ENC_EIR		0x1C // 0 00 11100
#define ENC_ESTAT	0x1D // 0 00 11101
#define ENC_ECON2	0x1E // 0 00 11110
#define ENC_ECON1	0x1F // 0 00 11111

/* Bank 0 */
#define ENC_ERDPTL	0x00 // 0 00 00000
#define ENC_ERDPTH	0x01 // 0 00 00001
#define ENC_EWRPTL	0x02 // 0 00 00010
#define ENC_EWRPTH	0x03 // 0 00 00011
#define ENC_ETXSTL	0x04 // 0 00 00100
#define ENC_ETXSTH	0x05 // 0 00 00101
#define ENC_ETXNDL	0x06 // 0 00 00110
#define ENC_ETXNDH	0x07 // 0 00 00111
#define ENC_ERXSTL	0x08 // 0 00 01000
#define ENC_ERXSTH	0x09 // 0 00 01001
#define ENC_ERXNDL	0x0A // 0 00 01010
#define ENC_ERXNDH	0x0B // 0 00 01011
#define ENC_ERXRDPTL	0x0C // 0 00 01100
#define ENC_ERXRDPTH	0x0D // 0 00 01101
#define ENC_ERXWRPTL	0x0E // 0 00 01110
#define ENC_ERXWRPTH	0x0F // 0 00 01111
#define ENC_EDMASTL	0x10 // 0 00 10000
#define ENC_EDMASTH	0x11 // 0 00 10001
#define ENC_EDMANDL	0x12 // 0 00 10010
#define ENC_EDMANDH	0x13 // 0 00 10011
#define ENC_EDMADSTL	0x14 // 0 00 10100
#define ENC_EDMADSTH	0x15 // 0 00 10101
#define ENC_EDMACSL	0x16 // 0 00 10110
#define ENC_EDMACSH	0x17 // 0 00 10111

/* Bank 1 */
#define ENC_EHT0	0x20 // 0 01 00000
#define ENC_EHT1	0x21 // 0 01 00001
#define ENC_EHT2	0x22 // 0 01 00010
#define ENC_EHT3	0x23 // 0 01 00011
#define ENC_EHT4	0x24 // 0 01 00100
#define ENC_EHT5	0x25 // 0 01 00101
#define ENC_EHT6	0x26 // 0 01 00110
#define ENC_EHT7	0x27 // 0 01 00111
#define ENC_EPMM0	0x28 // 0 01 01000
#define ENC_EPMM1	0x29 // 0 01 01001
#define ENC_EPMM2	0x2A // 0 01 01010
#define ENC_EPMM3	0x2B // 0 01 01011
#define ENC_EPMM4	0x2C // 0 01 01100
#define ENC_EPMM5	0x2D // 0 01 01101
#define ENC_EPMM6	0x2E // 0 01 01110
#define ENC_EPMM7	0x2F // 0 01 01111
#define ENC_EPMCSL	0x30 // 0 01 10000
#define ENC_EPMCSH	0x31 // 0 01 10001
#define ENC_EPMOL	0x34 // 0 01 10100
#define ENC_EPMOH	0x35 // 0 01 10101
#define ENC_EWOLIE	0x36 // 0 01 10110
#define ENC_EWOLIR	0x37 // 0 01 10111
#define ENC_ERXFCON	0x38 // 0 01 11000
#define ENC_EPKTCNT	0x39 // 0 01 11001

/* Bank 2 */
#define ENC_MACON1	0xC0 // 1 10 00000
#define ENC_MACON2	0xC1 // 1 10 00001
#define ENC_MACON3	0xC2 // 1 10 00010
#define ENC_MACON4	0xC3 // 1 10 00011
#define ENC_MABBIPG	0xC4 // 1 10 00100
#define ENC_MAIPGL	0xC6 // 1 10 00110
#define ENC_MAIPGH	0xC7 // 1 10 00111
#define ENC_MACLCON1	0xC8 // 1 10 01000
#define ENC_MACLCON2	0xC9 // 1 10 01001
#define ENC_MAMXFLL	0xCA // 1 10 01010
#define ENC_MAMXFLH	0xCB // 1 10 01011
#define ENC_MAPHSUP	0xCD // 1 10 01101
#define ENC_MICON	0xD1 // 1 10 10001
#define ENC_MICMD	0xD2 // 1 10 10010
#define ENC_MIREGADR	0xD4 // 1 10 10100
#define ENC_MIWRL	0xD6 // 1 10 10110
#define ENC_MIWRH	0xD7 // 1 10 10111
#define ENC_MIRDL	0xD8 // 1 10 11000
#define ENC_MIRDH	0xD9 // 1 10 11001

/* Bank 3 */
#define ENC_MAADR1	0xE0 // 1 11 00000
#define ENC_MAADR0	0xE1 // 1 11 00001
#define ENC_MAADR3	0xE2 // 1 11 00010
#define ENC_MAADR2	0xE3 // 1 11 00011
#define ENC_MAADR5	0xE4 // 1 11 00100
#define ENC_MAADR4	0xE5 // 1 11 00101
#define ENC_EBSTSD	0x66 // 0 11 00110
#define ENC_EBSTCON	0x67 // 0 11 00111
#define ENC_EBSTCSL	0x68 // 0 11 01000
#define ENC_EBSTCSH	0x69 // 0 11 01001
#define ENC_MISTAT	0xEA // 1 11 01010
#define ENC_EREVID	0x72 // 0 11 10010
#define ENC_ECOCON	0x75 // 0 11 10101
#define ENC_EFLOCON	0x77 // 0 11 10111
#define ENC_EPAUSL	0x78 // 0 11 11000
#define ENC_EPAUSH	0x79 // 0 11 11001

/*
 * PHY registers
 */
#define ENC_PHCON1	0x00
#define ENC_PHSTAT1	0x01
#define ENC_PHID1	0x02
#define ENC_PHID2	0x03
#define ENC_PHCON2	0x10
#define ENC_PHSTAT2	0x11
#define ENC_PHIE	0x12
#define ENC_PHIR	0x13
#define ENC_PHLCON	0x14

/*
 * Bit definitions
 */ 

/* EIE */
#define ENC_INTIE	7
#define ENC_PKTIE	6
#define ENC_DMAIE	5
#define ENC_LINKIE	4
#define ENC_TXIE	3
#define ENC_WOLIE	2
#define ENC_TXERIE	1
#define ENC_RXERIE	0

/* EIR */
#define ENC_PKTIF	6
#define ENC_DMAIF	5
#define ENC_LINKIF	4
#define ENC_TXIF	3
#define ENC_WOLIF	2
#define ENC_TXERIF	1
#define ENC_RXERIF	0

/* ESTAT */
#define ENC_INT		7
#define ENC_LATECOL	4
#define ENC_RXBUSY	2
#define ENC_TXABRT	1
#define ENC_CLKRDY	0

/* ECON2 */
#define ENC_AUTOINC	7
#define ENC_PKTDEC	6
#define ENC_PWRSV	5
#define ENC_VRPS	3

/* ECON1 */
#define ENC_TXRST	7
#define ENC_RXRST	6
#define ENC_DMAST	5
#define ENC_CSUMEN	4
#define ENC_TXRTS	3
#define ENC_RXEN	2
#define ENC_BSEL1	1
#define ENC_BSEL0	0

/* EWOLIE */
#define ENC_UCWOLIE	7
#define ENC_AWOLIE	6
#define ENC_PMWOLIE	4
#define ENC_MPWOLIE	3
#define ENC_HTWOLIE	2
#define ENC_MCWOLIE	1
#define ENC_BCWOLIE	0

/* EWOLIR */
#define ENC_UCWOLIF	7
#define ENC_AWOLIF	6
#define ENC_PMWOLIF	4
#define ENC_MPWOLIF	3
#define ENC_HTWOLIF	2
#define ENC_MCWOLIF	1
#define ENC_BCWOLIF	0

/* ERXFCON */
#define ENC_UCEN	7
#define ENC_ANDOR	6
#define ENC_CRCEN	5
#define ENC_PMEN	4
#define ENC_MPEN	3
#define ENC_HTEN	2
#define ENC_MCEN	1
#define ENC_BCEN	0

/* MACON1 */
#define ENC_LOOPBK	4
#define ENC_TXPAUS	3
#define ENC_RXPAUS	2
#define ENC_PASSALL	1
#define ENC_MARXEN	0

/* MACON2 */
#define ENC_MARST	7
#define ENC_RNDRST	6
#define ENC_MARXRST	3
#define ENC_RFUNRST	2
#define ENC_MATXRST	1
#define ENC_TFUNRST	0

/* MACON3 */
#define ENC_PADCFG2	7
#define ENC_PADCFG1	6
#define ENC_PADCFG0	5
#define ENC_TXCRCEN	4
#define ENC_PHDRLEN	3
#define ENC_HFRMEN	2
#define ENC_FRMLNEN	1
#define ENC_FULDPX	0

/* MACON4 */
#define ENC_DEFER	6
#define ENC_BPEN	5
#define ENC_NOBKOFF	4
#define ENC_LONGPRE	1
#define ENC_PUREPRE	0

/* MAPHSUP */
#define ENC_RSTINTFC	7
#define ENC_RSTRMII	3

/* MICON */
#define ENC_RSTMII	7

/* MICMD */
#define ENC_MIISCAN	1
#define ENC_MIIRD	0

/* EBSTCON */
#define ENC_PSV2	7
#define ENC_PSV1	6
#define ENC_PSV0	5
#define ENC_PSEL	4
#define ENC_TMSEL1	3
#define ENC_TMSEL0	2
#define ENC_TME		1
#define ENC_BISTST	0

/* MISTAT */
#define ENC_NVALID	2
#define ENC_SCAN	1
#define ENC_BUSY	0

/* ECOCON */
#define ENC_COCON2	2
#define ENC_COCON1	1
#define ENC_COCON0	0

/* EFLOCON */
#define ENC_FULDPXS	2
#define ENC_FCEN1	1
#define ENC_FCEN0	0

/* PHCON1 */
#define ENC_PRST	15
#define ENC_PLOOPBK	14
#define ENC_PPWRSV	11
#define ENC_PDPXMD	8

/* PHSTAT1 */
#define ENC_PFDPX	12
#define ENC_PHDPX	11
#define ENC_LLSTAT	2
#define ENC_JBSTAT	1

/* PHCON2 */
#define ENC_FRCLNK	14
#define ENC_TXDIS	13
#define ENC_JABBER	10
#define ENC_HDLDIS	8

/* PHSTAT2 */
#define ENC_TXSTAT	13
#define ENC_RXSTAT	12
#define ENC_COLSTAT	11
#define ENC_LSTAT	10
#define ENC_DPXSTAT	9
#define ENC_PLRITY	4

/* PHIE */
#define ENC_PLNKIE	4
#define ENC_PGEIE	1

/* PHIR */
#define ENC_PLNKIF	4
#define ENC_PGIF	2

/* PHLCON */
#define ENC_LACFG3	11
#define ENC_LACFG2	10
#define ENC_LACFG1	9
#define ENC_LACFG0	8
#define ENC_LBCFG3	7
#define ENC_LBCFG2	6
#define ENC_LBCFG1	5
#define ENC_LBCFG0	4
#define ENC_LFRQ1	3
#define ENC_LFRQ0	2
#define ENC_STRCH	1

#endif /* _ENC28J60DEFS_H */
