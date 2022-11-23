/* 
 *  Main Configuration Header
 *  Main Layer
 */

#ifndef MAIN_CONFIG_H
#define	MAIN_CONFIG_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
//#define GUI
#define N_STACKS 6
#define N_SLAVES 12
#define SLAVES_PER_STACK 2

#define N_CELLS 12
#define N_NTCS 5
#define N_STATS 4
#define PRECHARGE_PERCENTAGE 50

#define MAX_HV_VOLTAGE_0 580
#define MAX_HV_VOLTAGE_1 575
#define MAX_HV_VOLTAGE_2 570

#define MIN_HV_VOLTAGE_0 390
#define MIN_HV_VOLTAGE_1 395
#define MIN_HV_VOLTAGE_2 400

#define MAX_HV_VOLTAGE_IMP 30 //5

#define MAX_CELL_VOLTAGE_0 4100//3650 //4150
#define MAX_CELL_VOLTAGE_1 4125//3600 //4125
#define MAX_CELL_VOLTAGE_2 4100//3550 //4100

#define MIN_CELL_VOLTAGE_0 3300 //
#define MIN_CELL_VOLTAGE_1 3400 //
#define MIN_CELL_VOLTAGE_2 3500 //


#define MAX_CELL_DIFF_0 500 //400
#define MAX_CELL_DIFF_1 200
#define MAX_CELL_DIFF_2 100

#define MAX_CELL_DIFF_BALANCE 50
#define MAX_CYCLE_BALANCE 60

#define MAX_STACK_VOLTAGE_IMP 5

#define MAX_CELL_TEMP_0 57
#define MAX_CELL_TEMP_1 55
#define MAX_CELL_TEMP_2 52

#define MIN_CELL_TEMP_0 -1
#define MIN_CELL_TEMP_1 12
#define MIN_CELL_TEMP_2 15

#define MAX_TEMP_DIFF_0 20
#define MAX_TEMP_DIFF_1 12
#define MAX_TEMP_DIFF_2 15

#define MAX_CELL_TEMP_FANS 35

#define MAX_CURRENT_CHARGE_0 10
#define MAX_CURRENT_CHARGE_1 9
#define MAX_CURRENT_CHARGE_2 8

#define MAX_CURRENT_DISCHARGE_0 250
#define MAX_CURRENT_DISCHARGE_1 225
#define MAX_CURRENT_DISCHARGE_2 200

#define MAX_LOOP_TIME 500



#define SLAVE_1_MASK 0 // Sirve para definir cuales leen 12 (0) o 11 celdas (1)
#define SLAVE_2_MASK 1
#define SLAVE_3_MASK 0 
#define SLAVE_4_MASK 1
#define SLAVE_5_MASK 0
#define SLAVE_6_MASK 1
#define SLAVE_7_MASK 0
#define SLAVE_8_MASK 1
#define SLAVE_9_MASK 0
#define SLAVE_10_MASK 1
#define SLAVE_11_MASK 0
#define SLAVE_12_MASK 1

//MENSAJES CARGA
#define CAN_CHARGING_LIMITS_SID   0X601
#define CAN_CHARGING_LIMITS_EID   0X2E5F4

#define CAN_HCU_INFO_SID    0x618
#define CAN_HCU_INFO_EID    0x040F3

#define CAN_HCU_MAXV_SID    0x618
#define CAN_HCU_MAXV_EID    0x140F3

#define CAN_HCU_MAXT_SID    0x618
#define CAN_HCU_MAXT_EID    0x240F3

#define CAN_HCU_RELAY_SID   0x618
#define CAN_HCU_RELAY_EID   0x340F3

#define CAN_HCU_POWER_SID   0x619
#define CAN_HCU_POWER_EID   0x040F3

#define CAN_HCU_ALARM_SID   0x619
#define CAN_HCU_ALARM_EID   0x010F3

#define BMS_CELL_STACK1_S0_0  0x010
#define BMS_CELL_STACK1_S0_1  0x011
#define BMS_CELL_STACK1_S0_2  0x012
#define BMS_CELL_STACK1_S1_0  0x013
#define BMS_CELL_STACK1_S1_1  0x014
#define BMS_CELL_STACK1_S1_2  0x015

#define BMS_CELL_STACK2_S0_0  0x016
#define BMS_CELL_STACK2_S0_1  0x017
#define BMS_CELL_STACK2_S0_2  0x018
#define BMS_CELL_STACK2_S1_0  0x019
#define BMS_CELL_STACK2_S1_1  0x01A
#define BMS_CELL_STACK2_S1_2  0x01B

#define BMS_CELL_STACK3_S0_0  0x01C
#define BMS_CELL_STACK3_S0_1  0x01D
#define BMS_CELL_STACK3_S0_2  0x01E
#define BMS_CELL_STACK3_S1_0  0x01F
#define BMS_CELL_STACK3_S1_1  0x020
#define BMS_CELL_STACK3_S1_2  0x021

#define BMS_CELL_STACK4_S0_0  0x022
#define BMS_CELL_STACK4_S0_1  0x023
#define BMS_CELL_STACK4_S0_2  0x024
#define BMS_CELL_STACK4_S1_0  0x025
#define BMS_CELL_STACK4_S1_1  0x026
#define BMS_CELL_STACK4_S1_2  0x027

#define BMS_CELL_STACK5_S0_0  0x028
#define BMS_CELL_STACK5_S0_1  0x029
#define BMS_CELL_STACK5_S0_2  0x02A
#define BMS_CELL_STACK5_S1_0  0x02B
#define BMS_CELL_STACK5_S1_1  0x02C
#define BMS_CELL_STACK5_S1_2  0x02D

#define BMS_CELL_STACK6_S0_0  0x02E
#define BMS_CELL_STACK6_S0_1  0x02F
#define BMS_CELL_STACK6_S0_2  0x030
#define BMS_CELL_STACK6_S1_0  0x031
#define BMS_CELL_STACK6_S1_1  0x032
#define BMS_CELL_STACK6_S1_2  0x033

#define BMS_TEMP_STACK1_S0 0x001
#define BMS_TEMP_STACK1_S1 0x002

#define BMS_TEMP_STACK2_S0 0x003
#define BMS_TEMP_STACK2_S1 0x004

#define BMS_TEMP_STACK3_S0 0x005
#define BMS_TEMP_STACK3_S1 0x006

#define BMS_TEMP_STACK4_S0 0x007
#define BMS_TEMP_STACK4_S1 0x008

#define BMS_TEMP_STACK5_S0 0x009
#define BMS_TEMP_STACK5_S1 0x00A

#define BMS_TEMP_STACK6_S0 0x00B
#define BMS_TEMP_STACK6_S1 0x00C

#define BMS_HV 0x034
#define BMS_ERRORS 0x035
#define BMS_CELL_INFO 0x036
#define BMS_CELL_VARIATION 0x037
#define BMS_VOLTAGE_VARIATION 0x038
#define BMS_HCU_POWER_SID 0x619
#define BMS_HCU_POWER_EID 0x040F3
#define BMS_HCU_RELAY_SID 0x618
#define BMS_HCU_RELAY_EID 0x340F3

#define HV_FILTER_SIZE 20


typedef enum{ON, OFF} ctrl_signal;
typedef enum{STANDBY, CHARGE, DISCHARGE, ERROR, BALANCE, MAINTENANCE} mode;
volatile int internal_time;

typedef union byteMsg {
    struct{
        unsigned Bit0:1;
        unsigned Bit1:1;
        unsigned Bit2:1;
        unsigned Bit3:1;
        unsigned Bit4:1;
        unsigned Bit5:1;
        unsigned Bit6:1;
        unsigned Bit7:1;
    };
    uint8_t byte;
} ubyteMsg;

typedef struct{
    //Input Signals
    bool shutdown;
    bool charge;
    bool balance;
    bool discharge;
    //Mode
    mode bms_mode;
    uint8_t counter;
    int changed_mode;
    int first_cycle;
    //Time
    int loop_time;
    //Output signals
    int test_value;
    //Stack values
    int8_t mstack[N_STACKS][SLAVES_PER_STACK];
    float vstack[N_STACKS];
    uint16_t vmaxstack[N_STACKS];
    uint16_t vminstack[N_STACKS];
    uint16_t vdiffstack[N_STACKS];
    float tmaxstack[N_STACKS];
    float tminstack[N_STACKS];  
    float tdiffstack[N_STACKS];
    //Slave Values
    uint16_t vcell[N_SLAVES][N_CELLS];
    float tcell[N_SLAVES][N_NTCS+1];
    float stats[N_SLAVES][N_STATS];
    int8_t owcell[N_SLAVES][N_CELLS];
    int8_t bcell[N_SLAVES][N_CELLS];
    int8_t maskcell[N_SLAVES];
    uint16_t vmax[N_SLAVES];
    uint16_t vmean[N_SLAVES];
    uint16_t vmin[N_SLAVES];
    uint16_t vcell_max;
    uint16_t vcell_min;
    float vsums[N_SLAVES];
    float tmax[N_SLAVES];
    float tmean[N_SLAVES];
    float tmin[N_SLAVES];
    float tmaxglobal;
    float tminglobal;
    //Slave Configuration
    uint8_t tx_config[N_SLAVES][8];
    uint8_t rx_config[N_SLAVES][8];
    //HV Values
    float hv_batt;
    float hv_airs;
    float hv_batt_vals[HV_FILTER_SIZE];
    float hv_airs_vals[HV_FILTER_SIZE];
    //Current Value
    float current;
    //Relay Status
    ctrl_signal air_pos;
    ctrl_signal air_neg;
    ctrl_signal air_prech;
    //Cooling Status
    ctrl_signal fan1;
    ctrl_signal fan2;
    ctrl_signal fan3;
    //Balance parameters
    int8_t bcount;
    //Precharge Flag
    bool prechargeflag;
    //Main error flags
    bool error0flag;
    bool error1flag;
    bool error2flag;
    uint16_t error0count;
    uint16_t error1count;
    uint16_t error2count;
    //Input Errors
    int8_t input_error_mode_imp;
    //Slave Errors
    int8_t slave_pec_error_config;
    int8_t slave_pec_error_voltage;
    int8_t slave_pec_error_temp;
    int8_t slave_pec_error_stat;
    int8_t slave_vcell_error_low[3];
    int8_t slave_vcell_error_high[3];
    int8_t slave_vcell_error_sum;
    int8_t slave_vcell_error_diff[3];
    int8_t slave_tcell_error_high[3];
    int8_t slave_tcell_error_low[3];
    int8_t slave_tcell_error_diff[3];
    int8_t slave_owcell_error;
    //HV Errors
    int8_t hv_monitoring_error_imp;
    int8_t hv_monitoring_error_high[3];
    int8_t hv_monitoring_error_low[3];
    int8_t hv_monitoring_error_sum;
    int8_t hv_current_error_max[3];
    
    // Vector de errores CAN
    uint16_t error_vector[16];
    
    //Errores Temperaturas Slave-Ntc
    
    uint8_t SLAVE_ERROR;
    uint8_t NTC_ERROR;
    
    //Errores Voltajes Slave_Stack
    uint8_t V_SLAVE_MAX;
    uint8_t V_STACK_MAX;
    // Contador de precarga por delay
    
    uint8_t contador_precarga;
    
    // Carga
    int num_cycles;
    bool charge_flag;
    uint16_t MaxChrCurrLimit;
    uint16_t MaxChrPowerLimit;
    uint16_t ChrReqVoltage;
    uint16_t ChrReqCurrent;
    bool OnChrRlyStr;
    uint8_t OffChrRlyStr;
    
    //CAN
    bool can_flag;
    
    //Pruebas falsos errores
    uint8_t timererror;
    
    //MaxChrVoltage y MaxChrCurrent

uint16_t MaxChrVoltage;
uint16_t MaxChrCurrent ;
    
    
    
}bms;
#endif	/* MAIN_CONFIG_H */

