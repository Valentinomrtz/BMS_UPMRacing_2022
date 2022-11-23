/* 
 * Slave Comm Header
 * Application Layer
 */

#ifndef SLAVE_COMM_H
#define	SLAVE_COMM_H

#include "main_config.h"

void slave_monitoring(bms*);
void slave_init();
int8_t slave_config();
int8_t slave_cell_voltage_measurement();
int8_t slave_temperature_measurement();
int8_t slave_stat_measurement();
void slave_cell_balancing(int,int);
void slave_open_wire_check(bms*);
void slave_print_config();
void slave_print_rconfig();
#endif	/* SLAVE_COMM_H */

