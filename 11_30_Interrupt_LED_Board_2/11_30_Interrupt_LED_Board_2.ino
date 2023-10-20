#include <avr/interrupt.h>
#define pin 5
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
volatile int counter;
void setup()
{
  pinMode(pin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);

  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  TCNT1 = 34286;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();
}

void loop()
{
  digitalWrite(ledPin, state);
}

void blink() {
  state = !state;
}

ISR (TIMER1_OVF_vect)
{
  TCNT1 = 34286;
  digitalWrite(pin, digitalRead(pin) ^ 1);
}