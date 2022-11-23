/*
 *  Input Communication Header 
 *  Application layer
 */

#ifndef INPUT_COMM_H
#define	INPUT_COMM_H

#include "main_config.h"

void check_inputs(bms*);
void check_CAN(bms*);
void check_shutdown(bms*);
void check_balance(bms*);
void check_charge(bms*);
void check_discharge(bms*);
#endif	/* INPUT_COMM_H */

