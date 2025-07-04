// Note: This is an example is adapted from https://wiki.52pi.com/index.php?title=Z-0234

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27, if new version please use 0x3F instead.

void setup()
{
    lcd.init();      // initialize the lcd
    lcd.backlight(); // open the backlight
}

void loop()
{
    lcd.setCursor(3, 0);        // set the cursor to column 3, line 0
    lcd.print("Hello GeeekPi"); // Print a message to the LCD

    lcd.setCursor(2, 1);      // set the cursor to column 2, line 1
    lcd.print("hello world"); // Print a message to the LCD.
}