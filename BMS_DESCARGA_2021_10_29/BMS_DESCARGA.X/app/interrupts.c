/*
 *  Interrupt File 
 *  Application layer
 */
/**/
#include "interrupts.h"

#define _SUPPRESS_PLIB_WARNING

#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>
#include <plib.h>

#define BUFFER_SIZE 128

char s[BUFFER_SIZE];

extern volatile int internal_time;
/*UART RX Interrupt*/
void __ISR(_UART_1_VECTOR , IPL1AUTO) InterruptUART(void){
    serial_interrupt(s);
    // TO DO > Call to MODE
    if(s[0] == 'T'){
        led_toggle(s[1]-'1'+1);
        serial_print("Toggle\n");
    }
    else if(s[0] == 'S'){
        led_on(s[1]-'1'+1);  
        serial_print("Set\n");
    }
    else if(s[0] == 'C'){
        led_off(s[1]-'1'+1);
        serial_print("Clear\n");
    }else if(s[0] == 'M'){
        if(s[1] == '1'){
        serial_print("Measured value HV BATT: ");
        serial_printd(analog_hv_batt());
        serial_print("\n");
        }
        else{
        serial_print("Measured value HV AIR: ");
        serial_printd(analog_hv_airs());
        serial_print("\n"); 
        }
    }

}
/*Timer1 Interrupt*/
void __ISR(_TIMER_1_VECTOR , IPL1AUTO) InterruptTIMER1(void){
    if(time_interrupt_1()){
        //internal_time ++;
    }
}
/*Timer2 Interrupt*/
void __ISR(_TIMER_2_VECTOR, IPL1AUTO) InterruptTIMER2(void){
    if(time_interrupt_2()){
        internal_time ++;   
    }
}
/*Change Notice pins Interrupt*/
void __ISR(_CHANGE_NOTICE_VECTOR, IPL1AUTO) InterruptSignalChange(void){
    char aux[BUFFER_SIZE];
    int aux1 = gpio_signal_bal_read();
    int aux2 = gpio_signal_shtdwn_read();
    int aux3 = gpio_signal_disch_read();
    int aux4 = gpio_signal_ch_read();
    sprintf(aux, "Signals; BAL: %i, SHTDWN: %i, DSCH: %i, CH: %i\n", aux1, aux2, aux3, aux4);
    serial_print(aux);
    control_signal_interrupt();   
}