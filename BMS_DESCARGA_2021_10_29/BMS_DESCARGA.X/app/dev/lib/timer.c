/* 
 * Timer File
 * Library Layer
 */

#include "timer.h"
#include <p32xxxx.h>

/* Initialization of the Timer 1 registers */
void timer1_init(){
    T1CONbits.ON = 0;       //Disable timer
    T1CONbits.TCS = 0;      //Internal Peripheral Clock
    T1CONbits.TCKPS0 = 1;   //1:8 prescale value (clock divider)
    T1CONbits.TCKPS1 = 0;
    T1CONbits.TSYNC = 0;
    T1CONbits.TGATE = 0;    //Default value
    T1CONbits.SIDL = 0;     //Default value    
    T1CONbits.ON = 1;       //Enable timer
    TMR1 = 0;               //Clear timer register
    PR1 = 10000;            //Load timer reset count value  
}

/* Initialization of the Timer 2 registers */
void timer2_init(){
    T2CONbits.ON = 0;       //Disable timer
    T2CONbits.TCS = 0;      //Internal Peripheral Clock
    T2CONbits.TCKPS0 = 1;   //1:8 prescale value (clock divider)
    T2CONbits.TCKPS1 = 1;    
    T2CONbits.TCKPS2 = 0;    
    T2CONbits.TGATE = 0;    //Default value
    T2CONbits.T32 = 0;      //Independent 16 bit timers
    T2CONbits.SIDL = 0;     //Default value  
    T2CONbits.ON = 1;       //Enable timer
    TMR2 = 0;               //Clear timer register
    PR2 = 10000;            //Load timer reset count value  
}

/* Clear Timer 1 counter */
void timer1_set(){
    TMR1 = 0;               //Clear timer register 
}

/* Clear Timer 2 counter*/
void timer2_set(){
    TMR2 = 0;               //Clear timer register    
}

/* Read Timer 1 counter*/
int timer1_check(){
    return TMR1;
}

/* Read Timer 2 counter*/
int timer2_check(){
    return TMR2;
}

/* Initialization of the Timer 1 Interrupt registers*/
void timer1_interrupt_set(){
    IEC0bits.T1IE = 0;      //Disable Interrupt    
    IPC1bits.T1IP = 1;      //Priority Level
  //IPC1bits.T1IS = 1;      //SubPriority Level   
    IFS0bits.T1IF = 0;      //Clearing Flag bit
    IEC0bits.T1IE = 1;      //Enable Interrupt     
}

/* Initialization of the Timer 2 Interrupt registers*/
void timer2_interrupt_set(){
    IEC0bits.T2IE = 0;      //Disable Interrupt 
    IPC2bits.T2IP = 1;      //Priority Level
  //IPC2bits.T2IS = 1;      //SubPriority Level 
    IFS0bits.T2IF = 0;      //Clearing Flag bit
    IEC0bits.T2IE = 1;      //Enable Interrupt      
}

/* Clear the Timer 1 Interrupt Flag*/
void timer1_interrupt_clear(){
    IFS0bits.T1IF = 0;      //Clearing Flag bit   
}

/* Clear the Timer 2 Interrupt Flag*/
void timer2_interrupt_clear(){
    IFS0bits.T2IF = 0;      //Clearing Flag bit        
}

/* Disable the Timer 1 Interrupt*/
void timer1_interrupt_disable(){
    IEC0bits.T1IE = 0;      //Disable Interrupt          
}

/* Disable the Timer 2 Interrupt*/
void timer2_interrupt_disable(){
    IEC0bits.T2IE = 0;      //Disable Interrupt    
}