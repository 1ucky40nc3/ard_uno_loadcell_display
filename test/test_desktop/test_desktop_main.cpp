using namespace std;
#include <unity.h>
#include <ArduinoFake.h>
#include <stdlib.h>
#include "utils.h"

void test_calcAvg()
{
    float values[1] = {0.0};
    float avgValue = calcAvg(values, 1);
    TEST_ASSERT_TRUE(avgValue == 0.0);
}

void test_calcMax()
{
    float values[1] = {0.0};
    float maxValue = calcMax(values, 1);
    TEST_ASSERT_TRUE(maxValue == 0.0);
}

void test_calcMin()
{
    float values[1] = {0.0};
    float minValue = calcMin(values, 1);
    TEST_ASSERT_TRUE(minValue == 0.0);
}

void test_formatFloat()
{
    float floatValue0 = 0.0;
    String stringValue0 = formatFloat(floatValue0);
    TEST_ASSERT_EQUAL_STRING("  0.0", stringValue0.c_str());

    float floatValue1 = 10.01;
    String stringValue1 = formatFloat(floatValue1);
    TEST_ASSERT_EQUAL_STRING(" 10.0", stringValue1.c_str());

    float floatValue2 = 100.09;
    String stringValue2 = formatFloat(floatValue2);
    TEST_ASSERT_EQUAL_STRING("100.1", stringValue2.c_str());

    float floatValue3 = 1000;
    String stringValue3 = formatFloat(floatValue3);
    TEST_ASSERT_EQUAL_STRING("999.9", stringValue3.c_str());

    float floatValue4 = -10;
    String stringValue4 = formatFloat(floatValue4);
    TEST_ASSERT_EQUAL_STRING(" -10.0", stringValue4.c_str());

    float floatValue5 = -100.1;
    String stringValue5 = formatFloat(floatValue5);
    TEST_ASSERT_EQUAL_STRING("-100.1", stringValue5.c_str());
}

void setUp() {}

void tearDown() {}

int main()
{
    UNITY_BEGIN(); // Initialize Unity

    // Run the tests
    RUN_TEST(test_calcAvg);
    RUN_TEST(test_calcMax);
    RUN_TEST(test_calcMin);
    RUN_TEST(test_formatFloat);

    UNITY_END(); // End Unity

    return 0;
}