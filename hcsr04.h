#ifndef HCSR04_H
#define HCSR04_H

#include <stdint.h>

#define ddra (*(volatile uint8_t *)0x21)
#define outa (*(volatile uint8_t *)0x22)
#define ddrc (*(volatile uint8_t *)0x27)
#define inc (*(volatile uint8_t *)0x26)

#ifdef __cplusplus
extern "C" {
#endif

void hcsr04_init();
uint16_t get_echo_pulse_width_us();

#ifdef __cplusplus
}
#endif

#endif
