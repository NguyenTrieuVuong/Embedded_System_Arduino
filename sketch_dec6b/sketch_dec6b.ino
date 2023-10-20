#include <TimerOne.h>
//const int outPin = 2;
const int inPin = 2;
volatile byte state = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(inPin, OUTPUT);
  Serial.begin(9600);
  Serial.println();
  Timer1.initialize(1000000);
  Timer1.pwm(inPin, 512);
  attachInterrupt(digitalPinToInterrupt(inPin), countFallingPulse, CHANGE);
}

void countFallingPulse(){
  state=!state;
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(state);
  Serial.print(", ");
  Serial.println();
  delay(1000);
  int pulseHigh = pulseIn(inPin, HIGH);
  int pulseLow = pulseIn(inPin, LOW);
  int period = pulseHigh+pulseLow;
  int freq = 1000000/period;
  int duty = pulseHigh*1000/period;
    Serial.print("Freq = ");
  Serial.println(freq);
Serial.print("Duty cycle = ");
  Serial.println(duty);
  delay(500);
}
