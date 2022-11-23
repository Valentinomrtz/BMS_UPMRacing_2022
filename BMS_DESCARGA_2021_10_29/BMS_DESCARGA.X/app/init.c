
/*
 *  Initialization File 
 *  Application layer
 */

#include "init.h"

#include "dev/serial.h"
#include "dev/leds.h"
#include "dev/time.h"
#include "slave_comm.h"
#include "dev/analog.h"
#include "dev/control.h"
#include "dev/memory.h"
#include "dev/canlib.h"
#include <stdlib.h>
#include <stdio.h>


#define _SUPPRESS_PLIB_WARNING
#include "plib.h"

// Clock Configuration
#pragma config FNOSC    = PRIPLL    //Primary Oscillator
#pragma config POSCMOD  = XT        //Crystal Mode (HS also available))
#pragma config FPLLIDIV = DIV_2     //PLL Input Divider
#pragma config FPLLMUL  = MUL_20    //PLL Multiplier
#pragma config FPLLODIV = DIV_1     //PLL Output Divider
#pragma config FPBDIV   = DIV_1     //Peripheral Bus Clock Divider

//Additional Configuration
#pragma config FWDTEN = OFF         //Watchdog Disabled
#pragma config CP = OFF, BWP = OFF  //Code Protection Disabled

const int mask[N_SLAVES] = {SLAVE_1_MASK, SLAVE_2_MASK, SLAVE_3_MASK, SLAVE_4_MASK, 
SLAVE_5_MASK, SLAVE_6_MASK, SLAVE_7_MASK, SLAVE_8_MASK, SLAVE_9_MASK, SLAVE_10_MASK, 
SLAVE_11_MASK, SLAVE_12_MASK};
const int stack_map[N_STACKS][SLAVES_PER_STACK] = {{0,11}, {1,10},{2,9},{3,8},{4,7},{5,6}};

/* Initialization Function*/
void initialize_system(bms* bms){
    
    serial_init();
    #ifndef GUI
    serial_print("BMS Test v1.0\r\n");
    serial_print("UART/USB communication initialized\r\n");
    #endif
    bms_init(bms);
    leds_init();
    control_init();
    #ifndef GUI
    serial_print("GPIOs Initialized\r\n");
    #endif    
    time_init();  
    #ifndef GUI
    serial_print("Timers Initialized\r\n");
    #endif 
    analog_init();
    #ifndef GUI
    serial_print("ADC Initialized\r\n");
    #endif 
    slave_init();
    #ifndef GUI
    serial_print("SPI Communication Initialized\r\n");
    #endif 
    can_init();
    #ifndef GUI
    serial_print("CAN Communication Initialized\r\n");
    #endif 
    INTEnableSystemMultiVectoredInt();
    state_init();
    //serial_print("Interrups enabled: UART RX, TIMER1, TIMER2, CN GPIOs\r\n");
    slave_config();
    #ifndef GUI
    serial_print("Slaves configured\r\n");
    #endif 
    slave_print_config();
    slave_print_rconfig(); 
    
    char aux[256];
    unsigned int soc = mem_read_soc();
    #ifndef GUI
    sprintf(aux, "Old SOC: %u\r\n", soc); 
    serial_print(aux);  
    #endif
    if(soc >= 50){
        mem_write_soc(0);
    }
    else{
        soc++;
        mem_write_soc(soc);
    }
    soc = mem_read_soc();
    #ifndef GUI
    sprintf(aux, "New SOC: %u\r\n", soc);
    serial_print(aux);
    #endif
    time_delay(1, 5000);

}
/*BMS Cell Masking*/
void bms_init(bms* bms){
    int8_t i,j;
    for(i = 0; i< N_SLAVES; ++i){
        bms->maskcell[i] = mask[i];
    }
    for(i=0; i<N_STACKS; ++i){
        for(j=0; j<SLAVES_PER_STACK; ++j){
        bms->mstack[i][j] = stack_map[i][j];            
        }
    }
    bms->first_cycle = 1;
    bms->changed_mode = 0;
    bms->can_flag = true;
    bms->timererror = 0;
}
void charge_init (bms* bms) {
    bms->MaxChrVoltage = 19990;
    bms->MaxChrCurrent = 12800;
}