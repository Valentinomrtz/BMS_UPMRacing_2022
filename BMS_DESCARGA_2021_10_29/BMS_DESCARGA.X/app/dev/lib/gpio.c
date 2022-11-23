/* 
 * GPIO File 
 * Library Layer
 */

#include "gpio.h"

#include <p32xxxx.h>

/* Initialization of the output registers for the LEDs*/
void gpio_leds_init(){
    TRISAbits.TRISA3 = 0;  //Set pin 59/RA3 to output  - LED4 (MAX32))
    TRISCbits.TRISC1 = 0;  //Set pin  6/RC1 to output  - LED5 (MAX32))
    TRISEbits.TRISE1 = 0;  //Set pin 94/RE1 to output  - LEDA
    TRISEbits.TRISE0 = 0;  //Set pin 93/RE0 to output  - LEDB
}
/* Initialization of the output registers for the Relay and Cooling Control*/
void gpio_ctrl_init(){
    TRISDbits.TRISD3 = 0;  //Set pin 78/RD3 to output  - FAN1
    TRISDbits.TRISD2 = 0;  //Set pin 77/RD2 to output  - FAN2
    TRISDbits.TRISD1 = 0;  //Set pin 76/RD1 to output  - FAN3
    
    TRISDbits.TRISD8 = 0;  //Set pin 68/RD8 to output  - PRE
    TRISDbits.TRISD9 = 0;  //Set pin 69/RD9 to output  - AIR-
    TRISDbits.TRISD10= 0;  //Set pin 70/RD10 to output - AIR+
    
    TRISAbits.TRISA2 = 0;  //Set pin 58/RA2 to output  - BMS_FAULT
}
/* Initialization of the input registers for the Control Signals*/
void gpio_sgnl_init(){
    TRISDbits.TRISD4 = 1;  //Set pin 81/RD4/CN13 to input   - BALANCE_MODE
    TRISDbits.TRISD5 = 1;  //Set pin 82/RD5/CN14 to input   - SHTDWN
    TRISDbits.TRISD6 = 1;  //Set pin  83/RD6/CN15 to input  - DISCH_MODE 
    TRISDbits.TRISD13 = 1; //Set pin 80/RD5/CN19 to input   - CH_MODE
    
    CNCONbits.ON = 1;      //Enable Change Notification pins
    CNPUEbits.CNPUE13 = 0; //Internal pull up disabled
    CNPUEbits.CNPUE14 = 0; //Internal pull up disabled
    CNPUEbits.CNPUE15 = 0; //Internal pull up disabled
    CNPUEbits.CNPUE19 = 0; //Internal pull up disabled
    CNENbits.CNEN13 = 1;   //Activate CN13
    CNENbits.CNEN14 = 1;   //Activate CN14
    CNENbits.CNEN15 = 1;   //Activate CN15
    CNENbits.CNEN19 = 1;   //Activate CN19  
    
    /*TRISBbits.TRISB6 = 0;  //Set pin 26/RB6/PGC to output
    TRISBbits.TRISB7 = 0;  //Set pin 27/RB7/PGD to output
    LATBbits.LATB6 = 0;
    LATBbits.LATB7 = 0;
    */
}
/* Initialization of the GPIO Control Notification Interrupt Registers*/
void gpio_interrupt_cn_set(){
    IEC1bits.CNIE = 0;      //Disable Interrupt    
    IPC6bits.CNIP = 1;      //Priority Level
    //IPC6bits.CNIE = 1;    //SubPriority Level   
    IFS1bits.CNIF = 0;      //Clearing Flag bit
    IEC1bits.CNIE = 1;      //Disable Interrupt          
}
/* Clear the CN Interrupt Flag*/
void gpio_interrupt_cn_clear(){
    IFS1bits.CNIF = 0;      //Clearing Flag bit   
}
/* Disable the CN Interrupt*/
void gpio_interrupt_cn_disable(){
    IEC1bits.CNIE = 0;      //Disable Interrupt  
}
/* Set the output to the specified value*/
void gpio_led4_set(int c){
    LATAbits.LATA3 = c; 
}
/* Set the output to the specified value*/
void gpio_led5_set(int c){
    LATCbits.LATC1 = c; 
}
/* Set the output to the specified value*/
void gpio_leda_set(int c){
    LATEbits.LATE1 = c; 
}
/* Set the output to the specified value*/
void gpio_ledb_set(int c){
    LATEbits.LATE0 = c; 
}
/* Set the output to the specified value*/
void gpio_fan1_set(int c){
    LATDbits.LATD3 = c;    
}
/* Set the output to the specified value*/
void gpio_fan2_set(int c){
    LATDbits.LATD2 = c;         
}
/* Set the output to the specified value*/
void gpio_fan3_set(int c){
    LATDbits.LATD1 = c;     
}
/* Set the output to the specified value*/
void gpio_prec_set(int c){
    LATDbits.LATD8 = c;
}
/* Set the output to the specified value*/
void gpio_airn_set(int c){
    LATDbits.LATD9 = c;    
}
/* Set the output to the specified value*/
void gpio_airp_set(int c){
    LATDbits.LATD10= c;
}
/* Set the output to the specified value*/
void gpio_bmsf_set(int c){
    LATAbits.LATA2 = c;
}
/* Toggle the output value*/
void gpio_led4_toggle(){
    LATAbits.LATA3 = ~PORTAbits.RA3;     
}
/* Toggle the output value*/
void gpio_led5_toggle(){
    LATCbits.LATC1 = ~PORTCbits.RC1;   
}
/* Read the input value*/
void gpio_leda_toggle(){
    LATEbits.LATE1 = ~PORTEbits.RE1;     
}
/* Read the input value*/
void gpio_ledb_toggle(){
    LATEbits.LATE0 = ~PORTEbits.RE0;   
}
/* Read the input value*/
int  gpio_signal_bal_read(){
    return PORTDbits.RD4;   
}
int  gpio_signal_shtdwn_read(){
    return PORTDbits.RD5;        
}
/* Read the input value*/
int  gpio_signal_disch_read(){
    return PORTDbits.RD6;        
}
/* Read the input value*/
int  gpio_signal_ch_read(){
    return PORTDbits.RD13;   
}