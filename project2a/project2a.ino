#include <Adafruit_PCD8544.h>
#include "DHT.h"
Adafruit_PCD8544 display = Adafruit_PCD8544(2, 3, 4, 5, 6);
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  Serial.begin(9600);
  display.begin();
  display.setContrast(60);
  //display.display();
  display.clearDisplay();
}

void loop() {  
  // Check if any reads failed and exit early (to try again).
  // if (isnan(h) || isnan(t) || isnan(f)) {
  //   Serial.println(F("Failed to read from DHT sensor!"));
  //   return;
  // }
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
    display.setCursor(1, 1);
    display.print("Failed to read from DHT sensor!");
    display.display();
    display.clearDisplay();
    return;
  }
  if (!isnan(h) && !isnan(t) && !isnan(f) ){
    display.clearDisplay();
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
    display.setCursor(0,9);
    display.print("Temp: ");
    display.print(t);
    display.print(" C");
    display.setCursor(0,30);
    display.print("Humid: ");
    display.print(h);
    display.print("%");
    display.display();
    display.clearDisplay();
  }
}
