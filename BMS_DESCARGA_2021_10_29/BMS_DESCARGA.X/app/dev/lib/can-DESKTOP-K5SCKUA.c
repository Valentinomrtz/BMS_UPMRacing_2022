/* 
 * CAN File
 * Library Layer
 */

#include "can.h"

#include <p32xxxx.h>
#include <sys/kmem.h>

#define SID_1 0x146
#define SID_2 0x145
#define EID_1 0x000F3
#define FIFO_RX_SIZE 8
#define FIFO_TX_SIZE 32
#define MB_SIZE 4

/*OPERATION MODE*/
#define MODE_NORM 0 		/*Normal Operation Mode*/
#define MODE_DISA 1 		/*Disable Operation Mode*/
#define MODE_LOOP 2		    /*Loopback Operation Mode*/
#define MODE_LISTEN 3 		/*Listen-Only Operation Mode*/
#define MODE_CONF 4 		/*Configuration Mode*/
#define MODE_LISTENALL 7 	/*Listen All Messages Operation Mode*/

static volatile unsigned int fifo_can1[(FIFO_RX_SIZE + FIFO_TX_SIZE) * MB_SIZE];
//static volatile unsigned int fifo_can2[(FIFO_RX_SIZE + FIFO_TX_SIZE) * MB_SIZE];

/*Initialization of the CAN1 Registers*/
void can1_init(){
    //TRISFbits.TRISF0 = 1;                   //Set pin 87 to input - RX
    //TRISFbits.TRISF1 = 0;                   //Set pin 88 to output - TX
    C1CONbits.ON = 1;                       //Turn on CAN module
    can_mode_set(1, MODE_CONF);             //Set configuration mode
    C1FIFOCON0bits.FSIZE = FIFO_RX_SIZE -1; //Set FIFO RX size
    C1FIFOCON0bits.TXEN = 0;                //RX FIFO
    
    C1FIFOCON1bits.FSIZE = FIFO_TX_SIZE -1; //Set FIFO TX size
    C1FIFOCON1bits.TXEN = 1;                //TX FIFO
    C1FIFOBA = KVA_TO_PA(fifo_can1);        //Indicate FIFO location
    C1RXM0bits.SID = 0x000;                 //Set SID bits mask 0 (no bits must match) 
    C1RXM0bits.EID = 0x00FFF;               //Set EID bits mask (12 bits must match)
    C1RXM0bits.MIDE = 1;                    //Match only message types corresponding to EXID
    C1FLTCON0bits.FSEL0 = 0;                //Filter for FIFO 0 (RX)
    C1FLTCON0bits.MSEL0 = 0;                //Filter 0 uses mask 0
    C1RXF0bits.SID = SID_1;                 //Set SID to match  
    C1RXF0bits.EID = EID_1;                 //Set EID to match
    C1RXF0bits.EXID = 1;                    //Match only messages with extended identifier
    C1FLTCON0bits.FLTEN0 = 1;               //Enable filter
    //Timing configuration Brate = 500 Kbits/s
    C1CFGbits.BRP = 7;                      // Tq = (2 X (BRP + 1))/ Fsys
    C1CFGbits.PRSEG = 2;                    // 3 Tq in propagation segment
    C1CFGbits.SEG1PH = 2;                   // 3 Tq in phase 1 (and 2 auto)
    C1CFGbits.SJW = 0;                      // (SJW+1)*Tq adjustment window
    can_mode_set(1, MODE_NORM);             //Set Loopback mode
    
}
/*Initialization of the CAN2 Registers*/
//void can2_init(){
//    //TRISGbits.TRISG0 = 1;                   //Set pin 90 to input - RX
//    //TRISGbits.TRISG1 = 0;                   //Set pin 89 to output - TX
//    C2CONbits.ON = 1;                       //Turn on CAN module
//    can_mode_set(2, MODE_CONF);             //Set configuration mode
//    C2FIFOCON0bits.FSIZE = FIFO_RX_SIZE -1; //Set FIFO RX size
//    C2FIFOCON0bits.TXEN = 0;                //RX FIFO
//    
//    C2FIFOCON1bits.FSIZE = FIFO_TX_SIZE -1; //Set FIFO TX size
//    C2FIFOCON1bits.TXEN = 1;                //TX FIFO
//    C2FIFOBA = KVA_TO_PA(fifo_can2);        //Indicate FIFOs location
//    C2RXM0bits.SID = 0x000;                 //Set SID bits mask 0 (no bits must match) 
//    C2RXM0bits.EID = 0x00FFF;               //Set EID bits mask (12 bits must match)
//    C1RXM0bits.MIDE = 1;                    //Match only message types corresponding to EXID
//    C2FLTCON0bits.FSEL0 = 0;                //Filter for FIFO 0 (RX)
//    C2FLTCON0bits.MSEL0 = 0;                //Filter 0 uses mask 0
//    C2RXF0bits.SID = SID_1;                 //Set SID to match  
//    C2RXF0bits.EID = EID_1;                 //Set EID to match
//    C2RXF0bits.EXID = 1;                    //Match only messages with extended identifier
//    C2FLTCON0bits.FLTEN0 = 1;               //Enable filter
//    //Timing configuration Brate = 500 Kbits/s
//    C2CFGbits.BRP = 7;                      // Tq = (2 X (BRP + 1))/ Fsys
//    C2CFGbits.PRSEG = 2;                    // 3 Tq in propagation segment
//    C2CFGbits.SEG1PH = 2;                   // 3 Tq in phase 1 (and 2 auto)
//    C2CFGbits.SJW = 0;                      // (SJW+1)*Tq adjustment window
//    can_mode_set(2, MODE_NORM);             //Set Loopback mode
//}
/*Disables CAN1 module*/
void can1_off(){
    can_mode_set(1, MODE_CONF);
    C1CONbits.ON = 0;
    while(C1CONbits.CANBUSY == 1);
}
/*Disables CAN2 module*/
//void can2_off(){
//    can_mode_set(2, MODE_CONF);
//    C2CONbits.ON = 0;  
//    while(C2CONbits.CANBUSY == 1);
//}
/*Sets the CAN mode*/
void can_mode_set(unsigned int can, unsigned int mode){
    switch(can){
        case 1:
            C1CONbits.REQOP = mode;         //Request configuration mode
            while(C1CONbits.OPMOD != mode); //Wait configuration mode
            break;
        case 2: 
            C2CONbits.REQOP = mode;         //Request configuration mode
            while(C2CONbits.OPMOD != mode); //Wait configuration mode
            break;
    }
}

void can1_send(unsigned int* data){
    unsigned int * addr;
    if(C1FIFOINT1bits.TXNFULLIF){
        addr = PA_TO_KVA1(C1FIFOUA1);
        addr[0] = data[0];
        addr[1] = data[1];
        addr[2] = data[2];
        addr[3] = data[3];
        C1FIFOCON1SET = 0x2000;        //Increment FIFO head by 1 message (UINC bit doesn't work)
        C1FIFOCON1bits.TXREQ = 1;       //Request sending data
    }
}

//void can2_send(unsigned int* data){
//    unsigned int * addr;
//    if(C2FIFOINT1bits.TXNFULLIF){
//        addr = PA_TO_KVA1(C2FIFOUA1);
//        addr[0] = data[0];
//        addr[1] = data[1];
//        addr[2] = data[2];
//        addr[3] = data[3];
//        C2FIFOCON1SET = 0x2000;        //Increment FIFO head by 1 message (UINC bit doesn't work)
//        C2FIFOCON1bits.TXREQ = 1;       //Request sending data
//    }
//}


void can1_receive(unsigned int* data){
    unsigned int * addr;
    if(C1FIFOINT0bits.RXNEMPTYIF){
        addr = PA_TO_KVA1(C1FIFOUA0);
        data[0] = addr[0];
        data[1] = addr[1];
        data[2] = addr[2];
        data[3] = addr[3];   
        C1FIFOCON0SET = 0x2000;         //Increment FIFO head by 1 message (UINC bit doesn't work)
    }else{
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        data[3] = 0;
    }
}

//void can2_receive(unsigned int* data){
//    unsigned int * addr;
//    if(C2FIFOINT0bits.RXNEMPTYIF){
//        addr = PA_TO_KVA1(C2FIFOUA0);
//        data[0] = addr[0];
//        data[1] = addr[1];
//        data[2] = addr[2];
//        data[3] = addr[3];   
//        C2FIFOCON0SET = 0x2000;          //Increment FIFO head by 1 message (UINC bit doesn't work)
//    }else{
//        data[0] = 0;
//        data[1] = 0;
//        data[2] = 0;
//        data[3] = 0;
//    }
//}