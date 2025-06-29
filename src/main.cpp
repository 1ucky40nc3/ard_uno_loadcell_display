#include <Arduino.h>

// Note: This is an example is adapted from https://wiki.52pi.com/index.php?title=Z-0234

/*
Connect LCD1602 module to Arduino Uno board as following:

I2C -> LCD1602	Arduino Uno board
GND ->	GND
VCC ->	5V
SDA ->	A4 /pin 20 mega2560
SCL ->	A5 /pin 21 mega2560

Setup your scale and start the sketch WITHOUT a weight on the scale
Once readings are displayed place the weight on the scale
Press +/- or a/z to adjust the calibration_factor until the output readings match the known weight
Arduino pin 6   -> HX711 CLK
Arduino pin 5   -> HX711 DOUT
Arduino pin 5V  -> HX711 VCC
Arduino pin GND -> HX711 GND
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

HX711 scale;

float calibration_factor = 33; // this calibration factor is adjusted according to my load cell
float units;
float ounces;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27, if new version please use 0x3F instead.

void setup()
{
  Serial.begin(9600);

  lcd.init();      // initialize the lcd
  lcd.backlight(); // open the backlight

  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(5, 6);
  scale.set_scale();
  scale.tare(); // Reset the scale to 0

  long zero_factor = scale.read_average(); // Get a baseline reading
  Serial.print("Zero factor: ");           // This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop()
{

  scale.set_scale(calibration_factor); // Adjust to this calibration factor

  Serial.print("Reading: ");
  units = scale.get_units();

  Serial.print(units);
  Serial.print(" grams");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }

  lcd.setCursor(0, 0);
  lcd.print(units);

  lcd.setCursor(0, 1);

  if (units < 0)
  {
    const char *description = "cmp";
    lcd.print(description);
  }
  else
  {
    const char *description = "tns";
    lcd.print(description);
  }
}