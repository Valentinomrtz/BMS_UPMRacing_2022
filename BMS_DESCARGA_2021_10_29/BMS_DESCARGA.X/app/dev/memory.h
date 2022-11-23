/* 
 * Memory Header
 * Device Layer
 */

#ifndef MEMORY_H
#define	MEMORY_H

unsigned int mem_read(unsigned int slot);
void mem_write(unsigned int slot, unsigned int data);
unsigned int mem_read_soc();
void mem_write_soc(unsigned int data);


#endif	/* MEMORY_H */

