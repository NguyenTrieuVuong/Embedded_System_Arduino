#include <avr/interrupt.h>

#define pin 2


volatile unsigned long counter = 0;
volatile char check = 0;

void TimeSleep1() {
  noInterrupts();  // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  //delay 1s
  TCNT1 = 3036;
  //TCNT1 = 59286;            // preload timer
  TCCR1B |= (1 << CS12);   // 256 prescaler
  TIMSK1 |= (1 << TOIE1);  // enable timer overflow interrupt
  interrupts();            // enable all interrupts
}


void setup() {

  pinMode(pin, INPUT);
  Serial.begin(9600);

  TimeSleep1();
  attachInterrupt(0, In, FALLING);
}

void loop() {



}


ISR(TIMER1_OVF_vect) {
  TCNT1 = 3036;
  //TCNT1 = 59286;
  //TCNT1 = 40536;
  Serial.println(counter);
  counter = 0;
}

void In() {
  counter += 1;
}
