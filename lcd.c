#include "lcd.h"

void lcd_init() {
  ddrf = 0xFF;
  ddrk = 0xFF;
  lcd_out(0x30);  // 8-bit mode
  send_cmd_pulse();
  lcd_out(0x38); // 8-bit, 2 Line, 5x8 Font
  send_cmd_pulse();
  lcd_out(0x01); // clear display
  send_cmd_pulse();
  lcd_out(0x0C); //display on, cursor on, blinking on
  send_cmd_pulse();
  lcd_out(0x06); // increment on , no shift
  send_cmd_pulse();
}

void lcd_out(uint8_t data) {
  outf = data;
}
void send_cmd_pulse() {
  outk = (0 << RS) | (0 << EN);
  delay1(1);
  outk = (0 << RS) | (1 << EN);
  delay1(1);
  outk = (0 << RS) | (0 << EN);
  delay1(1);
}

void write_string(uint8_t *ptr) {
  while (*ptr != '\0') {
    write_data(*ptr++);
  }
}

void write_data(uint8_t data) {
  lcd_out(data);
  send_data_pulse();
}

void send_data_pulse() {
  outk = (1 << RS) | (0 << EN);
  delay1(1);
  outk = (1 << RS) | (1 << EN);
  delay1(1);
  outk = (1 << RS) | (0 << EN);
  delay1(1);
}

void lcd_print_distance(uint16_t n) {
  int i = 0;
  char temp[20] = "";
  if (n < 0) {
    strcat(temp, "-");
    n = -1 * n;
  }
  int numPart = (int) n;
  // converting numPart into string
  if (numPart == 0) {
    strcat(temp, "0");
  } else {
    int x = numPart;
    while (x != 0) {
      i++;
      x /= 10;
    }

    while (i != 0) {
      char abc[2];
      int divisor = 1;
      for (int k = 0; k < i - 1; k++) {
        divisor *= 10;
      }
      int t = numPart / divisor ;
      abc[0] = t + '0';
      abc[1] = '\0';
      strcat(temp, abc);
      numPart = numPart % divisor;
      i--;
    }
  }
  write_string(temp);
}

void lcd_set_cursor(uint8_t row, uint8_t column) {
  uint8_t address ;
  switch (row) {
    case 0: address = 0x00 + column; break;
    case 1: address = 0x40 + column; break;
  }
  lcd_out(0x80 | address);
  send_cmd_pulse();
}

void delay1(int count)
{
  volatile long i;
  while (count)
  {
    for (i = 0; i < 1000; i++);
    count--;
  }
}
