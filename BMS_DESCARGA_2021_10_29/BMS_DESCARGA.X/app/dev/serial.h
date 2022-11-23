/* 
 * Serial Header
 * Device layer
 */

#ifndef SERIAL_H
#define	SERIAL_H

void serial_init();
void serial_print(char* s);
void serial_printd(double s);
void serial_printf(float s);
void serial_printhex(int b);
void serial_printbytes(uint8_t* bytes, uint8_t len);
void serial_scan(char* s);
void serial_interrupt(char* s);

#endif	/* SERIAL_H */

