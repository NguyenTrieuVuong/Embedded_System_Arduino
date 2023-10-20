/*
Sau một khoảng thời gian là 1s thì led ở chân 13 đổi trạng thái
*/

    #include <avr/interrupt.h>     
    #define ledPin 13
    volatile int counter;
    
     
    void setup()
    {
    pinMode(ledPin, OUTPUT);        
    noInterrupts();           // disable all interrupts
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;    
    //delay 1s
    TCNT1 = 40536;   // preload timer           
    TCCR1B |= (1 << CS11)|(1<<CS10);    // 256 prescaler     
    TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt    
    interrupts();             // enable all interrupts                                  // cho phép ngắt toàn cục
    }
     
    void loop()
    {
    }
     
     
    ISR (TIMER1_OVF_vect) 
    {
        TCNT1 = 40536;           
        digitalWrite(ledPin, digitalRead(ledPin) ^ 1);           
    }