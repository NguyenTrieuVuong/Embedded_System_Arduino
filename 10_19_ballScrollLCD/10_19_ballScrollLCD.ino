#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

// make some custom characters:

byte ball[8] = {
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
  B00000
};


void setup() 
{
    Serial.begin(9600);
    lcd.begin(16, 2);
 #if 1   
    // create a new character
    lcd.createChar(0, ball);
#endif 
    // set up the lcd's number of columns and rows:
}

void loop() 
{
    // read the potentiometer on A0:
    int sensorReading = analogRead(A0);
    lcd.setCursor(0, 0);
    // Print a message to the lcd.
    lcd.print(sensorReading);
    // map the result to 200 - 1000:
    int delayTime = map(sensorReading, 0, 1023, 200, 1000);
    // set the cursor to the bottom row, 5th position:
    lcd.setCursor(0, 1);
    for (int thisChar = 0; thisChar < 10; thisChar++)
    {
        lcd.write((unsigned char)0);
        delay(500);
        lcd.clear();
    }
    // set the cursor to (16,1):
    lcd.setCursor(16,1);
    // set the display to automatically scroll:
    lcd.autoscroll();
    for (int thisChar = 0; thisChar < 10; thisChar++)
    {
        lcd.write((unsigned char)0);
        delay(500);
        lcd.clear();
    }
    // turn off automatic scrolling
    lcd.noAutoscroll();
}