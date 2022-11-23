/* 
 * LTC Configuration Header
 * Device Layer
 */

#ifndef LTC_CONFIG_H
#define	LTC_CONFIG_H

#include <stdint.h>
#include <stdbool.h>

/*Data Structures*/

/*1 - Cell Voltage Data Structure*/
typedef struct{
    uint16_t c_codes[18];   //Cell Voltage Codes
    uint8_t pec_match[6];   //PEC Error detection during last read cmd
} cv;
/*2 - AUX Reg Voltage Data Structure*/
typedef struct{
    uint16_t a_codes[9];    //AUX Voltage Codes
    uint8_t pec_match[4];   //PEC Error detection during last read cmd
} ax;
/*3 - Status Reg Data Structure*/
typedef struct{
    uint16_t stat_codes[4]; //Status Codes
    uint8_t flags[3];       //UV/OV Flag Data
    uint8_t mux_fail[1];    //MUX Self Test Flag
    uint8_t thsd[1];        //THermal Shutdown Status
    uint8_t pec_match[2];   //PEC Error detection during last read cmd
} st;
/*4 - IC Reg Structure*/
typedef struct{
    uint8_t tx_data[6];     //Stores data to be transmitted
    uint8_t rx_data[8];     //Stores received data
    uint8_t rx_pec_match;   //PEC Error detection during last read cmd
} ic_register;
/*5 - PEC Error Counter Structure*/
typedef struct{
    uint16_t pec_count;     //Overall PEC Error count
    uint16_t cfgr_pec;      //Configuration Register Data PEC Error Count
    uint16_t cell_pec[6];   //Cell Voltage Register Data PEC Error Count
    uint16_t aux_pec[4];    //Aux Register Data PEC Error Count
    uint16_t stat_pec[2];   //Status Register Data PEC Error Count
} pec_counter;
/*6 - Register Configuration Structure*/
typedef struct{
    uint8_t cell_channels;  //N of Cell Channels
    uint8_t stat_channels;  //N of Stat Channels
    uint8_t aux_channels;   //N of Aux Channels
    uint8_t num_cv_reg;     //N of Cell Voltage Registers
    uint8_t num_gpio_reg;   //N of Aux Registers
    uint8_t num_stat_reg;   //N of Status Registers
} register_cfg;
/*7 - Cell Variable Main Structure*/
typedef struct{
  ic_register config;
  cv  cells;
  ax  aux;
  st  stat;
  ic_register com;
  ic_register pwm;
  ic_register pwmb;
  ic_register sctrl;
  ic_register sctrlb;
  uint8_t sid[6];
  bool isospi_reverse;
  pec_counter crc_count;
  register_cfg ic_reg;
  long system_open_wire;    
} cell_asic;

/* Configuration Codes*/

#define MD_422HZ_1KHZ 0
#define MD_27KHZ_14KHZ 1
#define MD_7KHZ_3KHZ 2
#define MD_26HZ_2KHZ 3

#define ADC_OPT_ENABLED 1
#define ADC_OPT_DISABLED 0

#define CELL_CH_ALL 0
#define CELL_CH_1and7 1
#define CELL_CH_2and8 2
#define CELL_CH_3and9 3
#define CELL_CH_4and10 4
#define CELL_CH_5and11 5
#define CELL_CH_6and12 6

#define SELFTEST_1 1
#define SELFTEST_2 2

#define AUX_CH_ALL 0
#define AUX_CH_GPIO1 1
#define AUX_CH_GPIO2 2
#define AUX_CH_GPIO3 3
#define AUX_CH_GPIO4 4
#define AUX_CH_GPIO5 5
#define AUX_CH_VREF2 6

#define STAT_CH_ALL 0
#define STAT_CH_SOC 1
#define STAT_CH_ITEMP 2
#define STAT_CH_VREGA 3
#define STAT_CH_VREGD 4

#define REG_ALL 0
#define REG_1 1
#define REG_2 2
#define REG_3 3
#define REG_4 4
#define REG_5 5
#define REG_6 6

#define DCP_DISABLED 0
#define DCP_ENABLED 1

#define PULL_UP_CURRENT 1
#define PULL_DOWN_CURRENT 0

#define NUM_RX_BYT 8
#define CELL 1
#define AUX 2
#define STAT 3
#define CFGR 0
#define CFGRB 4
#define CS_PIN SS


#endif	/* LTC_CONFIG_H */

