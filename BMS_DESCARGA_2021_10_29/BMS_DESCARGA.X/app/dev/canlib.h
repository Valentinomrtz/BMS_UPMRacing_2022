/* 
 * CAN Library Header
 * Library Layer
 */

#ifndef CANLIB_H
#define	CANLIB_H

#include <stdint.h>
#include <stdbool.h>
/*CAN Data Structures*/

typedef struct {
    unsigned SID:11;
    unsigned FILHIT:5;
    unsigned CMSGTS:16;
} cmsgsid;

typedef struct {
    unsigned DLC:4;
    unsigned RB0:1;
    unsigned    :3;
    unsigned RB1:1;
    unsigned RTR:1;
    unsigned EID:18;
    unsigned IDE:1;
    unsigned SRR:1;
    unsigned    :2;
} cmsgeid;

typedef union ucmsgadata0 {
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
        
        unsigned Bit16:1;
        unsigned Bit17:1;
        unsigned Bit18:1;
        unsigned Bit19:1;
        unsigned Bit20:1;
        unsigned Bit21:1;
        unsigned Bit22:1;
        unsigned Bit23:1;
        
        unsigned Bit24:1;
        unsigned Bit25:1;
        unsigned Bit26:1;
        unsigned Bit27:1;
        unsigned Bit28:1;
        unsigned Bit29:1;
        unsigned Bit30:1;
        unsigned Bit31:1;
        
    };
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
} cmsgdata0;

typedef union ucmsgadata1 { 
    struct {
        unsigned Bit32:1;
        unsigned Bit33:1;
        unsigned Bit34:1;
        unsigned Bit35:1;
        unsigned Bit36:1;
        unsigned Bit37:1;
        unsigned Bit38:1;
        unsigned Bit39:1;
        
        unsigned Bit40:1;
        unsigned Bit41:1;
        unsigned Bit42:1;
        unsigned Bit43:1;
        unsigned Bit44:1;
        unsigned Bit45:1;
        unsigned Bit46:1;
        unsigned Bit47:1;
        
        unsigned Bit48:1;
        unsigned Bit49:1;
        unsigned Bit50:1;
        unsigned Bit51:1;
        unsigned Bit52:1;
        unsigned Bit53:1;
        unsigned Bit54:1;
        unsigned Bit55:1;
        
        unsigned Bit56:1;
        unsigned Bit57:1;
        unsigned Bit58:1;
        unsigned Bit59:1;
        unsigned Bit60:1;
        unsigned Bit61:1;
        unsigned Bit62:1;
        unsigned Bit63:1;
        
    };
    struct{
        unsigned Byte4:8;
        unsigned Byte5:8;
        unsigned Byte6:8;
        unsigned Byte7:8;
    };
    struct{
        unsigned Word2:16;
        unsigned Word3:16; 
        unsigned Word4:16;
        unsigned Word5:16; 
    };

} cmsgdata1;

typedef union uCANMessageBuffer {
    struct{
        cmsgsid     CMSGSID;
        cmsgeid     CMSGEID;
        cmsgdata0   CMSGDATA0;
        cmsgdata1   CMSGDATA1;
    }; 
    int messageWord[4];
} CANMessageBuffer;


void can_init();
void can_reset();
void can_send_msg(unsigned int, unsigned int, uint16_t[4]);
void can_send_msg_sd(unsigned int, uint16_t [4]);
void can_send_msg_sd_info(unsigned int, uint16_t [4]);
void can_send_msg_8(unsigned int, unsigned int, uint8_t[8]);
void can_send_msg_8_sd(unsigned int, uint8_t[8]);
void can_send_msg_ch(unsigned int, unsigned int, uint8_t[2], uint16_t[2]);
void can_send_msg_limits(unsigned int, unsigned int, uint16_t[2], uint8_t[1]);

unsigned int can_test();

#endif	/* CANLIB_H */

