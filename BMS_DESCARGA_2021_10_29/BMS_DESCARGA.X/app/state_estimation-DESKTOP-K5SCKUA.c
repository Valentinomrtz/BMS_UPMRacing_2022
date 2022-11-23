/*
 *  State Estimation File
 *  Application layer
 */

#include "state_estimation.h"
#include "interrupts.h"
#include "dev/time.h"

extern volatile int internal_time;

void state_init(){
    internal_time = 0;
    time_interrupt_set(2,1);    
}
void load_state(bms* bms){
    
    
    
    
}
void save_state(bms* bms){
    //while(internal_time < MAX_LOOP_TIME);
    bms->loop_time = internal_time;
    internal_time = 0;
}
void update_SOC(bms* bms){
    //TO DO
}
