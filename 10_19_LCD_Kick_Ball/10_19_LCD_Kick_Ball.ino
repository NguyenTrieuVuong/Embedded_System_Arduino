#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

byte human[8] = {
  B00000,
  B00100,
  B00100,
  B01110,
  B00100,
  B01010,
  B01010,
  B00000
};

byte humanKickRight[8] = {
  B00000,
  B00100,
  B00100,
  B01110,
  B00100,
  B01011,
  B01000,
  B00000
};

byte humanKickLeft[8] = {
  B00000,
  B00100,
  B00100,
  B01110,
  B00100,
  B11010,
  B00010,
  B00000
};

byte ball[8] = {
  B00000,
  B00000,
  B00000,
  B01110,
  B10101,
  B11111,
  B10101,
  B01110
};

byte blank[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

// make some custom characters:
void setup() {

  lcd.begin(16, 2);
#if 1
  // create a new character
  lcd.createChar(0, human);
  // create a new character
  lcd.createChar(1, humanKickRight);
  // create a new character
  lcd.createChar(2, humanKickLeft);
  lcd.createChar(3, ball);
  lcd.createChar(4, blank);
#endif
  // set up the lcd's number of columns and rows:
  lcd.setCursor(0, 0);
  lcd.write((unsigned char)0);
  lcd.setCursor(15, 0);
  lcd.write((unsigned char)0);
  lcd.setCursor(1, 0);
  lcd.write(3);
  lcd.setCursor(0, 1);
  lcd.print("RONALDO");
  lcd.setCursor(11, 1);
  lcd.print("MESSI");
}

void loop() {
  // read the potentiometer on A0:
  int sensorReading = analogRead(A0);
  // map the result to 200 - 1000:
  int delayTime = map(sensorReading, 0, 511, 0, 1000);
  delay(delayTime);
  lcd.setCursor(0, 0);
  lcd.write(1);
  delay(delayTime);
  lcd.setCursor(0, 0);
  lcd.write((unsigned char)0);
  //lcd.write((unsigned char) 0);
  for (int i = 1; i < 15; i++) {
    lcd.setCursor(i, 0);
    lcd.write(3);
    // lcd.setCursor(0, 0);
    // lcd.write((unsigned char)0);
    if (i > 1) {
      lcd.setCursor(i - 1, 0);
      lcd.write(4);
      delay(delayTime);
    }
    if (i == 14) {
      lcd.setCursor(15, 0);
      lcd.write(2);
      delay(delayTime);
      lcd.setCursor(15, 0);
      lcd.write((unsigned char)0);
      for (int j = 14; j >= 1; j--) {
        lcd.setCursor(j, 0);
        lcd.write(3);
        if (j < 14) {
          lcd.setCursor(j + 1, 0);
          lcd.write(4);
          delay(delayTime);
        }
      }
    }
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
