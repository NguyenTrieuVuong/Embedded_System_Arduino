#include <avr/sleep.h>
#include <avr/wdt.h>

#include <OneWire.h>
const byte DS18B20_PIN=2;  //sensor data pin
OneWire ds(DS18B20_PIN);
byte addr[8];
float DS18B20float;

void setup() {

Serial.begin(9600);

//Set up Temp sensor – there is only one 1 wire sensor connected
if ( !ds.search(addr)) {
Serial.println(F("—> ERROR: Did not find the DS18B20  Temperature Sensor!"));
return;
}
else {
Serial.print(F("DS18B20 ROM address ="));
for(byte i = 0; i < 8; i++) {
Serial.write(' ');
Serial.print(addr[i], HEX);
}
Serial.println();
}
delay (200);
}

void loop() {

DS18B20float = getTemp();
Serial.print(F("FLOAT temp in celcius: "));
Serial.println(DS18B20float);
//Note: sensor defaults to a reading of 85 if you read it too soon after a reset!
delay (200);  //just a delay to boot out the coms
}

// watchdog interrupt
ISR (WDT_vect)
{
wdt_disable(); // disable watchdog
} // end of WDT_vect

// this returns the temperature from one DS18S20 in DEG Celsius using 12 bit conversion
float getTemp(){
byte data[2];
ds.reset();
ds.select(addr);
ds.write(0x44); // start conversion, read temperature and store it in the scratchpad

//this next bit creates a 1 second WDT delay during the DS18b20 temp conversion
//The time needed between the CONVERT_T command and the READ_SCRATCHPAD command has to be at least
//750 millisecs (but can be shorter if using a D18B20 type with resolutions < 12 bits)
MCUSR = 0; // clear various “reset” flags
WDTCSR = bit (WDCE) | bit (WDE); // allow changes, disable reset
// set interrupt mode and an interval
WDTCSR = bit (WDIE) | bit (WDP2) | bit (WDP1); //a 1 sec timer
wdt_reset(); // pat the dog
set_sleep_mode (SLEEP_MODE_PWR_DOWN);
sleep_enable();
sleep_cpu ();
sleep_disable(); // cancel sleep after wakeup as a precaution

byte present = ds.reset();  //now we can read the temp sensor data
ds.select(addr);
ds.write(0xBE); // Read Scratchpad
for (int i = 0; i < 2; i++) { // Only read the bytes you need? there is more there
data[i] = ds.read();
}
byte MSB = data[1];
byte LSB = data[0];
float tempRead = ((MSB << 8) | LSB); //using two’s compliment
float TemperatureSum = tempRead / 16; //this converts to C
return TemperatureSum;

}