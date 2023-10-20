#include <Nokia_LCD.h>
#include "DHT.h"
#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
Nokia_LCD lcd(2 /* CLK */, 3 /* DIN */, 4 /* DC */, 5 /* CE */, 6 /* RST */ /* BL */);
  
void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin();
  // Turn on the backlight
  // lcd.setBacklight(true);
  lcd.setContrast(60);
  // lcd.clear();
  lcd.clear();
  lcd.setBacklight(false);
  // Set the contrast
  //lcd.setContrast(60);  // Good values are usualy between 40 and 60
  // Clear the screen by filling it with black pixels
  //lcd.setCursor(5, 2);
  //lcd.setInverted(false);
  //lcd.print("h");
  
}

void loop() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    lcd.setCursor(1, 1);
    lcd.print("Failed to read from DHT sensor!");
    lcd.clear();
    return;
  }
  if (!isnan(h) && !isnan(t) && !isnan(f) ){
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.setInverted(false);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.setCursor(1, 3);
    lcd.print("Humid: ");
    lcd.print(h);
    //lcd.clear();
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(f);
    Serial.print(F("°F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("°C "));
    Serial.print(hif);
    Serial.println(F("°F"));
  }
}
