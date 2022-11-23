/* 
 * State Estimation Header
 * Application Layer
 */

#ifndef STATE_ESTIMATION_H
#define	STATE_ESTIMATION_H

#include "main_config.h"
#include <stdbool.h>
void state_init();
void load_state(bms* bms);
void save_state(bms* bms);
void update_SOC(bms* bms);
#endif	/* STATE_ESTIMATION_H */

