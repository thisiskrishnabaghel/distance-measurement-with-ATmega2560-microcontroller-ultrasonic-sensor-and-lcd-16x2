#include "lcd.h"
#include "timer.h"
#include "hcsr04.h"

void setup() {
  // put your setup code here, to run once:
  timer_init();
  lcd_init();
  hcsr04_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t pulse_width = get_echo_pulse_width_us();
  uint16_t distance_cm = pulse_width / 58.8;
  lcd_set_cursor(0, 0);
  lcd_print_distance(distance_cm);
  write_string(" cm      ");
}
