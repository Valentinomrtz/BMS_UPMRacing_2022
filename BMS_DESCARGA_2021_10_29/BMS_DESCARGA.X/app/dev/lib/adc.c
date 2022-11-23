/* 
 * ADC File
 * Library Layer
 */

#include "adc.h"
#include "timer.h"
#include <p32xxxx.h>

#define CONVERSION_MODE 1           //1 Automatic 0 Manual

/* Initialization of the ADC and Analog input Registers*/
void adc_init(){
    AD1PCFGbits.PCFG5 = 0;          //Set AN5 as analog pin
    AD1PCFGbits.PCFG14 = 0;         //Set AN14 as analog pin
    AD1PCFGbits.PCFG15 = 0;         //Set AN15 as analog pin
  //AD1PCFG = 0xFFFE;               //Alternative
    AD1CON1 = 0;                    //Default Manual mode
    AD1CON1bits.FORM = 0;           //Integer 16 bit format
    if(CONVERSION_MODE){
        AD1CON1bits.SSRC = 0x7;     //Automatic conversion after sampling
        AD1CON3bits.ADCS = 0x3F;    //Conversion Clock Select Bits
    }
    else{               
        AD1CON3bits.ADCS = 0x02;    //Conversion Clock Select Bits 
    }
    AD1CSSL = 0;                    //No scanning required
    AD1CON2 = 0;                    //use MUXA, AVss/AVdd used as Vref   
    AD1CON3bits.ADRC = 0;           //Clock source = PBCLK
    AD1CON3bits.SAMC = 0x1F;        //Auto sample time bits - 31
    AD1CON1bits.ADON = 1;           //Enable ADC    
}

/* Perform an ADC Sample & Read Operation in the specified input*/
int adc_read(int c){
    AD1CHSbits.CH0SA = c;           //Select Analog Input
    AD1CON1bits.SAMP = 1;           //Start sampling
    if(CONVERSION_MODE){
        while(!AD1CON1bits.DONE);   //Wait until the conversion is complete
    }else{
        timer2_set();               //Wait for sampling time
        while(timer2_check() < 200);
        AD1CON1bits.SAMP = 0;       //Start the conversion
        while(!AD1CON1bits.DONE);   //Wait until the conversion is complete       
    }
    return ADC1BUF0;                //Read result     
}