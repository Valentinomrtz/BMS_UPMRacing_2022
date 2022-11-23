/* 
 * Slave Comm File
 * Application Layer
 */

#include "slave_comm.h"
#include "dev/ltc.h"
#include "dev/serial.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define OV_THRESHOLD 42000 //(4.25 V))
#define UV_THRESHOLD 30000 //(2.7 V)
#define BUFFER_SIZE 256
/*Main Structure*/
static cell_asic bms_slaves[N_SLAVES];
/*ADC Command Cofiguration*/
const uint8_t ADC_OPT = ADC_OPT_DISABLED; //!< ADC Mode option bit
const uint8_t ADC_CONVERSION_MODE = MD_7KHZ_3KHZ; //!< ADC Mode
const uint8_t ADC_DCP = DCP_ENABLED; //!< Discharge Permitted 
const uint8_t CELL_CH_TO_CONVERT = CELL_CH_ALL; //!< Channel Selection for ADC conversion
const uint8_t AUX_CH_TO_CONVERT = AUX_CH_ALL; //!< Channel Selection for ADC conversion
const uint8_t STAT_CH_TO_CONVERT = STAT_CH_ALL; //!< Channel Selection for ADC conversion
const uint8_t NO_OF_REG = REG_ALL; //!< Register Selection

/*Configuration Bits*/
bool REFON = true; //!< Reference Powered Up Bit
bool ADCOPT = false; //!< ADC Mode option bit
bool gpioBits_a[5] = {true,true,true,true,true}; //!< GPIO Pin Control // Gpio 1,2,3,4,5
uint16_t UV=UV_THRESHOLD; //!< Under-voltage Comparison Voltage
uint16_t OV=OV_THRESHOLD; //!< Over-voltage Comparison Voltage
bool dccBits_a[12] = {false,false,false,false,false,false,false,false,false,false,false,false}; //!< Discharge cell switch //Dcc 1,2,3,4,5,6,7,8,9,10,11,12
bool dctoBits[4] = {true, false, true, false}; //!< Discharge time value // Dcto 0,1,2,3 // Programed for 4 min 


/*Execute the Slave functions and store the data*/
void slave_monitoring(bms* bms){
    uint16_t cfg_pec;
    int i,j,k,l,m;
    float temp, vaux;
    uint16_t vmax, vmin;
    float tmax,tmin,tmean,vmean;
    bms->tmaxglobal = -1000;
    bms->tminglobal = 1000;
    bms->slave_pec_error_config = slave_config();
    bms->slave_pec_error_voltage = slave_cell_voltage_measurement();
    bms->slave_pec_error_temp = slave_temperature_measurement();
    bms->slave_pec_error_stat = slave_stat_measurement();
    slave_open_wire_check(bms);
    for(i=0; i<N_SLAVES; ++i){     
        for(m =0; m<6; ++m){
            bms->tx_config[i][m] = bms_slaves[i].config.tx_data[m];
            bms->rx_config[i][m] = bms_slaves[i].config.rx_data[m];
        }
        cfg_pec = ltc_pec(6,&bms_slaves[i].config.tx_data[0]);
        bms->tx_config[i][6] = ((uint8_t)(cfg_pec>>8));
        bms->tx_config[i][7] = ((uint8_t)(cfg_pec));
        bms->rx_config[i][6] = bms_slaves[i].config.rx_data[7];
        bms->rx_config[i][7] = bms_slaves[i].config.rx_data[m];
        vmax = 0;
        vmean = 0;
        vmin = 60000;
        for(j = 0; j < N_CELLS - bms->maskcell[i]; ++j){  //Aquí simplemente identifica cuales leen 11 o 12 celdas
            bms->vcell[i][j] = bms_slaves[i].cells.c_codes[j];
            vmean += bms->vcell[i][j];
            if(bms->vcell[i][j]>vmax){
                vmax = bms->vcell[i][j];
            }
            if(bms->vcell[i][j]<vmin){
                vmin = bms->vcell[i][j];
            }
        }
        bms->vmean[i] = vmean/(N_CELLS - bms->maskcell[i]);
        bms->vmax[i] = vmax;
        bms->vmin[i] = vmin;
        tmax = -1000;
        tmean = 0;
        tmin =1000;
        for(k = 0; k < N_NTCS; ++k){           
            temp = bms_slaves[i].aux.a_codes[k]*0.0001;
            temp = temp*100000/(bms_slaves[i].aux.a_codes[5]*0.0001-temp);
            temp = 4150/log(temp/0.090153388883630376)-273;
            bms->tcell[i][k] = temp;
            bms->tcell[4][4] = bms->tcell[4][3];
            bms->tcell[10][1] = bms->tcell[4][3];
            bms->tcell[5][1] = bms->tcell[4][3];
            bms->tcell[6][4] = bms->tcell[4][3];
            bms->tcell[9][3] = bms->tcell[4][3];
            tmean += bms->tcell[i][k];
            if(bms->tcell[i][k]>tmax){
                tmax = bms->tcell[i][k];
            }
            if(bms->tcell[i][k]<tmin){
                tmin = bms->tcell[i][k];
            }  
            if (bms->tcell[i][k]> bms->tmaxglobal) {
                bms->tmaxglobal = bms->tcell[i][k];
            }
            if (bms->tcell[i][k] < bms->tminglobal) {
                bms->tminglobal = bms->tcell[i][k];
            }
        }
        bms->tmean[i] = tmean/N_NTCS;
        bms->tmax[i] = tmax;
        bms->tmin[i] = tmin;
        bms->SLAVE_ERROR = i;
        bms->NTC_ERROR = k;
        bms->tcell[i][N_NTCS] = bms_slaves[i].aux.a_codes[5]*0.0001;
        bms->stats[i][0] = bms_slaves[i].stat.stat_codes[0]*0.0001*20;
        bms->stats[i][1] = bms_slaves[i].stat.stat_codes[1]*(0.0001/0.0075)-273;
        bms->stats[i][2] = bms_slaves[i].stat.stat_codes[2]*0.0001;
        bms->stats[i][3] = bms_slaves[i].stat.stat_codes[3]*0.0001;
    }
    for(i=0; i<N_STACKS; ++i){
        bms->vstack[i] = 0;
        vmax = 0;
        vmin = 60000;
        tmax = -1000;
        tmin =1000;
        for(j=0; j<SLAVES_PER_STACK; ++j){
            bms->vstack[i] += bms->stats[bms->mstack[i][j]][0];
            if(bms->vmax[bms->mstack[i][j]] > vmax){
                vmax = bms->vmax[bms->mstack[i][j]];
            }
            if(bms->vmin[bms->mstack[i][j]] < vmin){
                vmin = bms->vmin[bms->mstack[i][j]];
            }
            if(bms->tmax[bms->mstack[i][j]] > tmax){
                tmax = bms->tmax[bms->mstack[i][j]];
            }
            if(bms->tmin[bms->mstack[i][j]] < tmin){
                tmin = bms->tmin[bms->mstack[i][j]];
            }            
        }
        bms->vmaxstack[i] = vmax;
        bms->vminstack[i] = vmin;
        
        bms->V_SLAVE_MAX = j;
        bms->V_STACK_MAX = i;
        bms->vdiffstack[i] = bms->vmaxstack[i] - bms->vminstack[i];
        bms->tmaxstack[i] = tmax;
        bms->tminstack[i] = tmin;        
        bms->tdiffstack[i] = bms->tmaxstack[i] - bms->tminstack[i];
    }
    /* Correction*/
    for(i=0; i<N_SLAVES; ++i){
        vaux=0;
        for(j=1; j<N_CELLS - bms->maskcell[i]; ++j){
            vaux += bms->vcell[i][j];
        }
        bms->vsums[i] = vaux + bms->vcell[i][0];
        bms->vcell[i][0] = 10000*bms->stats[i][0] - vaux;
    }
    
    /* Calculate Vmax and Vmin*/
    
    bms->vcell_max = 0;
    bms->vcell_min = 60000;
    for(i=0; i<N_SLAVES; ++i){
        if(bms->vcell_max < bms->vmax[i]){
            bms->vcell_max = bms->vmax[i];
        }
        if(bms->vcell_min > bms->vmin[i]){
            bms->vcell_min = bms->vmin[i];
        }
    }
}
/*Initialize the Slave configuration*/
void slave_init(){
    uint8_t slave;
    ltc_init();
    ltc_init_cfg(N_SLAVES, bms_slaves);

    for(slave = 0; slave < N_SLAVES; ++slave){
        ltc_set_cfgr(slave,bms_slaves,REFON,ADCOPT,gpioBits_a,dccBits_a, dctoBits,UV, OV);
    }
    ltc_reset_crc_count(N_SLAVES, bms_slaves);
    ltc_init_reg_limits(N_SLAVES, bms_slaves);
    
}
/*Write the Slave configuration*/
int8_t slave_config(){
    int8_t error = 0;
    ltc_wakeup_sleep(N_SLAVES);
    ltc_wrcfga(N_SLAVES, bms_slaves);
    ltc_wakeup_idle(N_SLAVES);
    error = ltc_rdcfga(N_SLAVES, bms_slaves);
    return error;
}
/*Perform the ADC conversion and cell voltage measurement*/
int8_t slave_cell_voltage_measurement(){
    uint32_t conv_time = 0;
    int8_t error = 0;
    uint8_t slave,i;
    char aux[BUFFER_SIZE];
 
    ltc_wakeup_sleep(N_SLAVES);
    ltc_adcv(ADC_CONVERSION_MODE,ADC_DCP,CELL_CH_TO_CONVERT);
    //ltc_adcvax(ADC_CONVERSION_MODE,ADC_DCP);
    conv_time = ltc_pollAdc();
    /*serial_print("Cell conversion completed in: ");
    serial_printf((float)(conv_time));
    serial_print(" ms\n");*/
    //time_delay(1, 10);
    ltc_wakeup_sleep(N_SLAVES);
    error = ltc_rdcv(NO_OF_REG, N_SLAVES, bms_slaves);
    return error;
}
/*Perform the ADC conversion and cell temperature measurement*/
int8_t slave_temperature_measurement(){
    uint32_t conv_time = 0;
    int8_t error = 0;
    uint8_t slave,i; 
    float temp;
    char aux[BUFFER_SIZE];
    ltc_wakeup_sleep(N_SLAVES);
    ltc_adax(ADC_CONVERSION_MODE,AUX_CH_TO_CONVERT);
    conv_time = ltc_pollAdc();
    time_delay(1, 10);
    ltc_wakeup_sleep(N_SLAVES);
    error = ltc_rdaux(NO_OF_REG, N_SLAVES, bms_slaves); 
    return error;
}
/*Perform the ADC conversion and slave stats measurement*/
int8_t slave_stat_measurement(){
    uint32_t conv_time = 0;
    int8_t error = 0;
    uint8_t slave,i;
    char aux[BUFFER_SIZE];
    ltc_wakeup_sleep(N_SLAVES);
    ltc_adstat(ADC_CONVERSION_MODE, STAT_CH_TO_CONVERT);
    conv_time = ltc_pollAdc();
    time_delay(1, 10);
    ltc_wakeup_sleep(N_SLAVES);
    error = ltc_rdstat(NO_OF_REG, N_SLAVES, bms_slaves);
    return error;
    /*
    sprintf(aux,"Flags: ");
    serial_print(aux);
    serial_printhex(bms_slaves[slave].stat.flags[0]);
    serial_printhex(bms_slaves[slave].stat.flags[1]);
    serial_printhex(bms_slaves[slave].stat.flags[2]);
    sprintf(aux,"MUX Fail Flag: ");
    serial_print(aux);
    serial_printhex(bms_slaves[slave].stat.mux_fail[0]);      
    sprintf(aux,"THSD: ");
    serial_print(aux);
    serial_printhex(bms_slaves[slave].stat.thsd[0]);
    serial_print("\n");
    */
}
/*Perform cell balancing*/
void slave_cell_balancing(int slave, int cell){
    if((slave>0)&&(slave<=N_SLAVES)&&(cell>0)&&(cell<=12)){
        ltc_set_discharge(cell, N_SLAVES-slave, bms_slaves);              
    }else{
        ltc_clear_discharge(N_SLAVES, bms_slaves);
    } 
}
/*Perform openwire detection*/
void slave_open_wire_check(bms* bms){
    uint8_t open_cells[N_SLAVES*(bms_slaves[0].ic_reg.cell_channels)];
    char aux[BUFFER_SIZE];
    int slave,i;
    for(slave = 0; slave < N_SLAVES; ++slave){
        for(i=0; i< bms_slaves[0].ic_reg.cell_channels; ++i){
            open_cells[slave*12+i] = 0;  
        }
    }
    ltc_run_openwire_multi(N_SLAVES, bms_slaves, open_cells);
    //serial_print("Open Wires:\n");
    for(slave = 0; slave < N_SLAVES; ++slave){
       //sprintf(aux, "Slave %i: ", slave);
       //serial_print(aux);
        for(i=0; i< bms_slaves[0].ic_reg.cell_channels; ++i){
            bms->owcell[slave][i] = open_cells[slave*12+i];
            if(open_cells[slave*12+i] == 1){
                //sprintf(aux, "%i ", i+1);
                //serial_print(aux);                
            }            
        }
       //serial_print("\n");
    }
}
/*Print the slave configuration to send*/
void slave_print_config(){
    uint16_t cfg_pec;
    uint8_t slave,i;
    char aux[BUFFER_SIZE];
    serial_print("Written Configuration: \r\n");
    for(slave = 0; slave< N_SLAVES; ++slave){
       sprintf(aux, "Slave %i: ", slave+1);
       serial_print(aux);
       for(i =0; i < 6; ++i){
           serial_printhex(bms_slaves[slave].config.tx_data[i]);           
       }
       cfg_pec = ltc_pec(6,&bms_slaves[slave].config.tx_data[0]);
       serial_print("PEC: ");
       serial_printhex((uint8_t)(cfg_pec>>8));
       serial_printhex((uint8_t)cfg_pec);
       serial_print("\r\n");
    }
}
/*Print the received slave configuration*/
void slave_print_rconfig(){
    uint8_t slave,i;
    char aux[BUFFER_SIZE];
    serial_print("Received Configuration: \r\n");
    for(slave = 0; slave< N_SLAVES; ++slave){
       sprintf(aux, "Slave %i: ", slave+1);
       serial_print(aux);
       for(i =0; i < 6; ++i){
           serial_printhex(bms_slaves[slave].config.rx_data[i]);           
       }
       serial_print("PEC: ");
       serial_printhex(bms_slaves[slave].config.rx_data[6]); 
       serial_printhex(bms_slaves[slave].config.rx_data[7]); 
       serial_print("\r\n");
    }
}