/* 
 * Relay Control Header
 * Application Layer
 */

#include "cooling_control.h"
#include "dev/control.h"

/*Check cell temperatures and activate the fans accordingly */
void fan_control(bms* bms){
    int i,j,w,k;
    
    int fan;
    float temp;
    
    for(i=0; i < N_STACKS/2; ++i){
        fan = 0;
        for(w = 2*i; w < 2+2*i; ++w){
            for(j=0; j < SLAVES_PER_STACK; ++j){
                for(k=0; k<N_NTCS; ++k){
                      if(bms->tcell[bms->mstack[w][j]][k] > 1.0*MAX_CELL_TEMP_FANS){
                          fan = 1;
                      }  
                }
            }
        }
        switch(i){
            case 0:
                if(fan != 0){
                    control_fan_close(1);bms->fan1 = ON;
                }
                else{
                    control_fan_open(1);bms->fan1 = OFF;
                }
                break;
            case 1:
                if(fan != 0){
                    control_fan_close(2);bms->fan2 = ON;
                }
                else{
                    control_fan_open(2);bms->fan2 = OFF;
                }
                break;
            case 2:
                if(fan != 0){
                    control_fan_close(3);bms->fan3 = ON;
                }
                else{
                    control_fan_open(3);bms->fan3 = OFF;
                }
                break;
        }

    }
}