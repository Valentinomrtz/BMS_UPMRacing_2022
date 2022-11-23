/* 
 * LTC File
 * Device Layer
 */

#include "ltc.h"
#include "time.h"
#include "lib/spi.h"
#include <stdlib.h>
#include <stdint.h>

/*SPI initialization*/
void ltc_init(){    
    spi_init();
    spi_csb_set();
    //ltc_init_pec_table()
}
/*Changes isoSPI from IDLE to READY*/
void ltc_wakeup_idle(uint8_t n_slaves){
    uint8_t i;
    for(i=0; i<n_slaves; ++i){
        spi_csb_clear();
        spi_read();
        spi_csb_set();              
    }
}
/*Changes LTC6811 from SLEEP to STANDBY*/
void ltc_wakeup_sleep(uint8_t n_slaves){
    uint8_t i;
    for(i=0; i<n_slaves; ++i){
        spi_csb_clear();
        time_delay_u(1,20);
        spi_csb_set();   
        time_delay_u(1,10);        
    }      
}
/*Writes LTC6811 commands*/
void ltc_cmd(uint8_t tx_cmd[2]){
    uint8_t cmd[4];             //2 bytes for the CMD and 2 for the PEC
    uint16_t cmd_pec;
    
    cmd[0] = tx_cmd[0];
    cmd[1] = tx_cmd[1];
    cmd_pec = ltc_pec(2, cmd);
    cmd[2] = (uint8_t)(cmd_pec >> 8);
    cmd[3] = (uint8_t)(cmd_pec);
    
    spi_csb_clear();
    spi_write_array(cmd, 4);
    spi_csb_set();
}
/*Writes LTC6811 commands and payload data*/
void ltc_write(uint8_t n_slaves, uint8_t tx_cmd[2], uint8_t data[]){
    const uint8_t BYTES_IN_REG = 6;
    const uint8_t CMD_LEN = 4 + (8*n_slaves);
    uint8_t *cmd;
    uint16_t data_pec;
    uint16_t cmd_pec;
    uint8_t cmd_index;
    
    cmd = (uint8_t *) malloc(CMD_LEN*sizeof(uint8_t));   
    cmd[0] = tx_cmd[0];
    cmd[1] = tx_cmd[1];
    cmd_pec = ltc_pec(2, cmd);
    cmd[2] = (uint8_t)(cmd_pec >> 8);
    cmd[3] = (uint8_t)(cmd_pec);    
    cmd_index = 4;
    
    uint8_t slave, current_byte;
    
    for(slave = n_slaves; slave > 0; slave--){
        for(current_byte = 0; current_byte < BYTES_IN_REG; current_byte++){
            cmd[cmd_index] = data[((slave-1)*6)+current_byte];
            cmd_index = cmd_index + 1;
        }
        data_pec = (uint16_t) ltc_pec(BYTES_IN_REG, &data[(slave-1)*6]);
        cmd[cmd_index] = (uint8_t)(data_pec >> 8);
        cmd[cmd_index + 1] = (uint8_t)data_pec;
        cmd_index = cmd_index + 2;      
    }
    spi_csb_clear();
    spi_write_array(cmd,CMD_LEN);
    spi_csb_set();
            
    free(cmd);        
}
/*Writes LTC6811 commands and reads data*/
int8_t ltc_read(uint8_t n_slaves, uint8_t tx_cmd[2], uint8_t *rx_data){
    const uint8_t BYTES_IN_REG = 8;
    uint8_t cmd[4];
	uint8_t data[256];
	int8_t pec_error = 0;
	uint16_t cmd_pec;
	uint16_t data_pec;
	uint16_t received_pec;    
    
    cmd[0] = tx_cmd[0];
	cmd[1] = tx_cmd[1];
	cmd_pec = ltc_pec(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec); 

    spi_csb_clear();
    spi_read_write(cmd, 4, data, (BYTES_IN_REG*n_slaves));
    spi_csb_set();    
    
    uint8_t slave, current_byte;
    
    for(slave = 0; slave < n_slaves; slave++){
        for(current_byte = 0; current_byte < BYTES_IN_REG; current_byte++){
            rx_data[(slave*8)+current_byte] = data[current_byte + (slave*BYTES_IN_REG)];
        }
        received_pec = (rx_data[(slave*8)+6]<<8) + rx_data[(slave*8)+7];
        data_pec = ltc_pec(6, &rx_data[slave*8]);
    }
    if(received_pec != data_pec){
       pec_error = -1;
    }
    return pec_error;
}
/*Calcultes the Cyclic Redundancy Check CRC*/
uint16_t ltc_pec(uint8_t len, uint8_t *data){
    uint16_t remainder, addr;
    remainder = 16;
    uint8_t i;
    for(i=0; i<len; ++i){
        addr = ((remainder>>7)^data[i])&0xff;
		remainder = (remainder<<8)^crc15Table[addr];        
    }
    return(remainder*2);    // Fitting the 15 bits CRC in a 16 bits word
}
/*Alternative function to calculate the CRC table*/
void ltc_init_pec_table(){ 
    uint16_t CRC15_POLY = 0x4599; 
    uint16_t remainder;
    uint8_t i, bit;
    for (i = 0; i < 256; i++){ 
        remainder = i << 7;  
        for (bit = 8; bit > 0; --bit){   
            if (remainder & 0x4000){    
                remainder = ((remainder << 1));    
                remainder = (remainder ^ CRC15_POLY);   
            }   
            else{    
                remainder = ((remainder << 1));   
            }  
        }  
        crc15Table[i] = remainder&0xFFFF; 
    }
}
/*Command WRCFG - Writes Configuration Register*/
void ltc_wrcfga(uint8_t total_ic, cell_asic ic[]){
    uint8_t cmd[2] = {0x00, 0x01};
    uint8_t write_buffer[256];
    uint8_t write_count = 0;
    uint8_t c_ic = 0;
    uint8_t current_ic;
    for(current_ic = 0; current_ic < total_ic; current_ic++){       
        c_ic = total_ic - current_ic - 1; //First command sent to the last IC
        uint8_t data;
        for(data = 0; data < 6; data ++){
            write_buffer[write_count] = ic[c_ic].config.tx_data[data];
            write_count++;
        }
    }
    ltc_write(total_ic, cmd, write_buffer);
}
/*Command RDCFG - Reads Configuration Register*/
int8_t ltc_rdcfga(uint8_t total_ic, cell_asic ic[]){
    uint8_t cmd[2] = {0x00, 0x02};
    uint8_t read_buffer[256];
    int8_t pec_error = 0;
    uint16_t data_pec;
    uint16_t calc_pec;    
    uint8_t c_ic = 0;
    uint8_t current_ic;
    pec_error = ltc_read(total_ic, cmd, read_buffer);
    for(current_ic = 0; current_ic < total_ic; current_ic++){
        c_ic = current_ic;      //First command received from the first IC
        int byte;
        for(byte = 0; byte < 8; byte++){
            ic[c_ic].config.rx_data[byte] = read_buffer[byte+(8*current_ic)];
        }
        
        calc_pec = ltc_pec(6, &read_buffer[8*current_ic]);
        data_pec = read_buffer[7+(8*current_ic)] | (read_buffer[6+(8*current_ic)]<<8);
        if(calc_pec != data_pec){
            ic[c_ic].config.rx_pec_match = 1;
        }else{
            ic[c_ic].config.rx_pec_match = 0;
        }
    }    
    ltc_check_pec(total_ic, CFGR, ic);

    return(pec_error);    
}
/*Command ADCV - Start Cell Voltage ADC Conversion*/
void ltc_adcv(uint8_t MD, uint8_t DCP, uint8_t CHG){
    uint8_t cmd[4];
    uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + 0x60 + CHG ;
	
	ltc_cmd(cmd);
}
/*Command ADAX - Start GPIOs+Vref2 ADC Conversion*/
void ltc_adax(uint8_t MD, uint8_t CHG){
    uint8_t cmd[4];
	uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + 0x60 + CHG ;
	
	ltc_cmd(cmd);
}
/*Command ADSTAT - Start Status Group ADC Conversion*/
void ltc_adstat(uint8_t MD, uint8_t CHST){
	uint8_t cmd[4];
	uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + 0x68 + CHST ;
	
	ltc_cmd(cmd);      
}
/*Command ADCVAX - Start Combined Cell Voltage and GPIO1, GPIO2 Conversion*/
void ltc_adcvax(uint8_t MD, uint8_t DCP){
	uint8_t cmd[2];
	uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits | 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] =  md_bits | ((DCP&0x01)<<4) + 0x6F;
	
	ltc_cmd(cmd);   
}
/*Command ADCVSC - Start Combined Cell Voltage and SOC Conversion*/
void ltc_adcvsc(uint8_t MD, uint8_t DCP){
	uint8_t cmd[2];
	uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits | 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] =  md_bits | 0x60 | (DCP<<4) | 0x07;
	
	ltc_cmd(cmd);
}
/*Command RDCV - Read Cell Voltage Registers*/
uint8_t ltc_rdcv(uint8_t reg, uint8_t total_ic, cell_asic* ic){
	int8_t pec_error = 0;
	uint8_t *cell_data;
	uint8_t c_ic = 0;
    uint8_t current_ic;
	cell_data = (uint8_t *) malloc((NUM_RX_BYT*total_ic)*sizeof(uint8_t)); 
    
    if (reg == 0){
        uint8_t cell_reg;
		for (cell_reg = 1; cell_reg < ic[0].ic_reg.num_cv_reg+1; cell_reg++){
			ltc_rdcv_reg(cell_reg, total_ic,cell_data);
			for (current_ic = 0; current_ic < total_ic; current_ic++){
                c_ic = current_ic; //First command received from the first IC
                pec_error = pec_error + ltc_parse_cells(current_ic,cell_reg, cell_data,
												&ic[c_ic].cells.c_codes[0],
												&ic[c_ic].cells.pec_match[0]);
			}
		}
	}else{
		ltc_rdcv_reg(reg, total_ic, cell_data);
		for (current_ic = 0; current_ic < total_ic; current_ic++){
            c_ic = current_ic; //First command received from the first IC
			pec_error = pec_error + ltc_parse_cells(current_ic,reg, &cell_data[8*c_ic],
											  &ic[c_ic].cells.c_codes[0],
											  &ic[c_ic].cells.pec_match[0]);
		}
	}
	ltc_check_pec(total_ic,CELL,ic);
	free(cell_data);
	return(pec_error);         
}
/*Command RDAUX - Read Auxiliary Registers*/
int8_t ltc_rdaux(uint8_t reg, uint8_t total_ic, cell_asic* ic){
    uint8_t *data;
	int8_t pec_error = 0;
	uint8_t c_ic =0;
    uint8_t current_ic, gpio_reg;
	data = (uint8_t *) malloc((NUM_RX_BYT*total_ic)*sizeof(uint8_t));
	if (reg == 0){
		for (gpio_reg = 1; gpio_reg<ic[0].ic_reg.num_gpio_reg+1; gpio_reg++){
			ltc_rdaux_reg(gpio_reg, total_ic, data); 
			for (current_ic = 0; current_ic < total_ic; current_ic++){
				c_ic = current_ic; //First command received from the first IC
				pec_error = ltc_parse_cells(current_ic,gpio_reg, data,
                                            &ic[c_ic].aux.a_codes[0],
                                            &ic[c_ic].aux.pec_match[0]);
			}
		}
	}
	else{
		ltc_rdaux_reg(reg, total_ic, data);
		for (current_ic = 0; current_ic < total_ic; current_ic++){
            c_ic = current_ic; //First command received from the first IC
			pec_error = ltc_parse_cells(current_ic,reg, data,
								  &ic[c_ic].aux.a_codes[0],
								  &ic[c_ic].aux.pec_match[0]);
		}
	}
	ltc_check_pec(total_ic,AUX,ic);
	free(data);
	return (pec_error);       
}
/*Command RDSTAT - Read Status Registers*/
int8_t ltc_rdstat(uint8_t reg, uint8_t total_ic, cell_asic* ic){
    const uint8_t BYT_IN_REG = 6;
	const uint8_t STAT_IN_REG = 3;
	uint8_t *data;
	uint8_t data_counter = 0;
	int8_t pec_error = 0;
	uint16_t parsed_stat;
	uint16_t received_pec;
	uint16_t data_pec;
	uint8_t c_ic = 0;
	uint8_t current_ic, current_stat, stat_reg;
	data = (uint8_t *) malloc((12*total_ic)*sizeof(uint8_t));
	
	if (reg == 0){
		for (stat_reg = 1; stat_reg< 3; stat_reg++){
			data_counter = 0;
			ltc_rdstat_reg(stat_reg, total_ic,data);
			for (current_ic = 0 ; current_ic < total_ic; current_ic++){
				c_ic = current_ic; //First command received from the first IC
				if (stat_reg ==1){
					for (current_stat = 0; current_stat< STAT_IN_REG; current_stat++){
						parsed_stat = data[data_counter] + (data[data_counter+1]<<8);
						ic[c_ic].stat.stat_codes[current_stat] = parsed_stat;
						data_counter=data_counter+2;
					}
				}
				else if (stat_reg == 2){
					parsed_stat = data[data_counter] + (data[data_counter+1]<<8);
					data_counter = data_counter +2;
					ic[c_ic].stat.stat_codes[3] = parsed_stat;
					ic[c_ic].stat.flags[0] = data[data_counter++];
					ic[c_ic].stat.flags[1] = data[data_counter++];
					ic[c_ic].stat.flags[2] = data[data_counter++];
					ic[c_ic].stat.mux_fail[0] = (data[data_counter] & 0x02)>>1;
					ic[c_ic].stat.thsd[0] = data[data_counter++] & 0x01;
				}
				received_pec = (data[data_counter]<<8)+ data[data_counter+1];
				data_pec = ltc_pec(BYT_IN_REG, &data[current_ic*NUM_RX_BYT]);
				if (received_pec != data_pec){
					pec_error = -1;
					ic[c_ic].stat.pec_match[stat_reg-1] = 1;	
				}
				else{
					ic[c_ic].stat.pec_match[stat_reg-1] = 0;
				}
				data_counter=data_counter+2;
			}
		}
	}
	else{
		ltc_rdstat_reg(reg, total_ic, data);
		for (current_ic = 0 ; current_ic < total_ic; current_ic++){
                c_ic = current_ic;   //First command received from the first IC
            if (reg ==1){
                uint8_t current_stat;
				for (current_stat = 0; current_stat< STAT_IN_REG; current_stat++){	
					parsed_stat = data[data_counter] + (data[data_counter+1]<<8);
					ic[c_ic].stat.stat_codes[current_stat] = parsed_stat;
					data_counter=data_counter+2;
				}
			}else if (reg == 2){
				parsed_stat = data[data_counter++] + (data[data_counter++]<<8);
				ic[c_ic].stat.stat_codes[3] = parsed_stat;
				ic[c_ic].stat.flags[0] = data[data_counter++];
				ic[c_ic].stat.flags[1] = data[data_counter++];
				ic[c_ic].stat.flags[2] = data[data_counter++];
				ic[c_ic].stat.mux_fail[0] = (data[data_counter] & 0x02)>>1;
				ic[c_ic].stat.thsd[0] = data[data_counter++] & 0x01;
			}
			received_pec = (data[data_counter]<<8)+ data[data_counter+1]; 
			data_pec = ltc_pec(BYT_IN_REG, &data[current_ic*NUM_RX_BYT]);
			if (received_pec != data_pec){
				pec_error = -1;                
				ic[c_ic].stat.pec_match[reg-1]=1;
			}
			data_counter=data_counter+2;
		}
	}
	ltc_check_pec(total_ic,STAT,ic);	
	free(data);	
	return (pec_error);       
}
/*Writes the command RDCV and reads single Cell Voltage Register*/
void ltc_rdcv_reg(uint8_t reg, uint8_t total_ic, uint8_t *data){
	const uint8_t REG_LEN = 8;
	uint8_t cmd[4];
	uint16_t cmd_pec;
	if (reg == 1)     //1: RDCVA
	{
		cmd[1] = 0x04;
		cmd[0] = 0x00;
	}
	else if (reg == 2) //2: RDCVB
	{
		cmd[1] = 0x06;
		cmd[0] = 0x00;
	}
	else if (reg == 3) //3: RDCVC
	{
		cmd[1] = 0x08;
		cmd[0] = 0x00;
	}
	else if (reg == 4) //4: RDCVD
	{
		cmd[1] = 0x0A;
		cmd[0] = 0x00;
	}
	cmd_pec = ltc_pec(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);

	spi_csb_clear();
	spi_read_write(cmd,4,data,(REG_LEN*total_ic));
	spi_csb_set();
}
/*Writes the command RDAUX and reads a single GPIO Register*/
void ltc_rdaux_reg(uint8_t reg, uint8_t total_ic,  uint8_t *data){
	const uint8_t REG_LEN = 8;
	uint8_t cmd[4];
	uint16_t cmd_pec;
	if (reg == 1)     //Read back auxiliary group A
	{
		cmd[1] = 0x0C;
		cmd[0] = 0x00;
	}
	else if (reg == 2)  //Read back auxiliary group B
	{
		cmd[1] = 0x0E;
		cmd[0] = 0x00;
	}
	else          //Read back auxiliary group A
	{
		cmd[1] = 0x0C;
		cmd[0] = 0x00;
	}

	cmd_pec = ltc_pec(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);

	spi_csb_clear();
	spi_read_write(cmd,4,data,(REG_LEN*total_ic));
	spi_csb_set();
}
/*Writes the command RSTAT and reads a single STAT Register*/
void ltc_rdstat_reg(uint8_t reg, uint8_t total_ic,uint8_t *data){
	const uint8_t REG_LEN = 8;
	uint8_t cmd[4];
	uint16_t cmd_pec;

	if (reg == 1)     //Read back status group A
	{
		cmd[1] = 0x10;
		cmd[0] = 0x00;
	}
	else if (reg == 2)  //Read back status group B
	{
		cmd[1] = 0x12;
		cmd[0] = 0x00;
	}

	else          //Read back status group A
	{
		cmd[1] = 0x10;
		cmd[0] = 0x00;
	}
	cmd_pec = ltc_pec(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);

	spi_csb_clear();
	spi_read_write(cmd,4,data,(REG_LEN*total_ic));
	spi_csb_set();
}
/* Sends the poll ADC command */
uint8_t ltc_pladc()
{
	uint8_t cmd[4];
	uint8_t adc_state = 0xFF;
	uint16_t cmd_pec;
	
	cmd[0] = 0x07;
	cmd[1] = 0x14;
	cmd_pec = ltc_pec(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);
	
	spi_csb_clear();
	spi_write_array(cmd,4);
	adc_state = spi_read();
	spi_csb_set();
	
	return(adc_state);
}

/* Blocks operation until the ADC has finished it's conversion */
uint32_t ltc_pollAdc()
{
	uint32_t counter = 0;
	uint8_t finished = 0;
	uint8_t current_time = 0;
	uint8_t cmd[4];
	uint16_t cmd_pec;
	
	cmd[0] = 0x07;
	cmd[1] = 0x14;
	cmd_pec = ltc_pec(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);
	
	spi_csb_clear();
	spi_write_array(cmd,4);
	while ((counter<1000)&&(finished == 0))
	{
		current_time = spi_read();
		if (current_time>0)
		{
			finished = 1;
		}
		else
		{
			counter = counter + 10;
		}
	}
	spi_csb_set();
	
	return(counter);
}

/*
The command clears the cell voltage registers and initializes
all values to 1. The register will read back hexadecimal 0xFF
after the command is sent.
*/
void ltc_clrcell()
{
	uint8_t cmd[2]= {0x07 , 0x11};
	ltc_cmd(cmd);
}

/*
The command clears the Auxiliary registers and initializes
all values to 1. The register will read back hexadecimal 0xFF
after the command is sent.
*/
void ltc_clraux()
{
	uint8_t cmd[2]= {0x07 , 0x12};
	ltc_cmd(cmd);
}

/*
The command clears the Stat registers and initializes
all values to 1. The register will read back hexadecimal 0xFF
after the command is sent.

*/
void ltc_clrstat()
{
	uint8_t cmd[2]= {0x07 , 0x13};
	ltc_cmd(cmd);
}

/* Command DIAGN - Starts the Mux Decoder diagnostic self test */
void ltc_diagn()
{
	uint8_t cmd[2] = {0x07 , 0x15};
	ltc_cmd(cmd);
}
/* Command CSVT - Starts cell voltage self test conversion */
void ltc_cvst(uint8_t MD, //ADC Mode
				  uint8_t ST //Self Test
                 )
{
	uint8_t cmd[2];
	uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x02;
	md_bits = (MD & 0x01) << 7;
	cmd[1] =  md_bits + ((ST)<<5) +0x07;
	
	ltc_cmd(cmd);
}

/* Command AXST - Start an Auxiliary Register Self Test Conversion */
void ltc_axst(uint8_t MD, //ADC Mode
				  uint8_t ST //Self Test
				  )
{
	uint8_t cmd[2];
	uint8_t md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] =  md_bits + ((ST&0x03)<<5) +0x07;

	ltc_cmd(cmd);
}

/* Command STATST - Start a Status Register Self Test Conversion */
void ltc_statst(uint8_t MD, //ADC Mode
				    uint8_t ST //Self Test
					)
{
	uint8_t cmd[2];
	uint8_t md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] =  md_bits + ((ST&0x03)<<5) +0x0F;

	ltc_cmd(cmd);
}

/* Command ADOL - Starts cell voltage overlap conversion */
void ltc_adol(uint8_t MD, //ADC Mode
                  uint8_t DCP //Discharge Permit
				 )
{
	uint8_t cmd[2];
	uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x02;
	md_bits = (MD & 0x01) << 7;
	cmd[1] =  md_bits + (DCP<<4) +0x01;
	
	ltc_cmd(cmd);
}

/* Command ADAX - Start an GPIO Redundancy test */
void ltc_adaxd(uint8_t MD, //ADC Mode
				   uint8_t CHG //GPIO Channels to be measured
				   )
{
	uint8_t cmd[4];
	uint8_t md_bits;

	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + CHG ;

	ltc_cmd(cmd);
}

/* Command ADSTATD - Start a Status register redundancy test Conversion */
void ltc_adstatd(uint8_t MD, //ADC Mode
					 uint8_t CHST //Stat Channels to be measured
					 )
{
	uint8_t cmd[2];
	uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + 0x08 + CHST ;
	
	ltc_cmd(cmd);
}
/* Command ADOW - Start an open wire Conversion */
void ltc_adow(uint8_t MD, //ADC Mode
				  uint8_t PUP,//Pull up/Pull down current
				  uint8_t CH, //Channels
				  uint8_t DCP//Discharge Permit
				 )
{
	uint8_t cmd[2];
	uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x02;
	md_bits = (MD & 0x01) << 7;
	cmd[1] =  md_bits + 0x28 + (PUP<<6) + CH+(DCP<<4);
	
	ltc_cmd(cmd);
}
/* Command WRPWM - Writes the pwm register */
void ltc_wrpwm(uint8_t total_ic, // Number of ICs in the daisy chain
                   uint8_t pwmReg, // The PWM Register to be written A or B
                   cell_asic ic[] // A two dimensional array that stores the data to be written
                  )
{
	uint8_t cmd[2];
	uint8_t write_buffer[256];
	uint8_t write_count = 0;
	uint8_t c_ic = 0;
    uint8_t current_ic, data;
	if (pwmReg == 0)
	{
	cmd[0] = 0x00;
	cmd[1] = 0x20;
	}
	else
	{
	cmd[0] = 0x00;
	cmd[1] = 0x1C;
	}
	
	for (current_ic = 0; current_ic<total_ic; current_ic++)
	{
		c_ic = total_ic - current_ic - 1;   //First command sent to the last IC

		
		for (data = 0; data<6; data++)
		{
			write_buffer[write_count] = ic[c_ic].pwm.tx_data[data];
			write_count++;
		}
	}
	ltc_write(total_ic, cmd, write_buffer);
}


/* Command RDPWM - Reads pwm registers of a ltc daisy chain */
int8_t ltc_rdpwm(uint8_t total_ic, //Number of ICs in the system
                     uint8_t pwmReg, // The PWM Register to be written A or B
                     cell_asic ic[] // A two dimensional array that will store the data
                    )
{
	const uint8_t BYTES_IN_REG = 8;
	uint8_t cmd[4];
	uint8_t read_buffer[256];
	int8_t pec_error = 0;
	uint16_t data_pec;
	uint16_t calc_pec;
	uint8_t c_ic = 0;
    uint8_t current_ic;
    int byte;
	if (pwmReg == 0)
	{
		cmd[0] = 0x00;
		cmd[1] = 0x22;
	}
	else
	{
		cmd[0] = 0x00;
		cmd[1] = 0x1E;
	}
	
	pec_error = ltc_read(total_ic, cmd, read_buffer);
	for (current_ic =0; current_ic<total_ic; current_ic++)
	{
		c_ic = current_ic;   //First command received from the first IC
		for (byte=0; byte<8; byte++)
		{
			ic[c_ic].pwm.rx_data[byte] = read_buffer[byte+(8*current_ic)];
		}
		
		calc_pec = ltc_pec(6,&read_buffer[8*current_ic]);
		data_pec = read_buffer[7+(8*current_ic)] | (read_buffer[6+(8*current_ic)]<<8);
		if (calc_pec != data_pec )
		{
			ic[c_ic].pwm.rx_pec_match = 1;
		}
		else ic[c_ic].pwm.rx_pec_match = 0;
	}
	return(pec_error);
}

/* Command WRSCTRL - Write the ltc Sctrl register */
void ltc_wrsctrl(uint8_t total_ic, // Number of ICs in the daisy chain
                     uint8_t sctrl_reg, // The Sctrl Register to be written A or B
                     cell_asic *ic  // A two dimensional array that stores the data to be written
                    )
{
	uint8_t cmd[2];
    uint8_t write_buffer[256];
    uint8_t write_count = 0;
    uint8_t c_ic = 0;
    uint8_t current_ic, data;
    if (sctrl_reg == 0)
    {
      cmd[0] = 0x00;
      cmd[1] = 0x14;
    }
    else
    {
      cmd[0] = 0x00;
      cmd[1] = 0x1C;
    }
    
    for(current_ic = 0; current_ic<total_ic;current_ic++)
    {
        c_ic = total_ic - current_ic - 1;  //First command sent to the last IC
		
        for(data = 0; data<6;data++)
        {
            write_buffer[write_count] = ic[c_ic].sctrl.tx_data[data];
            write_count++;
        }
    }
    ltc_write(total_ic, cmd, write_buffer);
}					
					
/* Command RDSCTRL - Reads sctrl registers of a ltc daisy chain */    
int8_t ltc_rdsctrl(uint8_t total_ic, // Number of ICs in the daisy chain
                       uint8_t sctrl_reg, // The Sctrl Register to be written A or B
                       cell_asic *ic // A two dimensional array that the function stores the read data
                      )	
{
    uint8_t cmd[4];
    uint8_t read_buffer[256];
    int8_t pec_error = 0;
    uint16_t data_pec;
    uint16_t calc_pec;
    uint8_t c_ic = 0;
    uint8_t current_ic;
    int byte;
    if (sctrl_reg == 0)
    {
      cmd[0] = 0x00;
      cmd[1] = 0x16;
	  }
    else
    {
      cmd[0] = 0x00;
      cmd[1] = 0x1E;
	}
    
    pec_error = ltc_read(total_ic, cmd, read_buffer);

    for(current_ic =0; current_ic<total_ic; current_ic++)
    {	
        c_ic = current_ic;  //First command received from the first IC
        for(byte=0; byte<8;byte++)
        {
            ic[c_ic].sctrl.rx_data[byte] = read_buffer[byte+(8*current_ic)]; 	
        }
		
        calc_pec = ltc_pec(6,&read_buffer[8*current_ic]);
        data_pec = read_buffer[7+(8*current_ic)] | (read_buffer[6+(8*current_ic)]<<8);
        if(calc_pec != data_pec )
        {
            ic[c_ic].sctrl.rx_pec_match = 1;
        }
        else ic[c_ic].sctrl.rx_pec_match = 0;
		
    }
    return(pec_error);
}

/* 
Start Sctrl data communication       
This command will start the sctrl pulse communication over the spins
*/
void ltc_stsctrl()
{
	uint8_t cmd[4];
    uint16_t cmd_pec;
    
    cmd[0] = 0x00;
    cmd[1] = 0x19;
    cmd_pec = ltc_pec(2, cmd);
    cmd[2] = (uint8_t)(cmd_pec >> 8);
    cmd[3] = (uint8_t)(cmd_pec);
    
    spi_csb_clear();
    spi_write_array(cmd,4);          
    spi_csb_set();
}

/*
The command clears the Sctrl registers and initializes
all values to 0. The register will read back hexadecimal 0x00
after the command is sent.
*/
void ltc_clrsctrl()
{
	uint8_t cmd[2]= {0x00 , 0x18};
	ltc_cmd(cmd);
}
/* Command WRCOMM - Writes the comm register */
void ltc_wrcomm(uint8_t total_ic, //The number of ICs being written to
                    cell_asic ic[] // A two dimensional array that stores the data to be written
                   )
{
	uint8_t cmd[2]= {0x07 , 0x21};
	uint8_t write_buffer[256];
	uint8_t write_count = 0;
	uint8_t c_ic = 0;
    uint8_t current_ic;
    uint8_t data;
	for (current_ic = 0; current_ic<total_ic; current_ic++)
	{
		if (ic->isospi_reverse == true)
		{
			c_ic = current_ic;
		}
		else
		{
			c_ic = total_ic - current_ic - 1;
		}
	
		for (data = 0; data<6; data++)
		{
			write_buffer[write_count] = ic[c_ic].com.tx_data[data];
			write_count++;
		}
	}
	ltc_write(total_ic, cmd, write_buffer);
}
/* Command RDCOMM - Reads COMM registers of a ltc daisy chain */
int8_t ltc_rdcomm(uint8_t total_ic, //Number of ICs in the system
                      cell_asic ic[] //A two dimensional array that stores the read data
                     )
{
	uint8_t cmd[2]= {0x07 , 0x22};
	uint8_t read_buffer[256];
	int8_t pec_error = 0;
	uint16_t data_pec;
	uint16_t calc_pec;
	uint8_t c_ic=0;
	uint8_t current_ic;
    int byte;
	pec_error = ltc_read(total_ic, cmd, read_buffer);
	
	for (current_ic = 0; current_ic<total_ic; current_ic++)
	{
		c_ic = current_ic;	  //First command received from the first IC
		for (byte=0; byte<8; byte++)
		{
			ic[c_ic].com.rx_data[byte] = read_buffer[byte+(8*current_ic)];
		}
		
		calc_pec = ltc_pec(6,&read_buffer[8*current_ic]);
		data_pec = read_buffer[7+(8*current_ic)] | (read_buffer[6+(8*current_ic)]<<8);
		if (calc_pec != data_pec )
		{
			ic[c_ic].com.rx_pec_match = 1;
		}
		else ic[c_ic].com.rx_pec_match = 0;
	}
	
    return(pec_error);
}

/* Command STCOMM - Shifts data in COMM register out over ltc SPI/I2C port */
void ltc_stcomm(uint8_t len) //Length of data to be transmitted 
{
	uint8_t cmd[4];
	uint16_t cmd_pec;
    int i;
    
	cmd[0] = 0x07;
	cmd[1] = 0x23;
	cmd_pec = ltc_pec(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);

	spi_csb_clear();
	spi_write_array(cmd,4);
	for (i = 0; i<len*3; i++)
	{
	  spi_read();
	}
	spi_csb_set();
}


//High Level Functions

/* Runs the Digital Filter Self Test */
int16_t ltc_run_cell_adc_st(uint8_t adc_reg,uint8_t total_ic,
								cell_asic *ic,uint8_t md, bool adcopt)
{
	int16_t error = 0;
	uint16_t expected_result = 0;
    int self_test,cic, channel;
	for (self_test = 1; self_test<3; self_test++){
		expected_result = ltc_st_lookup(md,self_test,adcopt);
		ltc_wakeup_idle(total_ic);	
		switch (adc_reg){
		  case CELL:
			  ltc_wakeup_idle(total_ic);
			  ltc_clrcell();
			  ltc_cvst(md,self_test);
			  ltc_pollAdc();
				 
			  ltc_wakeup_idle(total_ic);
			  error = ltc_rdcv(0, total_ic,ic);      
			  for (cic = 0; cic < total_ic; cic++){
				  for (channel=0; channel< ic[cic].ic_reg.cell_channels; channel++){					 
					if (ic[cic].cells.c_codes[channel] != expected_result){
					  error = error+1;
					}
				  }
				}
			break;
		  case AUX:
			  error = 0;
			  ltc_wakeup_idle(total_ic);
			  ltc_clraux();
			  ltc_axst(md,self_test);
			  ltc_pollAdc();
			  
			  ltc_wakeup_idle(total_ic);
			  ltc_rdaux(0, total_ic,ic);     
			  for (cic = 0; cic < total_ic; cic++)
				{
				  for (channel=0; channel< ic[cic].ic_reg.aux_channels; channel++)
				  { 
					 
					if (ic[cic].aux.a_codes[channel] != expected_result)
					{
					  error = error+1;
					}
				  }
				}
			break;
		  case STAT:
			  ltc_wakeup_idle(total_ic);
			  ltc_clrstat();
			  ltc_statst(md,self_test);
			  ltc_pollAdc();
			  
			  ltc_wakeup_idle(total_ic);
			  error = ltc_rdstat(0,total_ic,ic);
			  for (cic = 0; cic < total_ic; cic++)
				{
				  for (channel=0; channel< ic[cic].ic_reg.stat_channels; channel++)
				  {
					if (ic[cic].stat.stat_codes[channel] != expected_result)
					{
					  error = error+1;
					}
				  }
				}
			break;

		  default:
			error = -1;
			break;
		}
	}
	
	return(error);
}
/* Runs the ADC overlap test for the IC */
uint16_t ltc_run_adc_overlap(uint8_t total_ic, cell_asic *ic)
{
	uint16_t error = 0;
	int32_t measure_delta =0;
	int16_t failure_pos_limit = 20;
	int16_t failure_neg_limit = -20;
	int32_t a, b;
	int cic;
    
	ltc_wakeup_idle(total_ic);
	ltc_adol(MD_7KHZ_3KHZ,DCP_DISABLED);
	ltc_pollAdc();
	ltc_wakeup_idle(total_ic);
	error = ltc_rdcv(0, total_ic,ic);
	  for (cic = 0; cic<total_ic; cic++)
	  {
		  measure_delta = (int32_t)ic[cic].cells.c_codes[6]-(int32_t)ic[cic].cells.c_codes[7];
		
		 if ((measure_delta>failure_pos_limit) || (measure_delta<failure_neg_limit))
		 {
		  error = error | (1<<(cic-1));
		 }
	  }
	  
    return(error);
}

/* Runs the redundancy self test */
int16_t ltc_run_adc_redundancy_st(uint8_t adc_mode, // ADC Mode
									  uint8_t adc_reg, // Type of register
									  uint8_t total_ic, // Number of ICs in the daisy chain
									  cell_asic *ic // A two dimensional array that will store the data
									  )
{
	int16_t error = 0;
    int self_test, cic, channel;
	for (self_test = 1; self_test<3; self_test++)
	{
		ltc_wakeup_idle(total_ic);
		switch (adc_reg)
		{
			case AUX:
			ltc_clraux();
			ltc_adaxd(adc_mode,AUX_CH_ALL);
			ltc_pollAdc();
		
			ltc_wakeup_idle(total_ic);
			error = ltc_rdaux(0, total_ic,ic);
			for (cic = 0; cic < total_ic; cic++)
			{
				for (channel=0; channel< ic[cic].ic_reg.aux_channels; channel++)
				{ 
					if (ic[cic].aux.a_codes[channel] >= 65280)
					{
						error = error+1;
					}
				}
			}
			break;
			case STAT:
			ltc_clrstat();
			ltc_adstatd(adc_mode,STAT_CH_ALL);
			ltc_pollAdc();
			ltc_wakeup_idle(total_ic);
			error = ltc_rdstat(0,total_ic,ic);
			for (cic = 0; cic < total_ic; cic++)
			{
				for (channel=0; channel< ic[cic].ic_reg.stat_channels; channel++)
				{
					if (ic[cic].stat.stat_codes[channel] >= 65280)
					{
						error = error+1;
					}
				}
			}
			break;
		
			default:
			error = -1;
			break;
		}
	}
	return(error);
}

/* Looks up the result pattern for digital filter self test */
uint16_t ltc_st_lookup(uint8_t MD, //ADC Mode
						   uint8_t ST, //Self Test
						   bool adcopt // ADCOPT bit in the configuration register
						  )
{
	uint16_t test_pattern = 0;

    if (MD == 1)
    { 
		if ( adcopt == false)
		{	
			if (ST == 1)
			{
				test_pattern = 0x9565;
			}
			else
			{
				test_pattern = 0x6A9A;
			}
		}
		else
		{	
			if (ST == 1)
			{
				test_pattern = 0x9553;
			}
			else
			{
				test_pattern = 0x6AAC;
			}	
		}
    }
    else
    {
		if (ST == 1)
		{
		   test_pattern = 0x9555;
		}
		else
		{
		   test_pattern = 0x6AAA;
		}
    }
    return(test_pattern);
}
/* Runs the data sheet algorithm for open wire for single cell detection */
void ltc_run_openwire_single(uint8_t total_ic, // Number of ICs in the daisy chain
								cell_asic ic[] // A two dimensional array that will store the data
								)
{				  
	uint16_t OPENWIRE_THRESHOLD = 4000;
	const uint8_t  N_CHANNELS = ic[0].ic_reg.cell_channels;
	
	uint16_t pullUp[total_ic][N_CHANNELS];
	uint16_t pullDwn[total_ic][N_CHANNELS];
	int16_t openWire_delta[total_ic][N_CHANNELS];
	
	int8_t error;
	int8_t i;
	uint32_t conv_time=0;
    int cic, cell;
	ltc_wakeup_sleep(total_ic);
	ltc_clrcell();
	// Pull Ups
	for (i = 0; i < 3; i++)
	{ 
	  ltc_wakeup_idle(total_ic);
	  ltc_adow(MD_26HZ_2KHZ,PULL_UP_CURRENT,CELL_CH_ALL,DCP_DISABLED);
	  conv_time = ltc_pollAdc();
	} 
	ltc_wakeup_idle(total_ic);
	error= ltc_rdcv(0, total_ic,ic);
	for (cic=0; cic<total_ic; cic++){
	    for (cell=0; cell<N_CHANNELS; cell++){
		  pullUp[cic][cell] = ic[cic].cells.c_codes[cell];
		}	
	}
	// Pull Downs
	for (i = 0; i < 3; i++){  
	  ltc_wakeup_idle(total_ic);
	  ltc_adow(MD_26HZ_2KHZ,PULL_DOWN_CURRENT,CELL_CH_ALL,DCP_DISABLED);
	  conv_time =ltc_pollAdc();
	}
	
	ltc_wakeup_idle(total_ic);
	error=ltc_rdcv(0, total_ic,ic); 
	
	for (cic=0; cic<total_ic; cic++){		  
	    for (cell=0; cell<N_CHANNELS; cell++){
		   pullDwn[cic][cell] = ic[cic].cells.c_codes[cell];
		}
	}
	for (cic=0; cic<total_ic; cic++){
	  ic[cic].system_open_wire = 0xFFFF;
	  
		for (cell=0; cell<N_CHANNELS; cell++){
			if (pullDwn[cic][cell] < pullUp[cic][cell]){
				openWire_delta[cic][cell] = (pullUp[cic][cell] - pullDwn[cic][cell]);
			}
			else{
				openWire_delta[cic][cell] = 0;                                             
			}  
				
			if (openWire_delta[cic][cell]>OPENWIRE_THRESHOLD)
			{
				ic[cic].system_open_wire = cell+1;
			}
		}
		
		if (pullUp[cic][0] == 0)
		{
		  ic[cic].system_open_wire = 0;
		}
		
		if (pullUp[cic][(N_CHANNELS-1)] == 0)//checking the Pull up value of the top measured channel
		{
		  ic[cic].system_open_wire = N_CHANNELS;
		}	
	}
}
/* Runs algorithm for open wire for multiple cell and two consecutive cells detection */
 void ltc_run_openwire_multi(uint8_t total_ic, // Number of ICs in the daisy chain
						  cell_asic ic[], // A two dimensional array that will store the data
						  uint8_t open[])
{              
	uint16_t OPENWIRE_THRESHOLD = 4000;
	const uint8_t  N_CHANNELS = ic[0].ic_reg.cell_channels;

	uint16_t pullUp[total_ic][N_CHANNELS];
	uint16_t pullDwn[total_ic][N_CHANNELS];
	uint16_t openWire_delta[total_ic][N_CHANNELS];

	int8_t error;
	int8_t opencells[N_CHANNELS];
	int8_t n=0;
	int8_t i,j,k;
	uint32_t conv_time=0;
    int cic, cell;
	ltc_wakeup_sleep(total_ic);
	ltc_clrcell();

	// Pull Ups
	for (i = 0; i < 5; i++){ 
		ltc_wakeup_idle(total_ic);
		ltc_adow(MD_7KHZ_3KHZ,PULL_UP_CURRENT,CELL_CH_ALL,DCP_DISABLED);
		conv_time = ltc_pollAdc();
	} 
	ltc_wakeup_idle(total_ic);
	error = ltc_rdcv(0, total_ic,ic);

	for (cic=0; cic<total_ic; cic++){
	    for (cell=0; cell<N_CHANNELS; cell++)
		{
		  pullUp[cic][cell] = ic[cic].cells.c_codes[cell];
		}
	}
	// Pull Downs
	for (i = 0; i < 5; i++){  
	  ltc_wakeup_idle(total_ic);
	  ltc_adow(MD_7KHZ_3KHZ,PULL_DOWN_CURRENT,CELL_CH_ALL,DCP_DISABLED);
	  conv_time =   ltc_pollAdc();
	}
	ltc_wakeup_idle(total_ic);
	error = ltc_rdcv(0, total_ic,ic); 
	for (cic=0; cic<total_ic; cic++)
	{
		for (cell=0; cell<N_CHANNELS; cell++)
		{
		   pullDwn[cic][cell] = ic[cic].cells.c_codes[cell];
		}
	}
	for (cic=0; cic<total_ic; cic++)
	{			  
		for (cell=0; cell<N_CHANNELS; cell++)
		{
			if (pullDwn[cic][cell] < pullUp[cic][cell])                   
				{
					openWire_delta[cic][cell] = (pullUp[cic][cell] - pullDwn[cic][cell]);
				}
				else
				{
					openWire_delta[cic][cell] = 0;                                             
				}
		}  
	}

	for (cic=0; cic<total_ic; cic++)
	{ 
		n=0;
						
		//Serial.print("IC:");
		//Serial.println(cic+1, DEC);
		
		for (cell=0; cell<N_CHANNELS; cell++)
		{  
		 
		  if (openWire_delta[cic][cell]>OPENWIRE_THRESHOLD)
			{
				opencells[n] = cell+1;
				n++;
				for (j = cell; j < N_CHANNELS-3 ; j++)                       
				{
					if (pullUp[cic][j + 2] == 0)
					{
					opencells[n] = j+2;
					n++;
					}
				}
				if((cell==N_CHANNELS-4) && (pullDwn[cic][N_CHANNELS-3] == 0))
				{
					  opencells[n] = N_CHANNELS-2;
					  n++;
				}
			}
		}
		if (pullDwn[cic][0] == 0)
		{
		  opencells[n] = 0;
		  //Serial.println("Cell 0 is Open and multiple open wires maybe possible.");
		  n++;
		}				
		if (pullDwn[cic][N_CHANNELS-1] == 0)
		{
		  opencells[n] = N_CHANNELS;
		  n++;
		}
					
		if (pullDwn[cic][N_CHANNELS-2] == 0)
		{  
		  opencells[n] = N_CHANNELS-1;
		  n++;
		}
		
	//Removing repetitive elements
		for(i=0;i<n;i++)
		{
			for(j=i+1;j<n;)
			{
				if(opencells[i]==opencells[j])
				{
					for(k=j;k<n;k++)
						opencells[k]=opencells[k+1];
						
					n--;
				}
				else
					j++;
			}
		}			
	// Sorting open cell array
		for(i=0; i<n; i++)
		{
			for(j=0; j<n-1; j++)
			{
				if( opencells[j] > opencells[j+1] )
				{
					k = opencells[j];
					opencells[j] = opencells[j+1];
					opencells[j+1] = k;
				}
			}
		}		

		if(n==0)
		{
		}
		else
		{				
			for(i=0;i<n;i++)
			{
                open[cic*12+(opencells[i]-1)] = 1;
			}
		}
	}
	//Serial.println("\n");
}
 /* Clears all of the DCC bits in the configuration registers */
void ltc_clear_discharge(uint8_t total_ic, // Number of ICs in the daisy chain
							 cell_asic *ic // A two dimensional array that will store the data
							 )
{
    int i;
	for (i=0; i<total_ic; i++)
	{
	   ic[i].config.tx_data[4] = 0;
	   ic[i].config.tx_data[5] =ic[i].config.tx_data[5]&(0xF0);
	}
}
/*Helper Function that parses Voltage Measuremetn Registers*/
int8_t ltc_parse_cells(uint8_t current_ic,uint8_t cell_reg,uint8_t cell_data[],uint16_t *cell_codes,uint8_t *ic_pec){
	const uint8_t BYT_IN_REG = 6;
	const uint8_t CELL_IN_REG = 3;
	int8_t pec_error = 0;
	uint16_t parsed_cell;
	uint16_t received_pec;
	uint16_t data_pec;
	uint8_t data_counter = current_ic*NUM_RX_BYT;
    uint8_t current_cell;
	for (current_cell = 0; current_cell<CELL_IN_REG; current_cell++){														
		parsed_cell = cell_data[data_counter] + (cell_data[data_counter + 1] << 8);
		cell_codes[current_cell  + ((cell_reg - 1) * CELL_IN_REG)] = parsed_cell;
		data_counter = data_counter + 2;
	}
	received_pec = (cell_data[data_counter] << 8) | cell_data[data_counter+1];
	data_pec = ltc_pec(BYT_IN_REG, &cell_data[(current_ic) * NUM_RX_BYT]);
	if (received_pec != data_pec){
		pec_error = 1;
		ic_pec[cell_reg-1]=1;
	}
	else
	{
		ic_pec[cell_reg-1]=0;
	}
	data_counter=data_counter+2;
	
	return(pec_error);
}
/* Helper function that increments PEC counters */
void ltc_check_pec(uint8_t total_ic, uint8_t reg,cell_asic *ic){
    int current_ic, i;
	switch (reg)
	{
		case CFGR:
		  for (current_ic = 0 ; current_ic < total_ic; current_ic++)
		  {
			ic[current_ic].crc_count.pec_count = ic[current_ic].crc_count.pec_count + ic[current_ic].config.rx_pec_match;
			ic[current_ic].crc_count.cfgr_pec = ic[current_ic].crc_count.cfgr_pec + ic[current_ic].config.rx_pec_match;
		  }
		break;
		case CELL:
		  for (current_ic = 0 ; current_ic < total_ic; current_ic++)
		  {
			for (i=0; i<ic[0].ic_reg.num_cv_reg; i++)
			{
			  ic[current_ic].crc_count.pec_count = ic[current_ic].crc_count.pec_count + ic[current_ic].cells.pec_match[i];
			  ic[current_ic].crc_count.cell_pec[i] = ic[current_ic].crc_count.cell_pec[i] + ic[current_ic].cells.pec_match[i];
			}
		  }
		break;
		case AUX:
		  for (current_ic = 0 ; current_ic < total_ic; current_ic++)
		  {
			for (i=0; i<ic[0].ic_reg.num_gpio_reg; i++)
			{
			  ic[current_ic].crc_count.pec_count = ic[current_ic].crc_count.pec_count + (ic[current_ic].aux.pec_match[i]);
			  ic[current_ic].crc_count.aux_pec[i] = ic[current_ic].crc_count.aux_pec[i] + (ic[current_ic].aux.pec_match[i]);
			}
		  }
		break;
		case STAT:
		  for (current_ic = 0 ; current_ic < total_ic; current_ic++)
		  {

			for (i=0; i<ic[0].ic_reg.num_stat_reg-1; i++)
			{
			  ic[current_ic].crc_count.pec_count = ic[current_ic].crc_count.pec_count + ic[current_ic].stat.pec_match[i];
			  ic[current_ic].crc_count.stat_pec[i] = ic[current_ic].crc_count.stat_pec[i] + ic[current_ic].stat.pec_match[i];
			}
		  }
		break;
		default:
		break;
	}
}
/* Helper Function to reset PEC counters */
void ltc_reset_crc_count(uint8_t total_ic, //Number of ICs in the system
							 cell_asic *ic //A two dimensional array that stores the data
							 )
{
    int current_ic, i;
	for (current_ic = 0 ; current_ic < total_ic; current_ic++)
	{
		ic[current_ic].crc_count.pec_count = 0;
		ic[current_ic].crc_count.cfgr_pec = 0;
		for (i=0; i<6; i++)
		{
			ic[current_ic].crc_count.cell_pec[i]=0;
		
		}
		for (i=0; i<4; i++)
		{
			ic[current_ic].crc_count.aux_pec[i]=0;
		}
		for (i=0; i<2; i++)
		{
			ic[current_ic].crc_count.stat_pec[i]=0;
		}
	}
}

/* Helper function to initialize CFG variables */
void ltc_init_cfg(uint8_t total_ic, //Number of ICs in the system
					  cell_asic *ic //A two dimensional array that stores the data
					  )
{
    uint8_t current_ic;
    int j;
	for (current_ic = 0; current_ic<total_ic;current_ic++)  
	{
		for (j =0; j<6; j++)
		{
		  ic[current_ic].config.tx_data[j] = 0;
		}
	}
}
/* Helper function to set CFGR variable */
void ltc_set_cfgr(uint8_t nIC, // Current IC
					 cell_asic *ic, // A two dimensional array that stores the data
					 bool refon, // The REFON bit
					 bool adcopt, // The ADCOPT bit
					 bool gpio[5], // The GPIO bits
					 bool dcc[12], // The DCC bits
					 bool dcto[4], // The Dcto bits
					 uint16_t uv, // The UV value
					 uint16_t  ov // The OV value
					 )
{
	ltc_set_cfgr_refon(nIC,ic,refon);
	ltc_set_cfgr_adcopt(nIC,ic,adcopt);
	ltc_set_cfgr_gpio(nIC,ic,gpio);
	ltc_set_cfgr_dis(nIC,ic,dcc);
	ltc_set_cfgr_dcto(nIC,ic,dcto);
	ltc_set_cfgr_uv(nIC, ic, uv);
	ltc_set_cfgr_ov(nIC, ic, ov);
}

/* Helper function to set the REFON bit */
void ltc_set_cfgr_refon(uint8_t nIC, cell_asic *ic, bool refon)
{
	if (refon) ic[nIC].config.tx_data[0] = ic[nIC].config.tx_data[0]|0x04;
	else ic[nIC].config.tx_data[0] = ic[nIC].config.tx_data[0]&0xFB;
}

/* Helper function to set the ADCOPT bit */
void ltc_set_cfgr_adcopt(uint8_t nIC, cell_asic *ic, bool adcopt)
{
	if (adcopt) ic[nIC].config.tx_data[0] = ic[nIC].config.tx_data[0]|0x01;
	else ic[nIC].config.tx_data[0] = ic[nIC].config.tx_data[0]&0xFE;
}

/* Helper function to set GPIO bits */
void ltc_set_cfgr_gpio(uint8_t nIC, cell_asic *ic,bool gpio[5])
{
    int i;
	for (i =0; i<5; i++)
	{
		if (gpio[i])ic[nIC].config.tx_data[0] = ic[nIC].config.tx_data[0]|(0x01<<(i+3));
		else ic[nIC].config.tx_data[0] = ic[nIC].config.tx_data[0]&(~(0x01<<(i+3)));
	}
}

/* Helper function to control discharge */
void ltc_set_cfgr_dis(uint8_t nIC, cell_asic *ic,bool dcc[12])
{
    int i;
	for (i =0; i<8; i++)
	{
		if (dcc[i])ic[nIC].config.tx_data[4] = ic[nIC].config.tx_data[4]|(0x01<<i);
		else ic[nIC].config.tx_data[4] = ic[nIC].config.tx_data[4]& (~(0x01<<i));
	}
	for (i =0; i<4; i++)
	{
		if (dcc[i+8])ic[nIC].config.tx_data[5] = ic[nIC].config.tx_data[5]|(0x01<<i);
		else ic[nIC].config.tx_data[5] = ic[nIC].config.tx_data[5]&(~(0x01<<i));
	}
}

/* Helper function to control discharge time value */
void ltc_set_cfgr_dcto(uint8_t nIC, cell_asic *ic,bool dcto[4])
{
    int i;
	for(i =0;i<4;i++)
	{
		if(dcto[i])ic[nIC].config.tx_data[5] = ic[nIC].config.tx_data[5]|(0x01<<(i+4));
		else ic[nIC].config.tx_data[5] = ic[nIC].config.tx_data[5]&(~(0x01<<(i+4)));
	} 
}

/* Helper Function to set UV value in CFG register */
void ltc_set_cfgr_uv(uint8_t nIC, cell_asic *ic,uint16_t uv)
{
	uint16_t tmp = (uv/16)-1;
	ic[nIC].config.tx_data[1] = 0x00FF & tmp;
	ic[nIC].config.tx_data[2] = ic[nIC].config.tx_data[2]&0xF0;
	ic[nIC].config.tx_data[2] = ic[nIC].config.tx_data[2]|((0x0F00 & tmp)>>8);
}

/* Helper function to set OV value in CFG register */
void ltc_set_cfgr_ov(uint8_t nIC, cell_asic *ic,uint16_t ov)
{
	uint16_t tmp = (ov/16);
	ic[nIC].config.tx_data[3] = 0x00FF & (tmp>>4);
	ic[nIC].config.tx_data[2] = ic[nIC].config.tx_data[2]&0x0F;
	ic[nIC].config.tx_data[2] = ic[nIC].config.tx_data[2]|((0x000F & tmp)<<4);
}

/*Initialize the Register limits*/
void ltc_init_reg_limits(uint8_t total_ic,cell_asic *ic)
{
    uint8_t cic;
  for (cic=0; cic<total_ic; cic++)
  {
    ic[cic].ic_reg.cell_channels=12;
    ic[cic].ic_reg.stat_channels=4;
    ic[cic].ic_reg.aux_channels=6;
    ic[cic].ic_reg.num_cv_reg=4;
    ic[cic].ic_reg.num_gpio_reg=2;
    ic[cic].ic_reg.num_stat_reg=3;
  }
}
/*Helper function to set discharge bit in CFG register*/
void ltc_set_discharge(int Cell, int select_ic,cell_asic *ic){
  int i;
  i = select_ic;
    if ((Cell<9)&& (Cell!=0) )
    {
      ic[i].config.tx_data[4] = ic[i].config.tx_data[4] | (1<<(Cell-1));
    }
    else if (Cell < 13)
    {
      ic[i].config.tx_data[5] = ic[i].config.tx_data[5] | (1<<(Cell-9));
    }
	else
	{
	}
}
