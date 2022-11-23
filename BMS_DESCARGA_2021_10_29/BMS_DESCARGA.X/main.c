/* 
 * BMS Test v1.0
 * Main layer
 */
#define _SUPPRESS_PLIB_WARNING

#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>
#include <plib.h>

#include "app/main_config.h"

int main(int argc, char** argv) {
    // System Initialization
    bms bms_master; 
    initialize_system(&bms_master);
    charge_init(&bms_master);
    int i = 0;//variable que dice cuando ejecutar un envio de CAN u otro
    bms_master.num_cycles = 0;
    while(1){
        check_inputs(&bms_master);
        select_mode(&bms_master);
        hv_monitoring(&bms_master);
        slave_monitoring(&bms_master);
        error_verification(&bms_master);
        relay_control(&bms_master);
        fan_control(&bms_master);
        can_comm_charge(&bms_master);
        can_comm_cell_info(&bms_master);
        balance_control(&bms_master);
        led_control(&bms_master);
        can_comm_cell_variation (&bms_master);
        if(bms_master.can_flag){
            can_comm_v(&bms_master);
            can_comm_t(&bms_master);
            bms_master.can_flag = false;
        }else{
            can_comm_info_main(&bms_master);
            can_comm_overall_main(&bms_master);
            bms_master.can_flag = true;
        }
        
        
        save_state(&bms_master);
        //pc_comm(&bms_master);
        bms_master.num_cycles += 1;
        //time_delay(1,100);
    }
    return (EXIT_SUCCESS);
}