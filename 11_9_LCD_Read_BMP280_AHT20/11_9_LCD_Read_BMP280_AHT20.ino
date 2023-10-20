#include "DHT.h"
#include <Wire.h>
#include "rgb_lcd.h"
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "DFRobot_AHT20.h"

DFRobot_AHT20 aht20;
rgb_lcd lcd;
Adafruit_BMP280 bmp; 

// make some custom characters:
byte percent[8] = {
    B11000,
    B11001,
    B00010,
    B00100,
    B01000,
    B10011,
    B00011,
    B00000
};

byte temperature[8]{
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
  aht20.begin();
  lcd.begin(16, 2);
  bmp.begin();
 #if 1  
  lcd.createChar(1, percent);
  lcd.createChar(2,temperature);
#endif 
}


void loop() {
  aht20.startMeasurementReady();
  // put your main code here, to run repeatedly:
  float h = aht20.getTemperature_C();
  // Read temperature as Celsius (the default)
  float t = aht20.getHumidity_RH();

  lcd.setCursor(0, 0);
  lcd.print("TEMP: ");
  lcd.setCursor(6, 0);
  lcd.print(aht20.getTemperature_C());
  lcd.setCursor(11, 0);
  lcd.write(2);
  lcd.setCursor(12, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("HUMID: ");
  lcd.setCursor(7, 1);
  lcd.print(t);
  lcd.setCursor(12, 1);
  lcd.write(1);
  delay(1000);
  lcd.clear();
  float bar = bmp.readPressure();
    lcd.setCursor(0,0);
    lcd.print("P= ");
    lcd.print(bar);
    lcd.print(" Pa");
    lcd.setCursor(0,1);
    lcd.print("H= ");
    lcd.print(bmp.readAltitude(1013.25));
    lcd.print(" m");
    delay(1000);
    lcd.clear();
}
//BMP280: Doc ap suat P; AHT20: Doc nhiet do Temp va do am Humid