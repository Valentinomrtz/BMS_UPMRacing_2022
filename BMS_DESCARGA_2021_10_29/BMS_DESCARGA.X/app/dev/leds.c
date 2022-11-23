/* 
 * LEDs File
 * Device layer
 */

#include "leds.h"
#include "lib/gpio.h"

/*Led Initialization*/
void leds_init(){
    gpio_leds_init();
    led_off(3);
    led_off(4);
}
/*Turn ON specified LED*/
void led_on(int i){
    switch(i){
            case 1:
            gpio_led4_set(1);
        break;
        case 2:
            gpio_led5_set(1);
        break;
        case 3:
            gpio_leda_set(1);
        break;
        case 4:
            gpio_ledb_set(1);
        break;  
    }     
}
/*Turn OFF specified LED*/
void led_off(int i){
    switch(i){
        case 1:
            gpio_led4_set(0);
        break;
        case 2:
            gpio_led5_set(0);
        break;
        case 3:
            gpio_leda_set(0);
        break;
        case 4:
            gpio_ledb_set(0);
        break;  
    }      
}
/*Toggle specified LED*/
void led_toggle(int i){
     switch(i){
        case 1:
            gpio_led4_toggle();
        break;
        case 2:
            gpio_led5_toggle();
        break;
        case 3:
            gpio_leda_toggle();
        break;
        case 4:
            gpio_ledb_toggle();
        break;
    }        
    
    
}