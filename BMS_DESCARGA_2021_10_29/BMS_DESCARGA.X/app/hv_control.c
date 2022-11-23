/*
 *  HV Control File
 *  Application layer
 */
#include "hv_control.h"
#include "dev/analog.h"

#include <stdbool.h>

/*Take HV measurements, update precharge status*/
void hv_monitoring(bms* bms){
    hv_measure(bms);
    current_measure(bms);
    error_hv_monitoring(bms);
    
    //Proceso Precarga
    if(bms->error0flag){
        bms->prechargeflag = false;
        bms->contador_precarga = 0;
    }else{
        
//          if(bms->contador_precarga < 10){
//              
//              bms->prechargeflag = true; 
//              bms->contador_precarga = bms->contador_precarga + 1; 
//              
//          }else{
//              
//              bms->prechargeflag = false; 
//             
//          };
          
          
        if(bms->hv_airs < (PRECHARGE_PERCENTAGE/100.0)*bms->hv_batt){
            bms->prechargeflag = true;  
        }else{
            bms->prechargeflag = false;  
        }
    }
    
}
/*Measure the voltage at both sides of the AIRs*/
void hv_measure(bms* bms){
    uint8_t i;    
    float suma_airs, suma_batt;
    
    bms->hv_batt = analog_hv_batt();
    bms->hv_airs = analog_hv_airs();
    
    if(bms->first_cycle){
        for(i = 0; i < HV_FILTER_SIZE - 1; i++){
           bms->hv_batt_vals[i] = bms->hv_batt;
        }  
        bms->first_cycle = 0;
    }else{
        for(i = 0; i < HV_FILTER_SIZE - 1; i++){
           bms->hv_batt_vals[i] = bms->hv_batt_vals[i+1];
        }        
    }
    if(bms->changed_mode){
        for(i = 0; i < HV_FILTER_SIZE - 1; i++){
           bms->hv_airs_vals[i] = bms->hv_airs;
        }        
    }else{
        for(i = 0; i < HV_FILTER_SIZE - 1; i++){
           bms->hv_airs_vals[i] = bms->hv_airs_vals[i+1];
        }      
    }

    bms->hv_airs_vals[HV_FILTER_SIZE - 1] = bms->hv_airs;
    bms->hv_batt_vals[HV_FILTER_SIZE - 1] = bms->hv_batt;
    
    suma_airs = 0;
    suma_batt = 0;
    for(i = 0; i < HV_FILTER_SIZE; i++){
        suma_airs = suma_airs + bms->hv_airs_vals[i];
        suma_batt = suma_batt + bms->hv_batt_vals[i];
    }
    bms->hv_batt = suma_batt/HV_FILTER_SIZE;
    bms->hv_airs = suma_airs/HV_FILTER_SIZE;
}
/*Measure the current from the Hall Sensor*/
void current_measure(bms* bms){
    /*if(bms->bms_mode == CHARGE){
        bms->current = -7;
    }
    else if(bms->bms_mode == DISCHARGE){
        bms->current = 55.0;
    }
    else{
        bms->current = 0.0;
    }*/
    bms->current = analog_hv_current();
    /*if(bms->bms_mode == ERROR || bms->bms_mode == STANDBY || bms->bms_mode == BALANCE){
        bms->current = 0;
    }else{
        if(bms->bms_mode == CHARGE){
            bms->current > 0 ? 0 : bms->current;
        }
        else if(bms->bms_mode == DISCHARGE){
            bms->current < 0 ? 0 : bms->current;
        }
    }
*/
}