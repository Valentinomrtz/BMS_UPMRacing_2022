/* 
 * Analog File
 * Device Layer
 */

#include "analog.h"

#include "lib/adc.h"

/* Initialization of the ADC function*/
void analog_init(){
    adc_init();  
}
/* Measure the Battery HV value*/
float analog_hv_batt(){
    int value;
    float aux;
    value = adc_read(14);
    aux = ((value/1023.0)*3.3)*301;
    return aux;
}
/* Measure the AIRs HV value*/
float analog_hv_airs(){
    int value;
    float aux;
    value = adc_read(15);
    aux = ((value/1023.0)*3.3)*301;
    return aux;
}
/* Measure the current value*/
float analog_hv_current(){
    int value;
    float aux;
    value = adc_read(5);
    aux = value;//(((value/1023.0)*3.3)-2.5)*200/1.25;   
    return aux;
}