/*
 *  Error Verification File
 *  Application layer
 */

#include "main_config.h"
#include "error_verification.h"

#include "dev/control.h"
#include "dev/serial.h"

/*Execute the error check functions*/
void error_verification(bms* bms){
    bms->error0count = 0;
    bms->error1count = 0;
    bms->error2count = 0;
    error_input_comm(bms);
    error_hv_monitoring(bms);
    error_hv_limits(bms);
    error_vcell_limits(bms);
    error_vcell_diff(bms);
    error_vstack_sum(bms);
    error_vbatt_sum(bms);
    error_tcell_limits(bms); //C: comentado para probar carga.
    error_tcell_diff(bms);
    error_current_limits(bms);
    error_ow_cells(bms);
    error_check_0(bms); 
    error_check_1(bms);
    error_check_2(bms);
}
/*Check input implausibilities for setting the BMS mode*/
void error_input_comm(bms* bms){
    if(bms->discharge&&bms->charge){
        bms->input_error_mode_imp = -1;
        bms->error0count++;
    }
    else{
        bms->input_error_mode_imp = 0; 
    }
}
/*Check if the AIRs voltage is higher than the battery voltage*/
void error_hv_monitoring(bms* bms){ 
    bms->hv_monitoring_error_imp = 0;
   
    if(bms->hv_airs - bms->hv_batt > 50 ){
        bms->hv_monitoring_error_imp = -1;
        bms->error0count++;
    }
    else{
        bms->hv_monitoring_error_imp = 0;
    }
     
}
/*Check if the battery voltage is between safe limits*/
void error_hv_limits(bms* bms){
    
    bms->hv_monitoring_error_high[0] = 0;
    bms->hv_monitoring_error_high[1] = 0;
    bms->hv_monitoring_error_high[2] = 0;
    
    if(bms->hv_batt > MAX_HV_VOLTAGE_0){
        bms->hv_monitoring_error_high[0] = -1;
        bms->error0count++;
    }
    else if(bms->hv_batt > MAX_HV_VOLTAGE_1){
        bms->hv_monitoring_error_high[1] = -1;
        bms->error1count++;
    }
    else if(bms->hv_batt > MAX_HV_VOLTAGE_2){
        bms->hv_monitoring_error_high[2] = -1;
        bms->error2count++;
    }
     
    bms->hv_monitoring_error_low[0] = 0;
    bms->hv_monitoring_error_low[1] = 0;
    bms->hv_monitoring_error_low[2] = 0;
    
    if(bms->hv_batt < MIN_HV_VOLTAGE_0){
        bms->hv_monitoring_error_low[0] = -1;
        bms->error0count++;
    }
    else if(bms->hv_batt < MIN_HV_VOLTAGE_1){
        bms->hv_monitoring_error_low[1] = -1;
        bms->error1count++;    
    }
    else if(bms->hv_batt < MIN_HV_VOLTAGE_2){
        bms->hv_monitoring_error_low[2] = -1;
        bms->error2count++;
    }
     
}
/*Check if each cell voltage is between safe limits*/
void error_vcell_limits(bms* bms){
    int i,j;
    bms->slave_vcell_error_high[0] = 0;
    bms->slave_vcell_error_high[1] = 0;
    bms->slave_vcell_error_high[2] = 0;
    bms->slave_vcell_error_low[0] = 0;
    bms->slave_vcell_error_low[1] = 0;
    bms->slave_vcell_error_low[2] = 0;
    for(i =0; i<N_SLAVES; ++i){
        for(j=0; j< N_CELLS - bms->maskcell[i]; ++j){
            if(bms->vcell[i][j]*0.1 > MAX_CELL_VOLTAGE_0){
                  bms->slave_vcell_error_high[0] += 1;
                  bms->error0count++;
            }
            else if(bms->vcell[i][j]*0.1 > MAX_CELL_VOLTAGE_1){
                 bms->slave_vcell_error_high[1] += 1;   
                 bms->error1count++;
                
            }
            else if(bms->vcell[i][j]*0.1 > MAX_CELL_VOLTAGE_2){
                    bms->slave_vcell_error_high[2] += 1;
                    bms->error2count++;
                
            }
            
            if(bms->vcell[i][j]*0.1 < MIN_CELL_VOLTAGE_0){
                    bms->slave_vcell_error_low[0] += 1;
                    bms->error0count++;
            }
            else if(bms->vcell[i][j]*0.1 < MIN_CELL_VOLTAGE_1){
                    bms->slave_vcell_error_low[1] += 1;
                    bms->error1count++;
            }
            else if(bms->vcell[i][j]*0.1 < MIN_CELL_VOLTAGE_2){
                bms->slave_vcell_error_low[2] += 1;
                bms->error2count++;
                
            }      
        }
    }
}
/*Check if the difference between the max and min cell voltage is safe*/
void error_vcell_diff(bms* bms){
    int i;
    bms->slave_vcell_error_diff[0] = 0;
    bms->slave_vcell_error_diff[1] = 0;
    bms->slave_vcell_error_diff[2] = 0;
    for(i =0; i< N_SLAVES; ++i){
        if((bms->vmax[i]-bms->vmin[i])*0.1 > MAX_CELL_DIFF_0){
            bms->slave_vcell_error_diff[0] += 1;
            bms->error0count++;
        }
        else if((bms->vmax[i]-bms->vmin[i])*0.1 > MAX_CELL_DIFF_1){
            bms->slave_vcell_error_diff[1] += 1;
            bms->error1count++;
        }
        else if((bms->vmax[i]-bms->vmin[i])*0.1 > MAX_CELL_DIFF_2){
            bms->slave_vcell_error_diff[2] += 1;
            bms->error2count++;
        }
    }
}
/*Check implausibilites between the stack voltage and the sum of cell voltages*/
void error_vstack_sum(bms* bms){
    int i,j;
    bms->slave_vcell_error_sum = 0;
    float vsum;
    for(i =0; i<N_SLAVES; ++i){
        vsum = 0;
        for(j=0; j< N_CELLS - bms->maskcell[i]; ++j){
            vsum += bms->vcell[i][j]*0.0001;
        }
        if(abs(bms->stats[i][0]-vsum) > MAX_STACK_VOLTAGE_IMP){
            bms->slave_vcell_error_sum += 1;
            bms->error0count++;
        }
    }
}
/*Check implausibilites between the battery voltage and the sum of stack voltages*/
void error_vbatt_sum(bms* bms){
    int i;
    float vsum = 0;
    bms->hv_monitoring_error_sum = 0;
    
    for(i =0; i< N_SLAVES; ++i){
        vsum += bms->stats[i][0];        
    }
    if(abs(bms->hv_batt-vsum) > MAX_HV_VOLTAGE_IMP){
        bms->hv_monitoring_error_sum = 1;
        bms->error0count++;
    }
    else{
        bms->hv_monitoring_error_sum = 0;
    }  
    
}
/*Check if each cell temperature is between safe limits*/
void error_tcell_limits(bms* bms){
    int i,j;
    bms->slave_tcell_error_high[0] = 0;
    bms->slave_tcell_error_high[1] = 0;
    bms->slave_tcell_error_high[2] = 0;
    bms->slave_tcell_error_low[0] = 0;
    bms->slave_tcell_error_low[1] = 0;
    bms->slave_tcell_error_low[2] = 0;
    for(i =0; i<N_SLAVES; ++i){ //C: comentado para probar carga
        for(j=0; j< N_NTCS; ++j){
            if(bms->tcell[i][j]>1.0*MAX_CELL_TEMP_0){
                bms->slave_tcell_error_high[0] += 1;
                bms->error0count++;
            } 
            else if(bms->tcell[i][j]>1.0*MAX_CELL_TEMP_1){
                bms->slave_tcell_error_high[1] += 1;
                bms->error1count++;
            } 
            else if(bms->tcell[i][j]>1.0*MAX_CELL_TEMP_2){
                bms->slave_tcell_error_high[2] += 1;
                bms->error2count++;
            }
            
            if(bms->tcell[i][j] < 1.0*MIN_CELL_TEMP_0){
                bms->slave_tcell_error_low[0] += 1;  
                bms->error0count++;
            }
            else if(bms->tcell[i][j] < 1.0*MIN_CELL_TEMP_1){
                bms->slave_tcell_error_low[1] += 1;     
                bms->error1count++;
            }
            else if(bms->tcell[i][j] < 1.0*MIN_CELL_TEMP_2){
                bms->slave_tcell_error_low[2] += 1;
                bms->error2count++;                
            }
        }
    }      
}
/*Check if the difference between the max and min cell temperature is safe*/
void error_tcell_diff(bms* bms){
    int i;
    bms->slave_tcell_error_diff[0] = 0;
    bms->slave_tcell_error_diff[1] = 0;
    bms->slave_tcell_error_diff[2] = 0;
    for(i =0; i< N_SLAVES; ++i){ //C: comentado para hacer cargar
        if(bms->tmax[i]-bms->tmin[i] > MAX_TEMP_DIFF_0){
            bms->slave_tcell_error_diff[0] += 1;
            bms->error0count++;
        }
        else if(bms->tmax[i]-bms->tmin[i] > MAX_TEMP_DIFF_1){
            bms->slave_tcell_error_diff[1] += 1;
            bms->error1count++;
        }
        else if(bms->tmax[i]-bms->tmin[i] > MAX_TEMP_DIFF_2){
            bms->slave_tcell_error_diff[2] += 1;
            bms->error2count++;
        }
    }   
}
/*Check if current is between safe limits, while charging or discharging*/
void error_current_limits(bms* bms){
    bms->hv_current_error_max[0] = 0;
    bms->hv_current_error_max[1] = 0; 
    bms->hv_current_error_max[2] = 0; 
    /*
    if(bms->bms_mode == CHARGE){
        if(-1*bms->current > MAX_CURRENT_CHARGE_0){
            bms->hv_current_error_max[0] = -1;
            bms->error0count++;
        }
        else if(-1*bms->current > MAX_CURRENT_CHARGE_1){
            bms->hv_current_error_max[1] = -1;
            bms->error1count++;
        }
        else if(-1*bms->current > MAX_CURRENT_CHARGE_2){
            bms->hv_current_error_max[2] = -1;
            bms->error2count++;
        }
    }
    else{
        if(bms->current > MAX_CURRENT_DISCHARGE_0){
            bms->hv_current_error_max[0] = -1;
            bms->error0count++;
            bms->hv_current_error_max[1] = -1;
            bms->error1count++;
        }
        else if(bms->current > MAX_CURRENT_DISCHARGE_1){
            bms->hv_current_error_max[1] = -1;
            bms->error1count++;
        }
        else if(bms->current > MAX_CURRENT_DISCHARGE_2){
            bms->hv_current_error_max[2] = -1;
            bms->error2count++;
        }
    }       
     */ 
       
    if((bms->current >=9 && bms->current <= 12) || (bms->current >= -2 && bms->current <=2)){
        bms->hv_current_error_max[0] = -1;
        bms->error0count++;
    }
}
/*Check if there are detected openwires*/
void error_ow_cells(bms* bms){
    int i,j;
    bms->slave_owcell_error = 0;
    for(i =0; i< N_SLAVES; ++i){
        for(j=0; j<N_CELLS - bms->maskcell[i]; ++j){
            if(bms->owcell[i][j] == 1){
                bms->slave_owcell_error += 1;
                bms->error0count++;
            }
        }
    }         
}
/*Signal the presence of active error 0 flags, change the mode to error*/
void error_check_0(bms* bms){ 
    bool boolerror = false; //(C)
    if(bms->input_error_mode_imp     !=0|| bms->slave_pec_error_config   !=0|| 
       bms->slave_pec_error_voltage  !=0|| bms->slave_pec_error_temp     !=0||
       bms->slave_pec_error_stat     !=0|| bms->slave_vcell_error_low[0] !=0||
       bms->slave_vcell_error_high[0]!=0|| bms->slave_vcell_error_sum    !=0||
       bms->slave_vcell_error_diff[0]!=0|| bms->slave_tcell_error_high[0]!=0||
       bms->slave_tcell_error_low[0] !=0|| bms->slave_tcell_error_diff[0]!=0||
       bms->slave_owcell_error       !=0|| bms->hv_monitoring_error_imp!=0||
       bms->hv_monitoring_error_high[0]!=0|| bms->hv_monitoring_error_low[0]!=0||
       bms->hv_monitoring_error_sum  !=0|| bms->hv_current_error_max[0]   !=0)
    {
        boolerror = true;
        if(bms->timererror >=1){
            bms->error0flag = true;
            bms->bms_mode = ERROR;
            control_bms_fault_set(); 
        }else{
            bms->timererror++;
            bms->error0flag = false; 
            control_bms_fault_clear();
        }
    }else{
        bms->error0flag = false; 
        control_bms_fault_clear();
    }  
    if(!boolerror){
        bms->timererror = 0;
    }
}
/*Signal the presence of active error 1 flags* Es un warning*/ 
void error_check_1(bms* bms){
    if(bms->slave_vcell_error_low[1] !=0|| bms->slave_vcell_error_high[1]!=0|| 
       bms->slave_vcell_error_diff[1]!=0|| bms->slave_tcell_error_high[1]!=0||
       bms->slave_tcell_error_low[1] !=0|| bms->slave_tcell_error_diff[1]!=0||
       bms->hv_monitoring_error_high[1]!=0||bms->hv_monitoring_error_low[1]!=0||
       bms->hv_current_error_max[1]   !=0)
    {
        bms->error1flag = true;
    }else{
        bms->error1flag = false; 
    }  
}
/*Signal the presence of active error 2 flags Es un Warning */
void error_check_2(bms* bms){
    if(bms->slave_vcell_error_low[2] !=0|| bms->slave_vcell_error_high[2]!=0|| 
       bms->slave_vcell_error_diff[2]!=0|| bms->slave_tcell_error_high[2]!=0||
       bms->slave_tcell_error_low[2] !=0|| bms->slave_tcell_error_diff[2]!=0||
       bms->hv_monitoring_error_high[2]!=0||bms->hv_monitoring_error_low[2]!=0||
       bms->hv_current_error_max[2]   !=0)
    {
        bms->error2flag = true;
    }else{
        bms->error2flag = false; 
    }  
}