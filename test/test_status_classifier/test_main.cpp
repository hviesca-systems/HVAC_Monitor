#include <unity.h>
#include <StatusClassifier.h>

#include <string>

struct ClassificationCase
{
    float temperatureF;
    float humidityPercent;
    const char* expectedStatus;
};

void setUp()
{
}

void tearDown()
{
}

void testTemperatureBoundaries()
{
    const ClassificationCase testCases[] =
    {
        {49.9F, 50.0F, "DANGER"},
        {50.0F, 50.0F, "WARNING"},
        {59.9F, 50.0F, "WARNING"},
        {60.0F, 50.0F, "NORMAL"},
        {90.0F, 50.0F, "NORMAL"},
        {90.1F, 50.0F, "WARNING"},
        {100.0F, 50.0F, "WARNING"},
        {100.1F, 50.0F, "DANGER"}
    };

    for (const ClassificationCase& testCase : testCases)
    {
        const std::string actualStatus = classifyStatus(
            testCase.temperatureF,
            testCase.humidityPercent
        );

        TEST_ASSERT_EQUAL_STRING(
            testCase.expectedStatus,
            actualStatus.c_str()
        );
    }
}

void testHumidityBoundaries()
{
    const ClassificationCase testCases[] =
    {
        {75.0F, 19.9F, "DANGER"},
        {75.0F, 20.0F, "WARNING"},
        {75.0F, 29.9F, "WARNING"},
        {75.0F, 30.0F, "NORMAL"},
        {75.0F, 65.0F, "NORMAL"},
        {75.0F, 65.1F, "WARNING"},
        {75.0F, 75.0F, "WARNING"},
        {75.0F, 75.1F, "DANGER"}
    };

    for (const ClassificationCase& testCase : testCases)
    {
        const std::string actualStatus = classifyStatus(
            testCase.temperatureF,
            testCase.humidityPercent
        );

        TEST_ASSERT_EQUAL_STRING(
            testCase.expectedStatus,
            actualStatus.c_str()
        );
    }
}

void testSeverityPrecedence()
{
    const ClassificationCase testCases[] =
    {
        {75.0F, 50.0F, "NORMAL"},
        {95.0F, 50.0F, "WARNING"},
        {75.0F, 70.0F, "WARNING"},
        {105.0F, 70.0F, "DANGER"},
        {95.0F, 80.0F, "DANGER"}
    };

    for (const ClassificationCase& testCase : testCases)
    {
        const std::string actualStatus = classifyStatus(
            testCase.temperatureF,
            testCase.humidityPercent
        );

        TEST_ASSERT_EQUAL_STRING(
            testCase.expectedStatus,
            actualStatus.c_str()
        );
    }
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(testTemperatureBoundaries);
    RUN_TEST(testHumidityBoundaries);
    RUN_TEST(testSeverityPrecedence);

    return UNITY_END();
}
