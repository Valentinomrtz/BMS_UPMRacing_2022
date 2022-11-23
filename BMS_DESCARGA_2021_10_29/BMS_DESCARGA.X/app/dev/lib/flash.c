/* 
 * FLASH File 
 * Library Layer
 */

#include "flash.h"

#include <p32xxxx.h>
#include <sys/kmem.h>

static const unsigned int buf[N_PAGES][PAGE_WORDS] __attribute__ ((__aligned__(PAGE_SIZE))) = {0};

/*Performs a basic FLASH operation*/
void flash_operation(){
    NVMCONbits.WREN  = 1;   //Enable Write 
    NVMKEY = 0x00000000;    //Unlock Step 0
    NVMKEY = 0xAA996655;    //Unlock Step 1
    NVMKEY = 0x556699AA;    //Unlock Step 2 
    NVMCONSET = 0x8000;      //Begin operation 
    while(NVMCONbits.WR); //Wait for the operation to finish
    NVMCONbits.WREN = 0;    //Disable Write   
}

/*Writes a word in the flash memory*/
void flash_write_word(unsigned int page, unsigned int index, unsigned int data){
    NVMDATA = data;
    NVMADDR = KVA_TO_PA(buf[page] + index);
    NVMCONbits.NVMOP = 1;   //Word Program Operation
    flash_operation();
}
/*Reads a word of the flash memory*/
unsigned int flash_read_word(unsigned int page, unsigned int index){
    if(index<PAGE_WORDS){
        return buf[page][index];
    }
    else{
        return 0;
    }
}
/*Erases the PFM*/
void flash_erase_page(unsigned int page){
    NVMADDR = KVA_TO_PA(buf[page]);
    NVMCONbits.NVMOP = 4;   //Erase Page Operation
    flash_operation();
}
/*Selects the next page*/
unsigned int flash_next_index(unsigned int page){
    unsigned int count = 0;
    while((flash_read_word(page, count) != 0xFFFFFFFF) && (count < PAGE_WORDS-1)){
        count = count + 1;
    }
    return count;    
}
