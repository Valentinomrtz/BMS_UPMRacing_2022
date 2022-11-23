/* 
 * Control File
 * Device Layer
 */

#include "control.h"
#include <stdio.h>
#include <stdint.h>

#include "lib/gpio.h"

/*Initialization of control signals, open everything*/
void control_init(){
    gpio_ctrl_init();
    gpio_sgnl_init();
    //gpio_interrupt_cn_set();
    control_relay_open(AIR_POS);
    control_relay_open(AIR_NEG);
    control_relay_open(AIR_PRECH);
    control_fan_open(1);
    control_fan_open(2);
    control_fan_open(3);
    control_bms_fault_clear();
}
/* Open the specified relay*/
void control_relay_open(relay c){
    switch(c){
        case AIR_POS:
            gpio_airp_set(0);
            break;
        case AIR_NEG:
            gpio_airn_set(0);            
            break;
        case AIR_PRECH:
            gpio_prec_set(0);            
            break;
    }
}
/* Close the specified relay*/
void control_relay_close(relay c){
    switch(c){
        case AIR_POS:
            gpio_airp_set(1);
            break;
        case AIR_NEG:
            gpio_airn_set(1);            
            break;
        case AIR_PRECH:
            gpio_prec_set(1);            
            break;
    }    
}
/*Deactivate the specified of group of fans*/
void control_fan_open(int c){
    switch(c){
        case 1:
            gpio_fan1_set(0);
            break;
        case 2:
            gpio_fan2_set(0);            
            break;
        case 3:
            gpio_fan3_set(0);            
            break;
    }
}
/*Activate the specified group of fans*/
void control_fan_close(int c){
    switch(c){
        case 1:
            gpio_fan1_set(1);
            break;
        case 2:
            gpio_fan2_set(1);            
            break;
        case 3:
            gpio_fan3_set(1);            
            break;
    }
}
/*Deactivate the BMS error signal*/
void control_bms_fault_clear(){
    gpio_bmsf_set(1);
}
/*Activate the BMS error signal*/
void control_bms_fault_set(){
    gpio_bmsf_set(0);
}
/*Read the specified control signal*/
uint8_t control_signal_read(ctrlsignal s){
    switch(s){
        case BAL:
            return gpio_signal_bal_read();
            break;
        case SHTDWN:
            return gpio_signal_shtdwn_read();            
            break;
        case DISCH:
            return gpio_signal_disch_read();          
            break;
        case CH:
            return gpio_signal_ch_read();  
            break;
    }
}
/*Clear Change Notification Interrupt*/
void control_signal_interrupt(){
    gpio_interrupt_cn_clear();
}