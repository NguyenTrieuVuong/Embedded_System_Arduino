#include <avr/interrupt.h>     
    #define ledPin 13
    #define sig 5
    
    volatile int counter;
    
    void TimeSleep1(){
      noInterrupts();           // disable all interrupts
      TCCR1A = 0;
      TCCR1B = 0;
      TIMSK1 = 0;    
      //delay 1s
      TCNT1 = 3036;   // preload timer           
      TCCR1B |= (1 << CS12);    // 256 prescaler     
      TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt    
      interrupts();             // enable all interrupts                              
    }
 void setup()
    {
    pinMode(ledPin, OUTPUT); 
    pinMode(sig, OUTPUT);        
    digitalWrite(2, LOW); 
    
    TimeSleep1();
    attachInterrupt(0, daoled, CHANGE);  
    }
     
    void loop()
    {
      
      //attachInterrupt(0, daoled, CHANGE); 
       
    }
     
     
    ISR (TIMER1_OVF_vect) 
    {
        TCNT1 = 3036;        
        digitalWrite(sig,!digitalRead(sig));           
    }

    void daoled()                      
    { 
         digitalWrite(ledPin,digitalRead(ledPin)^1); 
    }