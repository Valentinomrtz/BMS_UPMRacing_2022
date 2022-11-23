/* 
 * Memory File 
 * Device Layer
 */
#include "memory.h"

#include "lib/flash.h"

/*Retrieves the value of the specified data slot*/
unsigned int mem_read(unsigned int slot){
    unsigned int count = 0;
    count = flash_next_index(slot);    
    return flash_read_word(slot, count-1);
}
/*Writes the value in the specified data slot*/
void mem_write(unsigned int slot, unsigned int data){
    unsigned int count = 0;
    count = flash_next_index(slot);
    if(count > 1000){
        flash_erase_page(slot);
        count = 0;
    }
    flash_write_word(slot, count, data);
}
/*Retrieves the last SOC value*/
unsigned int mem_read_soc(){
    return mem_read(0);
}
/*Writes SOC value*/
void mem_write_soc(unsigned int data){
    mem_write(0, data);
}
