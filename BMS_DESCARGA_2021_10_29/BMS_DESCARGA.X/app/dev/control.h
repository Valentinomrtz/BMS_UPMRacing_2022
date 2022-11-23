/* 
 * File:   control.h
 * Author: Usuario
 *
 * Created on 19 de marzo de 2020, 19:43
 */

#ifndef CONTROL_H
#define	CONTROL_H

#include <stdint.h>

typedef enum{AIR_POS,AIR_NEG,AIR_PRECH} relay;
typedef enum{SHTDWN, BAL, CH, DISCH} ctrlsignal;

void control_init();
void control_relay_open(relay c);
void control_relay_close(relay c);
void control_fan_open(int c);
void control_fan_close(int c);
void control_bms_fault_clear();
void control_bms_fault_set();
uint8_t  control_signal_read(ctrlsignal s);
void control_signal_interrupt();
#endif	/* CONTROL_H */

