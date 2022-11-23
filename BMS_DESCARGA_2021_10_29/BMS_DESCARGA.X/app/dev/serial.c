/* 
 * Serial File
 * Device layer
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "serial.h"
#include "lib/uart.h"

#define BUFFER_SIZE 128
char hex[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

/*Initialization of the Serial interface*/
void serial_init(){
    uart_init();
    uart_interrupt_rx_set();
}
/*Print a string of characters*/
void serial_print(char* s){
    while(*s){
        uart_put(*s);
        *s++;
    }      
}
/*Print a double variable*/
void serial_printd(double s){
    char aux[BUFFER_SIZE];
    sprintf(aux, " %1.1f ", s);
    serial_print(aux);    
}
/*Print a float variable*/
void serial_printf(float s){
    char aux[BUFFER_SIZE];
    sprintf(aux, " %1.4f ", s);
    serial_print(aux);    
}
/*Print an hexadecimal variable*/
void serial_printhex(int b){
    int d2,d1;
    char aux[BUFFER_SIZE];
    d2 = b/16;
    d1 = b%16;
    sprintf(aux, "0x%c%c ", hex[d2], hex[d1]);
    serial_print(aux);
}
/*Prints an array of bits*/
void serial_printbytes(uint8_t* bytes, uint8_t len){
    uint8_t i;
    for(i=0; i<len; i++){
        uart_put(bytes[i]); 
    } 
}
/*Scan a string of characters*/
void serial_scan(char* s){
    int len = BUFFER_SIZE;
    do{
        *s = uart_get();
        if(*s == '\n'){
            break;
        }
        s++;
        len--;
    } while(len > 1);
    *s = '\0';       
}
/*Serial RX Interrupt*/
void serial_interrupt(char* s){
    serial_scan(s);
    serial_print("Message received: ");
    serial_print(s);
    serial_print("\n");
    uart_interrupt_rx_clear();
}