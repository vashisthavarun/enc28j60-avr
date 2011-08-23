#ifndef _ENC28J60_DRIVER_H
#define _ENC28J60_DRIVER_H

#include <avr/io.h>

#include "enc28j60defs.h"

#define ENC_DDR		DDRB
#define ENC_PORT	PORTB
#define ENC_PIN		PINB
#define ENC_CS		4
#define ENC_MOSI	5
#define ENC_MISO	6
#define ENC_SCK		7

#ifdef __cplusplus
extern "C" {
#endif

void enc_init();
uint8_t enc_rcr(uint8_t reg);
void enc_rbm_cont(uint8_t* values, const uint8_t n);
uint8_t enc_rbm();
void enc_wcr(uint8_t reg, uint8_t value);
void enc_wbm_cont(uint8_t* values, const uint8_t n);
void enc_wbm(uint8_t value);
void enc_bfs(uint8_t reg, uint8_t or_mask);
void enc_bfc(uint8_t reg, uint8_t inv_and_mask);
void enc_sc();

#ifdef __cplusplus
}
#endif

#endif /* _ENC28J60_DRIVER_H */
