/*
  CustomCharacter.ino
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-9-18

  Grove - Serial LCD RGB Backlight demo.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

// make some custom characters:
byte l[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b01010,
  0b01110,
  0b00000,
  0b00000
};
byte heart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

byte smiley[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b10001,
    0b01110,
    0b00000
};

byte frownie[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b00000,
    0b01110,
    0b10001
};

byte armsDown[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b00100,
    0b01110,
    0b10101,
    0b00100,
    0b01010
};
  
byte bl[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
byte armsUp[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b10101,
    0b01110,
    0b00100,
    0b00100,
    0b01010
};


void setup() 
{

    lcd.begin(16, 2);
 #if 1   
    // create a new character
    lcd.createChar(0, heart);// nhét máp vào cgram
    // create a new character
    lcd.createChar(1, smiley);
    // create a new character
    lcd.createChar(2, frownie);
    // create a new character
    lcd.createChar(3, armsDown);
    // create a new character
    lcd.createChar(4, armsUp);
    lcd.createChar(5,l);
    lcd.createChar(6,bl);
#endif 
    /*// set up the lcd's number of columns and rows:
    
    
    lcd.setCursor(0, 0);// sét location
    // Print a message to the lcd.
    lcd.print("I ");
    lcd.write((unsigned char)0);
    lcd.print(" LeSyVan ");
    lcd.write(1);
    lcd.setCursor(4, 2);
    lcd.write(5);*/

}

void loop() 
{
    int sensorReading = analogRead(A0);
    int delayTime = map(sensorReading, 0, 1023, 200, 1000);
    int de = map(sensorReading, 0, 1023, 0, 15);
    for(int i = 0;i<4;i++)
    {
      lcd.setCursor(i,0);
      lcd.write(6);
    }
    lcd.setCursor(0,0);
    lcd.print(sensorReading*15/1023);
    lcd.setCursor(de-1, 1);
    lcd.write(6);
    lcd.setCursor(de+1, 1);
    lcd.write(6);
    lcd.setCursor(de, 1);
    // draw the little man, arms down:
    if(de%2==0){
      lcd.write(3); 
    }
    else{
      lcd.write(4);
    }
    
    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/