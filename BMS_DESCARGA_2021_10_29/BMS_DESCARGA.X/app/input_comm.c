/*
 *  Input Communication File
 *  Application layer
 */

#include "input_comm.h"

#include "dev/control.h"
#include <stdlib.h>
#include <stdio.h>

/* Check the main control inputs*/
void check_inputs(bms* bms){
    check_shutdown(bms);
    check_balance(bms);
    check_charge(bms);
    check_discharge(bms);
}

/* Check the received CAN messages*/
void check_CAN(bms* bms){
    //TO DO    
}

/* Check the input Shutdown signal*/
void check_shutdown(bms* bms){
    bms->shutdown = (control_signal_read(SHTDWN)!=0);      
}

/* Check the input Balance signal*/
void check_balance(bms* bms){
    bms->balance = (control_signal_read(BAL)!=0);     
}

/* Check the input Charge signal*/
void check_charge(bms* bms){
    bms->charge =   (control_signal_read(CH)!=0);    
}

/* Check the input Discharge signal*/
void check_discharge(bms* bms){
    bms->discharge =(control_signal_read(DISCH)!=0);   
}
