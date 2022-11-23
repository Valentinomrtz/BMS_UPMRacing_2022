/* 
 * GPIO Header
 * Library Layer
 */

#ifndef FLASH_H
#define	FLASH_H

#define N_PAGES 2
#define PAGE_SIZE 4096              //Bytes
#define PAGE_WORDS (PAGE_SIZE/4)    //4-byte Words  

#include <stdint.h>

void flash_operation();
void flash_write_word(unsigned int page,unsigned int index, unsigned int data);
unsigned int flash_read_word(unsigned int page, unsigned int index);
void flash_erase_page(unsigned int page);
unsigned int flash_next_index(unsigned int page);

#endif	/* FLASH_H */

