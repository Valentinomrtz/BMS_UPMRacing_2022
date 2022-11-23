/* 
 * UART Header
 * Library Layer
 */

#ifndef UART_H
#define	UART_H

#include <stdint.h>

void uart_init();
void uart_interrupt_rx_set();
void uart_interrupt_rx_clear();
void uart_put(int8_t);
char uart_get();


#endif	/* UART_H */

