#include "timer.h"
#include "hcsr04.h"

void hcsr04_init() {
  ddra = 0xFF;
  inc = 0x00;
}
uint16_t get_echo_pulse_width_us() {
  uint16_t t_start, t_end;

  // send 10us trigger pulse (using your existing delay_us)
  outa = 0x01;
  delay_us(10);
  outa = 0x00;
  while (!(inc & 0x01));

  timer1_start_freerunning();
  t_start = timer1_read();

  while ((inc & 0x01));
  t_end = timer1_read();

  timer1_stop();

  uint16_t ticks = t_end - t_start;    // subtraction is safe even across overflow
  return ticks * 4;                    // convert ticks to microseconds
}
