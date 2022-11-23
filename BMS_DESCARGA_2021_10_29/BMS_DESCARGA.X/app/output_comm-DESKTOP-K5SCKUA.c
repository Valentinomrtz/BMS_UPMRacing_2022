/*
 *  Output Communication File 
 *  Application layer
 */

#include "output_comm.h"
#include "dev/serial.h"
#include "dev/canlib.h"
#include "slave_comm.h"
#include "main_config.h"
#include "dev/time.h"
#include <stdio.h>
#define AUX_SIZE 256

/*Control the output LEDs depending on the BMS mode*/
void led_control(bms* bms){
    switch(bms->bms_mode){
        case ERROR:
            led_off(3);
            led_on(4);
            break;
        case CHARGE:
            led_on(3);
            led_on(4);
            break;
        case BALANCE:
            led_on(3);
            led_on(4);
            break;
        case DISCHARGE:
            led_on(3);
            led_off(4);
            break;
        case STANDBY:
            led_off(3);
            led_off(4);            
        break;         
    }  
}
/*Send information to the PC terminal by calling the different display functions*/
void pc_comm(bms* bms){
#ifdef GUI
    gui_comm(bms);
#else
    signal_status(bms);
    mode_status(bms);
    hv_status(bms);
    slaves_status(bms);
    error_0_status(bms);
    error_1_status(bms);
    error_2_status(bms);
    relay_status(bms);
    cooling_status(bms);
    balance_status(bms);
    can_status(bms);        
#endif
}
/*Send information to the CAN bus*/
void can_comm(bms* bms){
    char aux[AUX_SIZE];
    //unsigned int data[4] = {bms->vcell[0][0], bms->vcell[0][1], bms->vcell[0][2], bms->vcell[0][3]};
    //can_send_msg(0x0, 0x0, data);
   
    can_comm_cellv(bms);
    can_comm_cellt(bms);
     
     
    
    
}
/*Display the Input signals values*/
void signal_status(bms* bms){
    char aux[AUX_SIZE];
    serial_print("=================================================\r\n");
    sprintf(aux, "BMS PROTOTYPE V1.5 Loop time: %u ms\r\n", bms->loop_time);
    serial_print(aux);
    sprintf(aux,"INPUT SIGNALS: SHUTDOWN: %s BALANCE: %s CHARGE: %s DISCHARGE: %s\r\n",
            bms->shutdown?"ON":"OFF",bms->balance?"ON":"OFF",
            bms->charge?"ON":"OFF",bms->discharge?"ON":"OFF");
    serial_print(aux);   
}
/*Display the current BMS Mode*/
void mode_status(bms* bms){
    char aux[AUX_SIZE];
    switch(bms->bms_mode){
        case STANDBY:
            sprintf(aux,"STANDBY MODE\r\n");
        break;
        case CHARGE:
            sprintf(aux,"CHARGE MODE\r\n");        
        break;
        case DISCHARGE:
            sprintf(aux,"DISCHARGE MODE\r\n");        
        break;
        case ERROR:
            sprintf(aux,"ERROR MODE\r\n");           
        break;
        case BALANCE:
            sprintf(aux,"BALANCE MODE\r\n");          
        break;
        case MAINTENANCE:
            sprintf(aux,"MAINTENANCE MODE\r\n");          
        break;
    } 
    serial_print(aux);
}
/*Display the HV measurements*/
void hv_status(bms* bms){
    char aux[AUX_SIZE];
    sprintf(aux,"HV MEASUREMENTS: HV_BATT: %1.1f V HV_AIRS: %1.1f V CURRENT: %1.2f A\r\n",
            bms->hv_batt, bms->hv_airs, bms->current);
    serial_print(aux);
}
/*Display the Slaves information: voltage, temperature, stats and open wires*/
void slaves_status(bms* bms){
    char aux[AUX_SIZE];
    int i,j;
    serial_print("SLAVE MEASUREMENTS:\r\n");
    slave_print_config();
    slave_print_rconfig();
    serial_print("CELL VOLTAGE:\r\n");
    for(i=0; i< N_SLAVES; ++i){
        sprintf(aux, "SLAVE %i\r\n", i+1);serial_print(aux);
        for(j =0; j<N_CELLS - bms->maskcell[i]; ++j){
            sprintf(aux,"C%i: %1.4f V ",j+1,bms->vcell[i][j]*0.0001);serial_print(aux);
        }
        sprintf(aux,"\r\nVmax: %1.4f V Vmean: %1.4f V Vmin: %1.4f V Vdiff: %1.4f ", 
                bms->vmax[i]*0.0001, bms->vmean[i]*0.0001, bms->vmin[i]*0.0001, (bms->vmax[i]-bms->vmin[i])*0.0001);
        serial_print(aux);
        serial_print("\r\n");
    }
    serial_print("CELL TEMPERATURE:\r\n");
    for(i=0; i< N_SLAVES; ++i){
        sprintf(aux, "SLAVE %i\r\n", i+1);serial_print(aux);
        for(j =0; j<N_NTCS; ++j){
            sprintf(aux,"T%i: %1.2f C ",j+1, bms->tcell[i][j]);serial_print(aux);
        }
        sprintf(aux,"Vref2: %1.4f V ", bms->tcell[i][N_NTCS]);
        serial_print(aux);
        sprintf(aux,"Tmax: %1.2f C Tmean: %1.2f C Tmin: %1.2f C ", 
            bms->tmax[i], bms->tmean[i], bms->tmin[i]);
        serial_print(aux);
        serial_print("\r\n");
    }
    serial_print("STATS:\r\n");
    sprintf(aux,"STACK 1\r\n");serial_print(aux);
    sprintf(aux,"SOC: %1.4f V\r\n", bms->vstack[0]);serial_print(aux);
    for(i=0; i< N_SLAVES; ++i){
        sprintf(aux,"SLAVE %i\r\n", i+1);serial_print(aux);
        sprintf(aux,"SOC: %1.4f V ",bms->stats[i][0]);serial_print(aux);      
        sprintf(aux,"ITemp: %.2f C ",bms->stats[i][1]);serial_print(aux);
        sprintf(aux,"VregA: %1.4f V ",bms->stats[i][2]);serial_print(aux);
        sprintf(aux,"VregD: %1.4f V ",bms->stats[i][3]);serial_print(aux);
        serial_print("\r\n");
    }
    serial_print("OPEN WIRES:\r\n");
    for(i=0; i< N_SLAVES; ++i){
       sprintf(aux, "SLAVE %i: ", i+1);serial_print(aux);
        for(j=0; j< N_CELLS - bms->maskcell[i]; ++j){
            if(bms->owcell[i][j] == 1){
                sprintf(aux, "%i ", j+1);
                serial_print(aux);                
            }            
        }
       serial_print("\r\n");
    }
}
/*Display the active errors*/
void error_0_status(bms* bms){
    char aux[AUX_SIZE];
    sprintf(aux,"ERRORS: %i\r\n", bms->error0count);serial_print(aux);    
    if(bms->input_error_mode_imp!=0){serial_print("Modes Implausibility Error\r\n");}
    if(bms->slave_pec_error_config!=0){serial_print("Slave PEC Config Error\r\n");}
    if(bms->slave_pec_error_voltage!=0){serial_print("Slave PEC Voltage Error\r\n");}
    else{
        if(bms->slave_vcell_error_low[0]!=0){serial_print("Slave Low Voltage Error\r\n");}
        if(bms->slave_vcell_error_high[0]!=0){serial_print("Slave High Voltage Error\r\n");}
        if(bms->slave_vcell_error_sum!=0){serial_print("Slave Voltage Sum Error\r\n");}
        if(bms->slave_vcell_error_diff[0]!=0){serial_print("Slave Voltage Difference Error\r\n");}
        if(bms->slave_owcell_error!=0){serial_print("Slave Open Wire Error\r\n");}        
    }
    if(bms->slave_pec_error_temp!=0){serial_print("Slave PEC Temperature Error\r\n");}
    else{
        if(bms->slave_tcell_error_high[0]!=0){serial_print("Slave High Temperature Error\r\n");}
        if(bms->slave_tcell_error_low[0]!=0){serial_print("Slave Low Temperature Error\r\n");}
        if(bms->slave_tcell_error_diff[0]!=0){serial_print("Slave Temperature Difference Error\r\n");}        
    }
    if(bms->slave_pec_error_stat!=0){serial_print("Slave PEC Stats Error\r\n");}
    if(bms->hv_monitoring_error_imp!=0){serial_print("HV Implausibility Error\r\n");}
    if(bms->hv_monitoring_error_high[0]!=0){serial_print("HV High Voltage Error\r\n");}
    if(bms->hv_monitoring_error_low[0]!=0){serial_print("HV Low Voltage Error\r\n");}
    if(bms->hv_monitoring_error_sum!=0){serial_print("HV Voltage Sum Error\r\n");}
    if(bms->hv_current_error_max[0] !=0){serial_print("HV Current Error\r\n");}    
}
/*Display the active alarms 1*/
void error_1_status(bms* bms){
    char aux[AUX_SIZE];
    sprintf(aux,"ALARMS 1: %i\r\n", bms->error1count);serial_print(aux); 
    if(bms->slave_vcell_error_low[1]!=0){serial_print("Slave Low Voltage Alarm 1\r\n");}
    if(bms->slave_vcell_error_high[1]!=0){serial_print("Slave High Voltage Alarm 1\r\n");}
    if(bms->slave_vcell_error_diff[1]!=0){serial_print("Slave Voltage Difference Alarm 1\r\n");}
    if(bms->slave_tcell_error_high[1]!=0){serial_print("Slave High Temperature Alarm 1\r\n");}
    if(bms->slave_tcell_error_low[1]!=0){serial_print("Slave Low Temperature Alarm 1\r\n");}
    if(bms->slave_tcell_error_diff[1]!=0){serial_print("Slave Temperature Difference Alarm 1\r\n");}
    if(bms->hv_monitoring_error_high[1]!=0){serial_print("HV High Voltage Alarm 1\r\n");}
    if(bms->hv_monitoring_error_low[1]!=0){serial_print("HV Low Voltage Alarm 1\r\n");}
    if(bms->hv_current_error_max[1] !=0){serial_print("HV Current Alarm 1\r\n");}     
}
/*Display the active alarms 2*/
void error_2_status(bms* bms){
    char aux[AUX_SIZE];
    sprintf(aux,"ALARMS 2: %i\r\n", bms->error2count);serial_print(aux);     
    if(bms->slave_vcell_error_low[2]!=0){serial_print("Slave Low Voltage Alarm 2\r\n");}
    if(bms->slave_vcell_error_high[2]!=0){serial_print("Slave High Voltage Alarm 2\r\n");}
    if(bms->slave_vcell_error_diff[2]!=0){serial_print("Slave Voltage Difference Alarm 2\r\n");}
    if(bms->slave_tcell_error_high[2]!=0){serial_print("Slave High Temperature Alarm 2\r\n");}
    if(bms->slave_tcell_error_low[2]!=0){serial_print("Slave Low Temperature Alarm 2\r\n");}
    if(bms->slave_tcell_error_diff[2]!=0){serial_print("Slave Temperature Difference Alarm 2\r\n");}
    if(bms->hv_monitoring_error_high[2]!=0){serial_print("HV High Voltage Alarm 2\r\n");}
    if(bms->hv_monitoring_error_low[2]!=0){serial_print("HV Low Voltage Alarm 2\r\n");}
    if(bms->hv_current_error_max[2] !=0){serial_print("HV Current Alarm 2\r\n");}       
}
/*Display the Relays status: open or closed*/
void relay_status(bms* bms){
    char aux[AUX_SIZE];
    serial_print("RELAY STATUS:\r\n");
    sprintf(aux,"AIR-: %s AIR+: %s AIR PRECHARGE: %s\r\n",
        (bms->air_neg==ON)?"ON":"OFF",(bms->air_pos==ON)?"ON":"OFF",
        (bms->air_prech==ON)?"ON":"OFF");
    serial_print(aux);  
}
/*Display the fans status: open or closed*/
void cooling_status(bms* bms){
    char aux[AUX_SIZE];
    serial_print("COOLING STATUS:\r\n");
    sprintf(aux,"FAN1/2: %s FAN3/4: %s FAN5/6: %s\r\n",
        (bms->fan1==ON)?"ON":"OFF",(bms->fan2==ON)?"ON":"OFF",
        (bms->fan3==ON)?"ON":"OFF");
    serial_print(aux);        
}
/*Display which cells need balancing*/
void balance_status(bms* bms){
    int i,j;
    char aux[AUX_SIZE];
    sprintf(aux,"BALANCE STATUS: Counter %i\r\n", bms->bcount);
    serial_print(aux);    
    for(i=0; i< N_SLAVES; ++i){
        sprintf(aux, "SLAVE %i\r\n", i+1);serial_print(aux);
        for(j =0; j<N_CELLS - bms->maskcell[i]; ++j){
            sprintf(aux,"C%i: %s ",j+1,(bms->bcell[i][j]==1)?"ON":"OFF");serial_print(aux);
        }
        serial_print("\r\n");
    }    
}

/* Display CAN status*/
void can_status(bms* bms){
   
}
/*Sends information with an optimal format for the GUI*/
void gui_comm(bms* bms){
    UartMessage1Bytes tx_data_1;
    UartMessage2Bytes tx_id, tx_id_2;
    UartMessage2Bytes tx_data_2;
    UartMessage2Bytes tx_eof;
    UartMessage4Bytes tx_data_4;
    tx_eof.Byte0 = 0;
    tx_eof.Byte1 = 0;
    
    uint8_t i,j,k;
//Mode
    tx_id.Msg = 1;
    tx_data_2.Msg = bms->bms_mode; gui_msg(tx_id, tx_data_2, tx_eof);
//Alarms
    tx_id.Msg = 2;
    tx_data_2.Msg = bms->error0count; gui_msg(tx_id, tx_data_2, tx_eof);
    tx_id.Msg++;
    tx_data_2.Msg = bms->error1count; gui_msg(tx_id, tx_data_2, tx_eof);
    tx_id.Msg++;
    tx_data_2.Msg = bms->error2count; gui_msg(tx_id, tx_data_2, tx_eof);  
//HV Parameters
    
//AIRs
    tx_id.Msg = 8;
    tx_data_2.Msg = (bms->air_neg == ON)?1:0; gui_msg(tx_id, tx_data_2, tx_eof);
    tx_id.Msg++;
    tx_data_2.Msg = (bms->air_pos == ON)?1:0; gui_msg(tx_id, tx_data_2, tx_eof);
    tx_id.Msg++;
    tx_data_2.Msg = (bms->air_prech == ON)?1:0; gui_msg(tx_id, tx_data_2, tx_eof);
    tx_id.Msg++;
    tx_data_2.Msg = (bms->shutdown)?1:0; gui_msg(tx_id, tx_data_2, tx_eof);
//Stacks
    tx_id.Msg = 12;
    for(i=0; i < N_STACKS; ++i){
        tx_data_4.Msg = bms->vstack[i]*1000; gui_msg_long(tx_id, tx_data_4, tx_eof);
        tx_id.Msg++;
        tx_data_2.Msg = bms->vmaxstack[i]; gui_msg(tx_id, tx_data_2, tx_eof);
        tx_id.Msg++;
        tx_data_2.Msg = bms->vminstack[i]; gui_msg(tx_id, tx_data_2, tx_eof);
        tx_id.Msg++;
        tx_data_2.Msg = bms->vdiffstack[i]; gui_msg(tx_id, tx_data_2, tx_eof);
        tx_id.Msg++;
        //tx_data_4.Msg = bms->tmax[i]; gui_msg_long(tx_id, tx_data_4, tx_eof);
        tx_id.Msg++;
        //tx_data_4.Msg = bms->tmin[i]; gui_msg_long(tx_id, tx_data_4, tx_eof);
        tx_id.Msg++;
        //tx_data_4.Msg = (bms->tmax[i] - bms->tmin[i]); gui_msg_long(tx_id, tx_data_4, tx_eof);
        tx_id.Msg++;
    }
//Fans
    tx_id.Msg = 54;
    tx_data_2.Msg = (bms->fan1 == ON)?1:0; gui_msg(tx_id, tx_data_2, tx_eof);
    tx_id.Msg++;
    tx_data_2.Msg = (bms->fan2 == ON)?1:0; gui_msg(tx_id, tx_data_2, tx_eof);
    tx_id.Msg++;
    tx_data_2.Msg = (bms->fan3 == ON)?1:0; gui_msg(tx_id, tx_data_2, tx_eof);      

//Errors
    tx_id.Msg = 57;
    tx_data_2.Msg = 0;
    if(bms->input_error_mode_imp!=0){tx_data_2.Bit0 = 1;}
    if(bms->slave_pec_error_config!=0){tx_data_2.Bit1 = 1;}
    if(bms->slave_pec_error_voltage!=0){tx_data_2.Bit2 = 1;}
    else{
        if(bms->slave_vcell_error_low[0]!=0){tx_data_2.Bit3 = 1;}
        if(bms->slave_vcell_error_high[0]!=0){tx_data_2.Bit4 = 1;}
        if(bms->slave_vcell_error_sum!=0){tx_data_2.Bit5 = 1;}
        if(bms->slave_vcell_error_diff[0]!=0){tx_data_2.Bit6 = 1;}
        if(bms->slave_owcell_error!=0){tx_data_2.Bit7 = 1;}        
    }
    if(bms->slave_pec_error_temp!=0){tx_data_2.Bit2 = 1;}
    else{
        if(bms->slave_tcell_error_low[0]!=0){tx_data_2.Bit8 = 1;}
        if(bms->slave_tcell_error_high[0]!=0){tx_data_2.Bit9 = 1;}
        if(bms->slave_tcell_error_diff[0]!=0){tx_data_2.Bit10 = 1;}        
    }
    if(bms->slave_pec_error_stat!=0){tx_data_2.Bit2 = 1;}
    if(bms->hv_monitoring_error_imp!=0){tx_data_2.Bit11 = 1;}
    if(bms->hv_monitoring_error_high[0]!=0){tx_data_2.Bit12 = 1;}
    if(bms->hv_monitoring_error_low[0]!=0){tx_data_2.Bit13 = 1;}
    if(bms->hv_monitoring_error_sum!=0){tx_data_2.Bit14 = 1;}
    if(bms->hv_current_error_max[0] !=0){tx_data_2.Bit15 = 1;}    
    gui_msg(tx_id, tx_data_2, tx_eof);
    
    tx_id.Msg = 58;
    tx_data_2.Msg = 0;
    if(bms->slave_vcell_error_low[1]!=0){tx_data_2.Bit3 = 1;}
    if(bms->slave_vcell_error_high[1]!=0){tx_data_2.Bit4 = 1;}
    if(bms->slave_vcell_error_diff[1]!=0){tx_data_2.Bit6 = 1;}  
    if(bms->slave_tcell_error_low[1]!=0){tx_data_2.Bit8 = 1;}
    if(bms->slave_tcell_error_high[1]!=0){tx_data_2.Bit9 = 1;}
    if(bms->slave_tcell_error_diff[1]!=0){tx_data_2.Bit10 = 1;} 
    if(bms->hv_monitoring_error_high[1]!=0){tx_data_2.Bit12 = 1;}
    if(bms->hv_monitoring_error_low[1]!=0){tx_data_2.Bit13 = 1;}
    if(bms->hv_current_error_max[1] !=0){tx_data_2.Bit15 = 1;}     
    gui_msg(tx_id, tx_data_2, tx_eof);
    tx_id.Msg = 59;
    tx_data_2.Msg = 0;
    if(bms->slave_vcell_error_low[2]!=0){tx_data_2.Bit3 = 1;}
    if(bms->slave_vcell_error_high[2]!=0){tx_data_2.Bit4 = 1;}
    if(bms->slave_vcell_error_diff[2]!=0){tx_data_2.Bit6 = 1;}  
    if(bms->slave_tcell_error_low[2]!=0){tx_data_2.Bit8 = 1;}
    if(bms->slave_tcell_error_high[2]!=0){tx_data_2.Bit9 = 1;}
    if(bms->slave_tcell_error_diff[2]!=0){tx_data_2.Bit10 = 1;} 
    if(bms->hv_monitoring_error_high[2]!=0){tx_data_2.Bit12 = 1;}
    if(bms->hv_monitoring_error_low[2]!=0){tx_data_2.Bit13 = 1;}
    if(bms->hv_current_error_max[2] !=0){tx_data_2.Bit15 = 1;}    
    gui_msg(tx_id, tx_data_2, tx_eof);   
//Cells
    tx_id.Msg = 60;
    for(i=0; i < N_STACKS; ++i){
        for(j=0; j < SLAVES_PER_STACK; ++j){
            for(k=0; k<N_CELLS - bms->maskcell[bms->mstack[i][j]]; ++k){
                tx_data_2.Msg = bms->vcell[bms->mstack[i][j]][k]; gui_msg(tx_id, tx_data_2, tx_eof);
                tx_id_2.Msg = tx_id.Msg + 138;
                tx_data_1.Msg = bms->bcell[bms->mstack[i][j]][k]; gui_msg_short(tx_id_2, tx_data_1, tx_eof);
                tx_id.Msg++;
            }
        }
    }
    
}
/*Sends Cell Voltages via CAN*/
void can_comm_cellv(bms* bms){
    unsigned int can_cellv_sid[36] = {BMS_CELL_STACK1_S0_0, BMS_CELL_STACK1_S0_1, BMS_CELL_STACK1_S0_2, BMS_CELL_STACK1_S1_0, BMS_CELL_STACK1_S1_1, BMS_CELL_STACK1_S1_2,
                                      BMS_CELL_STACK2_S0_0, BMS_CELL_STACK2_S0_1, BMS_CELL_STACK2_S0_2, BMS_CELL_STACK2_S1_0, BMS_CELL_STACK2_S1_1, BMS_CELL_STACK2_S1_2,
                                      BMS_CELL_STACK3_S0_0, BMS_CELL_STACK3_S0_1, BMS_CELL_STACK3_S0_2, BMS_CELL_STACK3_S1_0, BMS_CELL_STACK3_S1_1, BMS_CELL_STACK3_S1_2,
                                      BMS_CELL_STACK4_S0_0, BMS_CELL_STACK4_S0_1, BMS_CELL_STACK4_S0_2, BMS_CELL_STACK4_S1_0, BMS_CELL_STACK4_S1_1, BMS_CELL_STACK4_S1_2,
                                      BMS_CELL_STACK5_S0_0, BMS_CELL_STACK5_S0_1, BMS_CELL_STACK5_S0_2, BMS_CELL_STACK5_S1_0, BMS_CELL_STACK5_S1_1, BMS_CELL_STACK5_S1_2,
                                      BMS_CELL_STACK6_S0_0, BMS_CELL_STACK6_S0_1, BMS_CELL_STACK6_S0_2, BMS_CELL_STACK6_S1_0, BMS_CELL_STACK6_S1_1, BMS_CELL_STACK6_S1_2};
    
    //unsigned int can_cellv_eid[4] = {CAN_HCU_CELL_EID_0, CAN_HCU_CELL_EID_1, CAN_HCU_CELL_EID_2, CAN_HCU_CELL_EID_3};
    unsigned int data[4];
    int i, j, k, cell, sid = 0;
    for(i=0; i < N_SLAVES; ++i){
        for(j=0; j<N_CELLS/4; ++j){
            for(k=0; k<4; ++k){
                cell = 4*j+k;
                if( cell == (N_CELLS - bms->maskcell[i])){
                    data[k] = 0;
                }
                else{
                    data[k] = bms->vcell[i][cell];
                            
                }
            }
            can_send_msg_sd(can_cellv_sid[sid], data);
            sid++;
        }
        time_delay(1, 5); // Delay para que envie el CAN correctamente, porque sino se satura
    }
}
/*Sends Cell Temperatures via CAN*/
void can_comm_cellt(bms* bms){
   unsigned int can_cellt_sid[12] = {BMS_TEMP_STACK1_S0, BMS_TEMP_STACK2_S1, BMS_TEMP_STACK3_S0, BMS_TEMP_STACK4_S1, BMS_TEMP_STACK5_S0, BMS_TEMP_STACK6_S1,
                                    BMS_TEMP_STACK6_S0, BMS_TEMP_STACK5_S1, BMS_TEMP_STACK4_S0, BMS_TEMP_STACK3_S1, BMS_TEMP_STACK2_S0, BMS_TEMP_STACK1_S1};
   
   uint8_t data[5];
   int i,k;
   for(i=0; i< 12; ++i){
        for(k=0; k<5; k++){
          
            data[k] = bms->tcell[i][k];
                                 
        }
        can_send_msg_8_sd(can_cellt_sid[i], data); 
    }
}
void gui_msg_short(UartMessage2Bytes id, UartMessage1Bytes data, UartMessage2Bytes eof){
    serial_printbytes(id.ByteArray, 2);
    serial_printbytes(data.ByteArray,1);
    serial_printbytes(eof.ByteArray,2);       
}
void gui_msg(UartMessage2Bytes id, UartMessage2Bytes data, UartMessage2Bytes eof){
    serial_printbytes(id.ByteArray, 2);
    serial_printbytes(data.ByteArray,2);
    serial_printbytes(eof.ByteArray,2);       
}
void gui_msg_long(UartMessage2Bytes id, UartMessage4Bytes data, UartMessage2Bytes eof){
    serial_printbytes(id.ByteArray, 2);
    serial_printbytes(data.ByteArray,4);
    serial_printbytes(eof.ByteArray,2);       
}