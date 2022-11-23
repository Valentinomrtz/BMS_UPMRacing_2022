/* 
 * UART File 
 * Library Layer
 */

#include "uart.h"
#include <stdint.h>
#include <p32xxxx.h>

#define BRATE 173   //Baud Rate

/* Initialization of the UART Registers */
void uart_init(){
    U1BRG = BRATE;          //Set Baud rate to 115200 BRATE = FPB/(4*(BRG+1))
    U1MODEbits.ON = 0;      //Disable UART
    U1MODEbits.PDSEL = 0;   //8-bit data, no parity
    U1MODEbits.STSEL = 0;   //1 Stop bit
    U1MODEbits.BRGH = 1;    //High Baud Rate Enable 4x 
    U1STAbits.URXEN = 1;    //Enable Receiver
    U1STAbits.UTXEN = 1;    //Enable Transmitter
    U1MODEbits.ON = 1;      //Enable UART       
}

/* Initialization of the UART RX Interrupt Registers */
void uart_interrupt_rx_set(){
    IEC0bits.U1RXIE = 0;    //Disable interrupt    
    IPC6bits.U1IP = 1;      //Priority level
    //IPC6bits.U1IS = 1;    //Subpriority level
    U1STAbits.URXISEL = 0;  //UART Interrupt mode    
    IFS0bits.U1RXIF = 0;    //Clearing Flag bit
    IEC0bits.U1RXIE = 1;    //Enable interrupt
}

/* Clear the RX Interrupt Flag*/
void uart_interrupt_rx_clear(){
    IFS0bits.U1RXIF = 0;//Clearing Flag bit    
}

/* Put a byte in the TX Buffer*/
void uart_put(int8_t c){
    while(U1STAbits.UTXBF); //Wait while TX buffer full
    U1TXREG = c;            //Put a byte in the buffer
}

/*Take a byte from the RX buffer*/
char uart_get(){
    while(!U1STAbits.URXDA);//Wait for a new char to arrive
    return U1RXREG;         //Read char from receive buffer
}