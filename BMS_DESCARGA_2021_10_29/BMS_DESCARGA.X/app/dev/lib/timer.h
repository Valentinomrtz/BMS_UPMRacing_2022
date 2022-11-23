/* 
 * Timer Header
 * Library Layer
 */

#ifndef TIMER_H
#define	TIMER_H

void timer1_init();
void timer2_init();
void timer1_set();
void timer2_set();
int  timer1_check();
int  timer2_check();
void timer1_interrupt_set();
void timer2_interrupt_set();
void timer1_interrupt_clear();
void timer2_interrupt_clear();
void timer1_interrupt_disable();
void timer2_interrupt_disable();

#endif	/* TIMER_H */

