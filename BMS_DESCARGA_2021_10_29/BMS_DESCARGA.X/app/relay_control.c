/* 
 * Relay Control Header
 * Application Layer
 */

#include "relay_control.h"

#include "dev/control.h"


/*Verify the mode, the precharge flag and the erros, decide which relays to open or close*/
void relay_control(bms* bms){
    if(bms->bms_mode == DISCHARGE ){

        control_relay_close(AIR_NEG);
        bms->air_neg = ON;
        
        if(bms->prechargeflag){
            control_relay_close(AIR_PRECH);
            control_relay_open(AIR_POS);
            bms->air_prech = ON;
            bms->air_pos = OFF;
        }
        else{
            control_relay_close(AIR_POS);
            bms->air_pos = ON;
            time_delay(1,50);
            

            control_relay_open(AIR_PRECH);
            bms->air_prech = OFF;            
        }
    }
    else if(bms->bms_mode == CHARGE && bms->charge_flag){
        control_relay_close(AIR_POS);
        bms->air_pos = ON;
        control_relay_close(AIR_NEG);
        bms->air_neg = ON;
    }else{
        control_relay_open(AIR_POS);
        bms->air_pos = OFF;
        control_relay_open(AIR_NEG);
        bms->air_neg = OFF;
        control_relay_open(AIR_PRECH); 
        bms->air_prech = OFF;                     
    }  
    //bms->air_pos = OFF;  bms->air_prech = OFF;
    //control_relay_close(AIR_NEG);   bms->air_neg = ON;
    //control_relay_close(AIR_PRECH); bms->air_prech = ON;
}