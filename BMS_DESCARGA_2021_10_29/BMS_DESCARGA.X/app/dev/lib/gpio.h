/* 
 * GPIO Header
 * Library Layer
 */

#ifndef GPIO_H
#define	GPIO_H

void gpio_leds_init();
void gpio_ctrl_init();
void gpio_sgnl_init();
void gpio_interrupt_cn_set();
void gpio_interrupt_cn_clear();
void gpio_interrupt_cn_disable();
void gpio_led4_set(int c);
void gpio_led5_set(int c);
void gpio_leda_set(int c);
void gpio_ledb_set(int c);
void gpio_fan1_set(int c);
void gpio_fan2_set(int c);
void gpio_fan3_set(int c);
void gpio_prec_set(int c);
void gpio_airn_set(int c);
void gpio_airp_set(int c);
void gpio_led4_toggle();
void gpio_led5_toggle();
void gpio_leda_toggle();
void gpio_ledb_toggle();
int  gpio_signal_bal_read();
int  gpio_signal_shtdwn_read();
int  gpio_signal_disch_read();
int  gpio_signal_ch_read();
#endif	/* GPIO_H */

