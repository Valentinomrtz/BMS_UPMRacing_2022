/* 
 * CAN Header
 * Library Layer
 */

#ifndef CAN_H
#define	CAN_H

void can1_init();
void can2_init();
void can1_off();
void can2_off();
void can_mode_set(unsigned int, unsigned int);
void can1_send(unsigned int*);
void can2_send(unsigned int*);
void can1_receive(unsigned int*);
void can2_receive(unsigned int*);
#endif	/* CAN_H */

