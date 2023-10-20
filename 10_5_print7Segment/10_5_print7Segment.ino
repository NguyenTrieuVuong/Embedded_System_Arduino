#include "TM1637.h"
#define CLK 2//pins definitions for TM1637 and can be changed to other ports
#define DIO 3
TM1637 tm(CLK, DIO);
void setup() {
  // put your setup code here, to run once:
  tm.init();
  tm.set(BRIGHT_TYPICAL);
}

void loop() {
  // put your main code here, to run repeatedly:
  tm.display(0,9);
  tm.display(1,9);
  tm.display(3,9);
}
