using namespace std;
#include <unity.h>
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

void setUp() {}

void tearDown() {}

int main()
{
    UNITY_BEGIN(); // Initialize Unity

    // Run the tests
    RUN_TEST(test_calcAvg);
    RUN_TEST(test_calcMax);

    UNITY_END(); // End Unity

    return 0;
}