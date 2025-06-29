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

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>
#include <utils.h>

HX711 scale;

float calibration_factor = 33; // this calibration factor is adjusted according to my load cell

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27, if new version please use 0x3F instead.

// A buffer for about 5 seconds measurements
// Note: The Load Cell has a sampling rate of 80 hz
const long measurementBufferSize = 200;
float measurementBuffer[measurementBufferSize];
// The index of the measurements
long measurementIndex = 0;

// Flag to indicate if the buffer has been filled at least once
bool bufferFull = false;

void setup()
{
  Serial.begin(9600);

  lcd.init();      // initialize the lcd
  lcd.backlight(); // open the backlight

  delay(100);
  Serial.println("Displaying information on LCD");

  // Display the calibration message on the LCD display
  lcd.setCursor(0, 0);
  lcd.print("Calibration...");
  lcd.setCursor(0, 1);
  lcd.print("Do not load!");

  // Show the calibration message on the serial output
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  // Begin the scale calibration
  scale.begin(5, 6);
  scale.set_scale();
  scale.tare();                            // Reset the scale to 0
  long zero_factor = scale.read_average(); // Get a baseline reading
  Serial.print("Zero factor: ");           // This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);

  // Clear the LCD display after the calibration
  lcd.clear();

  // Initialize the measurements buffer with zeros
  for (long i = 0; i < measurementBufferSize; i++)
  {
    measurementBuffer[i] = 0.0;
  }
}

void loop()
{

  scale.set_scale(calibration_factor); // Adjust to this calibration factor

  // Get the scale readings in gram and convert to kg
  float measurement = scale.get_units() / 1000;
  // We normalize between [-999.9,999.9] to avoid measurements outside of the display range
  // The display output should have a max of 3 chars before the decimal point and one after
  // Note: The normalization is also in the max contraints of the load cell of about [-200.0,200.0]
  if (measurement > 999.9)
    measurement = 999.9;
  else if (measurement < -999.9)
  {
    measurement = -999.9;
  }

  // Output the measurement on the serial output
  Serial.print("Reading: ");
  Serial.print(measurement);
  Serial.print(" kg");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  // Set the measurement in the buffer
  if (measurementIndex >= measurementBufferSize)
  {
    // Keep the measurement index in bounds
    measurementIndex = 0;
  }
  measurementBuffer[measurementIndex] = measurement;

  // Update the measurement index at the end of each loop
  measurementIndex++;

  // Check if the buffer has just become full
  if (measurementIndex >= measurementBufferSize)
  {
    measurementIndex = 0; // Wrap around to the beginning
    bufferFull = true;    // Mark buffer as full
  }

  // Determine the number of valid measurements to use for calculation
  long numValidMeasurements;
  if (bufferFull)
  {
    numValidMeasurements = measurementBufferSize;
  }
  else
  {
    numValidMeasurements = measurementIndex; // Use current index as count if not full
  }

  // Calculate the max and averages
  float avgMeasurement = calcAvg(measurementBuffer, numValidMeasurements);
  float maxMeasurement = calcMax(measurementBuffer, numValidMeasurements);
  float minMeasurement = calcMin(measurementBuffer, numValidMeasurements);

  String measurementString = formatFloat(measurement);
  String avgMeasurementString = formatFloat(avgMeasurement);

  // Display the average and top labels
  lcd.setCursor(0, 1);
  lcd.print("a");
  lcd.setCursor(9, 1);
  lcd.print("t");

  // Display the kg label
  lcd.setCursor(9, 0);
  lcd.print("kg");

  // Display the measurements and calculation on the screen
  lcd.setCursor(2, 0);
  lcd.print(measurementString.c_str());
  lcd.setCursor(2, 1);
  lcd.print(avgMeasurementString);

  if (measurement < 0)
  {
    lcd.setCursor(13, 0);
    const char *description = "cmp";
    lcd.print(description);
    lcd.setCursor(11, 1);
    String minMeasurementString = formatFloat(minMeasurement);
    lcd.print(minMeasurementString);
  }
  else
  {
    lcd.setCursor(13, 0);
    const char *description = "tns";
    lcd.print(description);
    lcd.setCursor(11, 1);
    String maxMeasurementString = formatFloat(maxMeasurement);
    lcd.print(maxMeasurementString);
  }

  // Adjust the calibration factor based on the serial input
  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
}