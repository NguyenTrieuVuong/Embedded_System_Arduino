#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
byte empty[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.createChar(1, empty);
}

void loop() {
  // put your main code here, to run repeatedly:
  String text = "Trieu Vuong";
  for(int i = -16;i<0;i++)
    {
      lcd.setCursor(i,0);
      lcd.print(text);
      
    //lcd.setCursor(i-1, 0);
    //lcd.write(1);
      delay(500);
    }
    for(int i = 1;i<=16;i++)
    {
      lcd.setCursor(i,0);
      lcd.print(text);
      
    lcd.setCursor(i-1, 0);
    lcd.write(1);
      delay(500);
    }
}
