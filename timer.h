#ifndef TIMER_H
#define TIMER_H

#define tccr1a (*(volatile uint8_t *)0x80)
#define tccr1b (*(volatile uint8_t *)0x81)
#define tcnt1  (*(volatile uint16_t *)0x84) // always declare them as uint_16bit
#define ocr1a  (*(volatile uint16_t *)0x88) // if declare 8bit or char , then only 255
#define timsk1 (*(volatile uint8_t *)0x6F) //..will go to them rest will be overflowed

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void timer_init();
void delay_us(uint16_t time);
void timer1_start_freerunning();
uint16_t timer1_read();
void timer1_stop();

#ifdef __cplusplus
}
#endif

#endif
