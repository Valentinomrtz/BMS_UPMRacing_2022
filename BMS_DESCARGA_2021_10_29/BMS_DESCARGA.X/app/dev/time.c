/* 
 * Time File
 * Device Layer
 */

#include "time.h"
#include <stdbool.h>

#include "lib/timer.h"

int i = 0;
int count1 = 0;
int count2 = 0;
int timer1_limit = 0;
int timer2_limit = 0;

/*Initialization of Time modules*/
void time_init(){
    timer1_init();
    timer2_init();    
}
/*Wait with the specified Timer, the specified number of miliseconds*/
void time_delay(int c, int time_ms){
    switch(c){
        case 1:
            for (i=0; i<2*time_ms; ++i){
                timer1_set();
                while(timer1_check() < 5000);
            }
            break;
        case 2:
            for (i=0; i<2*time_ms; ++i){
                timer2_set();
                while(timer2_check() < 5000);
            }
            break;         
    }
}
/*Wait with the specified Timer, the specified number of microseconds*/
void time_delay_u(int c, int time_us){
    switch(c){
        case 1:
            for (i=0; i<2*time_us; ++i){
                timer1_set();
                while(timer1_check() < 5);
            }
            break;
        case 2:
            for (i=0; i<2*time_us; ++i){
                timer2_set();
                while(timer2_check() < 5);
            }
            break;         
    }
}
/*Set the specified Timer interrupt, with the period specified in miliseconds*/
void time_interrupt_set(int c, int time_ms){
    switch(c){
        case 1:
            timer1_interrupt_set();
            timer1_limit = time_ms;
            count1 = 0;
            break;
        case 2:
            timer2_interrupt_set();
            timer2_limit = time_ms;
            count2 = 0;
            break;         
    }
}
/*Disable the specified Timer interrupt*/
void time_interrupt_disable(int c){
    switch(c){
        case 1:
            timer1_interrupt_disable();
            break;
        case 2:
            timer2_interrupt_disable();
            break;         
    }    
}
/* Timer 1 Interrupt Routine*/
int time_interrupt_1(){
    timer1_interrupt_clear();
    count1++;    
    if(count1 == timer1_limit){
        count1 = 0;
        return 1;
    }else{
        return 0;
    }    
}
/*Timer 2 Interrupt Routine*/
int time_interrupt_2(){
    timer2_interrupt_clear();
    count2++;    
    if(count2 == timer2_limit){
        count2 = 0;
        return 1;
    }else{
        return 0;
    }     
}