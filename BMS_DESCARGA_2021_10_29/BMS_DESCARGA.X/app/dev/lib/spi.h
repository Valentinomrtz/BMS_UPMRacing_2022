/* 
 * SPI Header
 * Library Layer
 */

#ifndef SPI_H
#define	SPI_H

#include <stdint.h>

void spi_init();
uint8_t spi_transfer(uint8_t);
void spi_csb_set();
void spi_csb_clear();

uint8_t spi_read();
void spi_write(uint8_t);
void spi_read_array(uint8_t *, uint8_t);
void spi_write_array(uint8_t [], uint8_t);
void spi_write_read(uint8_t [], uint8_t, uint8_t *, uint8_t);
#endif	/* SPI_H */

