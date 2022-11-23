/* 
 * Time Header
 * Device Layer
 */

#ifndef TIME_H
#define	TIME_H

#include <stdint.h>

void time_init();
void time_delay(int c,int time_ms);
void time_delay_u(int c, int time_us);
void time_interrupt_set(int,int);
void time_interrupt_disable(int);
int time_interrupt_1();
int time_interrupt_2();
#endif	/* TIME_H */

