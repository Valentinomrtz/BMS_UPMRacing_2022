/*
 *  Mode Control File
 *  Application layer
 */

#include "mode_control.h"

/*Decide which mode to use depending on the input signals */
void select_mode(bms* bms){
    bms->changed_mode = 0;
    if(bms->error0flag){
        set_mode(bms,ERROR);
    }
    else{
        if(bms->shutdown){
            if(bms->discharge){
                if(bms->bms_mode == STANDBY){
                    bms->changed_mode = 1;
                }
                set_mode(bms,DISCHARGE);
            }else if(bms->charge){
                if(bms->balance){
                    set_mode(bms,BALANCE);
                }else{
                    if(bms->bms_mode == STANDBY){
                       
                        bms->changed_mode = 1;
                    }                
                    set_mode(bms,CHARGE);
                }
            }else{
                if(bms->bms_mode == CHARGE || bms->bms_mode == DISCHARGE ){
                    bms->changed_mode = 1;
                } 
                set_mode(bms,STANDBY);                
            }
        }
        else{
            if(bms->bms_mode == CHARGE || bms->bms_mode == DISCHARGE ){
                bms->changed_mode = 1;
            }             
            set_mode(bms,STANDBY);
        }
    }  
}
/*Set the BMS mode*/
void set_mode(bms* bms, mode mode){
    bms->bms_mode = mode;   
}