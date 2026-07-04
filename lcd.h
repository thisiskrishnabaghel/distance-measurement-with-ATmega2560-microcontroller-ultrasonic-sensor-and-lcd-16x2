#ifndef LCD_H
#define LCD_H
#include <stdint.h>

#define EN 0
#define RS 1
#define ddrf (*(volatile uint8_t *)0x30)
#define outf (*(volatile uint8_t *)0x31)
#define ddrk (*(volatile uint8_t *)0x107)
#define outk (*(volatile uint8_t *)0x108)


#ifdef __cplusplus
extern "C" {
#endif

void lcd_init();
void lcd_out(uint8_t data);
void send_cmd_pulse();
void write_string(uint8_t *ptr);
void write_data(uint8_t data);
void send_data_pulse();
void delay1(int count);
void lcd_print_distance(uint16_t n);
void lcd_set_cursor(uint8_t row, uint8_t column);


#ifdef __cplusplus
}
#endif

#endif
