/*
 *  Output Communication Header
 *  Application layer
 */



#ifndef OUTPUT_COMM_H
#define	OUTPUT_COMM_H

#include "main_config.h"

typedef union uUartMessage4Bytes {
    struct {
        unsigned Byte0:8;
        unsigned Byte1:8;
        unsigned Byte2:8;
        unsigned Byte3:8;
    };
    struct {
        unsigned Word0:16;
        unsigned Word1:16;
    };
    struct {
        unsigned Msg:32;
    };
    struct {
        uint8_t ByteArray[4];
    };
} UartMessage4Bytes;

typedef union uUartMessage2Bytes {
    struct {
        unsigned Bit0:1;
        unsigned Bit1:1;
        unsigned Bit2:1;
        unsigned Bit3:1;
        unsigned Bit4:1;
        unsigned Bit5:1;
        unsigned Bit6:1;
        unsigned Bit7:1;
        unsigned Bit8:1;
        unsigned Bit9:1;
        unsigned Bit10:1;
        unsigned Bit11:1;
        unsigned Bit12:1;
        unsigned Bit13:1;
        unsigned Bit14:1;
        unsigned Bit15:1;        
    };
    struct {
        unsigned Byte0:8;
        unsigned Byte1:8;
    };
    struct {
        unsigned Msg:16;
    };
    struct {
        uint8_t ByteArray[2];
    };
} UartMessage2Bytes;

typedef union uUartMessage1Bytes {
    struct {
        unsigned Msg:8;
    };
    struct {
        uint8_t ByteArray[1];
    };
} UartMessage1Bytes;


void led_control(bms*);
void pc_comm(bms*);
void lite_comm(bms*);
void can_comm_v(bms*); //TO DO
void can_comm_t(bms*);

void signal_status(bms* bms);
void mode_status(bms* bms);
void hv_status(bms* bms);
void slaves_status(bms* bms);
void error_0_status(bms* bms);
void error_1_status(bms* bms);
void error_2_status(bms* bms);
void relay_status(bms* bms);
void cooling_status(bms* bms);
void balance_status(bms* bms);
void can_status(bms* bms);

void gui_comm(bms* bms);
void gui_msg_short(UartMessage2Bytes id, UartMessage1Bytes data, UartMessage2Bytes eof);
void gui_msg(UartMessage2Bytes id, UartMessage2Bytes data, UartMessage2Bytes eof);
void gui_msg_long(UartMessage2Bytes id, UartMessage4Bytes data, UartMessage2Bytes eof);
void can_comm_cellv(bms* bms);
void can_comm_cellt(bms* bms);
void can_comm_overall(bms* bms);
void can_comm_charge(bms* bms);
void can_comm_cell_info(bms* bms);


#endif	/* OUTPUT_COMM_H */

