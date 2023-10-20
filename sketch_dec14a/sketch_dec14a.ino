#include <avr/interrupt.h>
#define pin 13

volatile int counter;
volatile byte state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(pin, OUTPUT);        
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0; 
     
  //delay 1s
  TCNT1 = 3036;   // preload timer           
  TCCR1B |= (1 << CS12);    // 256 prescaler     
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt    
  interrupts();             // enable all interrupts*/

  //delay 0.5s
  /*TCNT1 = 34286; //preload timer
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt    
  interrupts();             // enable all interrupts*/

  // delay 0.2s
  /*TCNT1 = 15536; // Preload timer
  TCCR1B |= (1 << CS11);
  TCCR1B |= (1 << CS10);  
  TIMSK1 |= (1 << TOIE1);
  interrupts();*/

  // delay 0.1s
  /*TCNT1 = 40536; //
  TCCR1B |= (1 << CS11);
  TCCR1B |= (1 << CS10);  
  TIMSK1 |= (1 << TOIE1);
  interrupts();*/

  // delay 0.05s
//  TCNT1 = 50000;
//  TCCR1B |= (1 << CS11);
//  TCCR1B |= (1 << CS10);  
//  TIMSK1 |= (1 << TOIE1);
  interrupts();
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(pin, state);
}

/*void blink() {
  state = !state;
}*/


ISR (TIMER1_OVF_vect) 
{
  TCNT1 = 3036; // Nho thay doi khi thay doi code        
  digitalWrite(pin, digitalRead(pin) ^ 1);           
}
