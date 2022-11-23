/* 
 * CAN Library File 
 * Device Layer
 */

#include "canlib.h"
#include "lib/can.h"
#include "serial.h"
#include <stdio.h>

void can_init(){
    can1_init();
    //can2_init();
}

void can_reset(){
    can1_off();
    //can2_off();
    can1_init();
    //can2_init();
}

void can_send_msg_sd(unsigned int SID, unsigned int data[4]){
    CANMessageBuffer can_tx;
    can_tx.CMSGSID.SID = SID;
    can_tx.CMSGEID.IDE = 0;
    can_tx.CMSGEID.DLC = 8;
    can_tx.CMSGDATA0.Word0 = data[0];
    can_tx.CMSGDATA0.Word1 = data[1];
    can_tx.CMSGDATA1.Word2 = data[2];
    can_tx.CMSGDATA1.Word3 = data[3];
    can1_send(can_tx.messageWord);
}

void can_send_msg(unsigned int SID, unsigned int EID, unsigned int data[4]){
    CANMessageBuffer can_tx;
    can_tx.CMSGSID.SID = SID;
    can_tx.CMSGEID.EID = EID;
    can_tx.CMSGEID.IDE = 1;
    can_tx.CMSGEID.DLC = 8;
    can_tx.CMSGDATA0.Word0 = data[0];
    can_tx.CMSGDATA0.Word1 = data[1];
    can_tx.CMSGDATA1.Word2 = data[2];
    can_tx.CMSGDATA1.Word3 = data[3];
    can1_send(can_tx.messageWord);
}

void can_send_msg_8_sd(unsigned int SID, uint8_t data[5]){
    CANMessageBuffer can_tx;
    can_tx.CMSGSID.SID = SID;
    can_tx.CMSGEID.IDE = 0;
    can_tx.CMSGEID.DLC = 8;
    can_tx.CMSGDATA0.Byte0 = data[0];
    can_tx.CMSGDATA0.Byte1 = data[1];
    can_tx.CMSGDATA0.Byte2 = data[2];
    can_tx.CMSGDATA0.Byte3 = data[3];
    can_tx.CMSGDATA1.Byte4 = data[4];
    can_tx.CMSGDATA1.Byte5 = 0;
    can_tx.CMSGDATA1.Byte6 = 0;
    can_tx.CMSGDATA1.Byte7 = 0;
    can1_send(can_tx.messageWord);
}

void can_send_msg_8(unsigned int SID, unsigned int EID, uint8_t data[8]){
    CANMessageBuffer can_tx;
    can_tx.CMSGSID.SID = SID;
    can_tx.CMSGEID.EID = EID;
    can_tx.CMSGEID.IDE = 1;
    can_tx.CMSGEID.DLC = 8;
    can_tx.CMSGDATA0.Byte0 = data[0];
    can_tx.CMSGDATA0.Byte1 = data[1];
    can_tx.CMSGDATA0.Byte2 = data[2];
    can_tx.CMSGDATA0.Byte3 = data[3];
    can_tx.CMSGDATA1.Byte4 = data[4];
    can_tx.CMSGDATA1.Byte5 = data[5];
    can_tx.CMSGDATA1.Byte6 = data[6];
    can_tx.CMSGDATA1.Byte7 = data[7];
    can1_send(can_tx.messageWord);
}

unsigned int can_test(){
    char aux[256];
    unsigned int data[4] = {4250, 3900, 4060, 3980};
    CANMessageBuffer can_rx;
    can_send_msg(0x147,0x140F3,data);
    /*can2_receive(can_rx.messageWord);
    sprintf(aux, "CAN Message: SID: %u EID: %u DLC: %u\n",can_rx.CMSGSID.SID,can_rx.CMSGEID.EID, can_rx.CMSGEID.DLC);
    serial_print(aux);
    sprintf(aux,"DATA: Value 0: %u Value 1: %u \n", can_rx.CMSGDATA0.Word0, can_rx.CMSGDATA0.Word1);
    serial_print(aux);
    sprintf(aux,"DATA: Value 2: %u Value 3: %u \n", can_rx.CMSGDATA1.Word2, can_rx.CMSGDATA1.Word3);
    serial_print(aux);*/
    return can_rx.CMSGDATA1.Word3;
}