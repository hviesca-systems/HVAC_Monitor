#include "StatusClassifier.h"

namespace
{
    constexpr float TEMP_DANGER_LOW_F = 50.0F;
    constexpr float TEMP_WARNING_LOW_F = 60.0F;
    constexpr float TEMP_WARNING_HIGH_F = 90.0F;
    constexpr float TEMP_DANGER_HIGH_F = 100.0F;

    constexpr float HUMIDITY_DANGER_LOW_PERCENT = 20.0F;
    constexpr float HUMIDITY_WARNING_LOW_PERCENT = 30.0F;
    constexpr float HUMIDITY_WARNING_HIGH_PERCENT = 65.0F;
    constexpr float HUMIDITY_DANGER_HIGH_PERCENT = 75.0F;
}

std::string classifyStatus(float temperatureF, float humidityPercent)
{
    const bool temperatureDanger =
        temperatureF < TEMP_DANGER_LOW_F || temperatureF > TEMP_DANGER_HIGH_F;

    const bool humidityDanger =
        humidityPercent < HUMIDITY_DANGER_LOW_PERCENT || humidityPercent > HUMIDITY_DANGER_HIGH_PERCENT;

    if (temperatureDanger || humidityDanger)
    {
        return "DANGER";
    }

    const bool temperatureWarning =
        temperatureF < TEMP_WARNING_LOW_F || temperatureF > TEMP_WARNING_HIGH_F;

    const bool humidityWarning =
        humidityPercent < HUMIDITY_WARNING_LOW_PERCENT || humidityPercent > HUMIDITY_WARNING_HIGH_PERCENT;

    if (temperatureWarning || humidityWarning)
    {
        return "WARNING";
    }

    return "NORMAL";
}
