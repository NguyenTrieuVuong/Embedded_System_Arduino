#include <Wire.h>
#include "DHT.h"
#include "rgb_lcd.h"
rgb_lcd lcd;
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
byte doC[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};
void setup() {
  // put your setup code here, to run once:
  dht.begin();
  lcd.begin(16, 2);
  lcd.createChar(0, doC);
  delay(1000);
}

void loop() {
  delay(500);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Humid: ");
  lcd.print(h);
  //lcd.write((unsigned char)0);
  lcd.print(F("%H"));
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t*1.0);
  lcd.write((unsigned char)0);
  lcd.print(F("C"));
}
