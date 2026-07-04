#include "timer.h"
#include <avr/interrupt.h>

volatile uint8_t timer_done;

void timer_init() {
  tccr1a = 0;
  tccr1b = 0;
  timer_done = 0;

}
void delay_us(uint16_t time) {
  tccr1a = 0;
  tccr1b = 0;

  tcnt1 = 0;
  timer_done = 0;

  ocr1a = (2 * time) - 1;   // prescaler 8

  timsk1 |= (1 << 1);       // enable interrupt
  tccr1b = 0x0A;            // CTC + prescaler 8

  while (timer_done == 0);

  tccr1b = 0x00;            // stop timer
  timsk1 &= ~(1 << 1);      // disable interrupt
}

void timer1_start_freerunning() {
  tccr1a = 0;
  tccr1b = 0;
  tcnt1  = 0;
  tccr1b = 0x03;   // normal mode, prescaler 64 -> 4us per tick @16MHz
}

uint16_t timer1_read() {
  return tcnt1;
}

void timer1_stop() {
  tccr1b = 0x00;
}


ISR(TIMER1_COMPA_vect) {
  timer_done = 1;
}
