/* 
 * SPI File
 * Library Layer
 */

#include "spi.h"

#include <p32xxxx.h>
#include <stdint.h>

#define SPI_BAUD_025MHz 159
#define SPI_BAUD_05MHz  79
#define SPI_BAUD_1MHz   39
#define SPI_BAUD_2MHz   19
#define SPI_BAUD_4MHz   9

/* Initialization of the SPI Registers*/
void spi_init(){
    TRISGbits.TRISG6 = 0;   //Set pin 10/RG6 to output - SCK
    TRISGbits.TRISG7 = 1;   //Set pin 11/RG7 to input - SDI/MISO
    TRISGbits.TRISG8 = 0;   //Set pin 12/RG8 to output - SDO/MOSI    
    TRISGbits.TRISG9 = 0;   //Set pin 14/RG9 to output  - CSB

    SPI2CONbits.ON = 0;     //Disable SPI
    SPI2BUF = 0;            //Clear buffer
    SPI2CONbits.ENHBUF = 0; //Normal buffer mode
    SPI2CONbits.CKE = 1;    //Changes from active to idle (Low to High)
    SPI2CONbits.CKP = 1;    //Idle state for clock is high level
    SPI2CONbits.MSTEN = 1;  //Master Mode
    SPI2CONbits.SMP = 1;    //Input data sampled at the end of data output time
    SPI2CONbits.MODE16 = 0; //8-bit mode
    SPI2CONbits.MODE32 = 0;
    SPI2STATbits.SPIROV = 0;
    SPI2BRG = SPI_BAUD_025MHz;//SCK 1MHz Baud Rate: FPB/(2*(BRG+1))
    SPI2CONbits.ON = 1;     //Enable SPI
}

/* Transfer a byte through the SPI Buffer*/
uint8_t spi_transfer(uint8_t c){
    SPI2BUF = c;
    while(!SPI2STATbits.SPIRBF);
    return SPI2BUF;
}

/* Set the CSB pin*/
void spi_csb_set(){
    LATGbits.LATG9 = 1;
}

/* Clear the CSB pin*/
void spi_csb_clear(){
    LATGbits.LATG9 = 0;    
}

/*Read one byte of the SPI Buffer*/
uint8_t spi_read(){
    uint8_t data;
    data = spi_transfer(0xFF);
    return data;   
}

/*Write one byte in the SPI Buffer*/
void spi_write(uint8_t data){
    spi_transfer(data);    
}

/*Read an array of bytes in the SPI Buffer*/
void spi_read_array(uint8_t *data, uint8_t len){
    uint8_t i;
    for(i = 0; i < len; ++i){
        data[i] = spi_read();        
    }   
}

/*Write an array of bytes in the SPI Buffer*/
void spi_write_array(uint8_t data[], uint8_t len){
    uint8_t i;
    for(i = 0; i < len; ++i){
        spi_write(data[i]);        
    }
}

/* Perform a Write/Read sequence*/
void spi_read_write(uint8_t data_tx[], uint8_t len_tx, uint8_t *data_rx, uint8_t len_rx){
    spi_write_array(data_tx, len_tx);
    spi_read_array(data_rx, len_rx);    
}