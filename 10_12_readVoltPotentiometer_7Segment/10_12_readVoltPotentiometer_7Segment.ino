/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/
#include "TM1637.h"
#define CLK 2
#define DIO 3
TM1637 tm1637 (CLK,DIO);
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  float y = sensorValue*5.0/1023;
  // print out the value you read:
  Serial.println(y);
  delay(50);        // delay in between reads for stability
  int arr[4];
  int volt1=y;
  int volt=y*1000;
  int chiaphandu=volt%100;
  int volt2 = chiaphandu/10;
  int volt3=chiaphandu%10;
  int i;
  // tm1637.display(1,volt1);
  // tm1637.display(2,volt2);
  // tm1637.display(3,volt3);
  for(i=3;i>=0;i--){
    arr[i]=volt%10;
    volt/=10;
  }
  for(i=0;i<=3;i++){
    tm1637.display(i,arr[i]);
  }
}
