#include <stdlib.h>

#ifndef UNIT_TEST    // Or a specific macro defined for your native test env
#include <WString.h> // For Arduino compilation
#else
#include <ArduinoFake.h> // For native compilation
#endif

float calcAvg(float *values, long currentNumValidValues)
{
    float sum = 0;
    for (long i = 0; i < currentNumValidValues; i++)
    { // Corrected loop initialization
        sum += values[i];
    }
    if (currentNumValidValues > 0)
    {
        return sum / currentNumValidValues;
    }
    else
    {
        return 0.0; // Avoid division by zero
    }
}

float calcMax(float *values, long currentNumValidValues)
{
    if (currentNumValidValues == 0)
    {
        return 0.0; // Or -FLT_MAX, depending on desired behavior for empty buffer
    }

    float val = values[0]; // Initialize with the first valid element
    for (long i = 1; i < currentNumValidValues; i++)
    { // Corrected loop initialization
        if (values[i] > val)
        { // Corrected logic: find greater value
            val = values[i];
        }
    }
    return val;
}

float calcMin(float *values, long currentNumValidValues)
{
    if (currentNumValidValues == 0)
    {
        return 0.0; // Or -FLT_MAX, depending on desired behavior for empty buffer
    }

    float val = values[0]; // Initialize with the first valid element
    for (long i = 1; i < currentNumValidValues; i++)
    { // Corrected loop initialization
        if (values[i] < val)
        { // Corrected logic: find greater value
            val = values[i];
        }
    }
    return val;
}

String formatFloat(float value)
{
    // We normalize between [-999.9,999.9] to avoid measurements outside of the display range
    // The display output should have a max of 3 chars before the decimal point and one after
    // Note: The normalization is also in the max contraints of the load cell of about [-200.0,200.0]
    float normalizedValue = value;
    if (normalizedValue > 999.9)
        normalizedValue = 999.9;
    else if (normalizedValue < -999.9)
    {
        normalizedValue = -999.9;
    }

    // Buffer size of 7 bytes to hold 5 characters + null terminator + optional negtive sign
    char buffer[7];
    // Allow more width for negative numbers
    signed char width = 5;
    if (normalizedValue < 0)
    {
        width = 6;
    }
    dtostrf(normalizedValue, width, 1, buffer);
    String formattedString = String(buffer);
    return buffer;
}