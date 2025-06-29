#pragma once
#ifndef UNIT_TEST    // Or a specific macro defined for your native test env
#include <WString.h> // For Arduino compilation
#else
#include <ArduinoFake.h> // For native compilation
#endif

float calcAvg(float *values, long currentNumValidValues);
float calcMax(float *values, long currentNumValidValues);
float calcMin(float *values, long currentNumValidValues);
String formatFloat(float value);