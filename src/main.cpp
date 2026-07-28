#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SHT31.h>
#include <string>

using std::string;

struct HVACReading 
{
  float temperatureF;
  float humidity;
  float vibration;
  int airflow;
  string status;
  unsigned long timeMs;
};

HVACReading currentReading;

Adafruit_SHT31 sht31 = Adafruit_SHT31();

constexpr float TEMP_DANGER_LOW_F = 50.0F;
constexpr float TEMP_WARNING_LOW_F = 60.0F;
constexpr float TEMP_WARNING_HIGH_F = 90.0F;
constexpr float TEMP_DANGER_HIGH_F = 100.0F;

constexpr float HUMIDITY_DANGER_LOW_PERCENT = 20.0F;
constexpr float HUMIDITY_WARNING_LOW_PERCENT = 30.0F;
constexpr float HUMIDITY_WARNING_HIGH_PERCENT = 65.0F;
constexpr float HUMIDITY_DANGER_HIGH_PERCENT = 75.0F;

string classifyStatus(float temperatureF, float humidityPercent)
{
  const bool temperatureDanger = temperatureF < TEMP_DANGER_LOW_F || temperatureF > TEMP_DANGER_HIGH_F;

  const bool humidityDanger = humidityPercent < HUMIDITY_DANGER_LOW_PERCENT || humidityPercent > HUMIDITY_DANGER_HIGH_PERCENT;

  if (temperatureDanger || humidityDanger)
  {
    return "DANGER";
  }

  const bool temperatureWarning = temperatureF < TEMP_WARNING_LOW_F || temperatureF > TEMP_WARNING_HIGH_F;

  const bool humidityWarning = humidityPercent < HUMIDITY_WARNING_LOW_PERCENT || humidityPercent > HUMIDITY_WARNING_HIGH_PERCENT;

  if (temperatureWarning || humidityWarning)
  {
    return "WARNING";
  }

  return "NORMAL";

}

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Wire.begin(21, 22); // SDA, SCL

  if(!sht31.begin(0x45))
  {
    Serial.println("SHT31 sensor not found");
    Serial.println("Check power, ground, SDA, and SCL wiring.");

    while (true)
    {
      delay(1000);
    }
  }
  Serial.println("SHT31 sensor initialized successfully");
}

void loop() 
{
  float temperatureC = sht31.readTemperature();
  float humidityPercent = sht31.readHumidity();

  if (isnan(temperatureC) || isnan(humidityPercent))
  {
    Serial.println("Failed to read data from SHT31 sensor");
    delay(2000);
    return;
  }

  currentReading.temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    currentReading.humidity = humidityPercent;

    currentReading.vibration = 15.0;
    currentReading.airflow = 620;
    currentReading.status = classifyStatus(currentReading.temperatureF, currentReading.humidity);
    currentReading.timeMs = millis();

    Serial.println();
    Serial.println("Live HVAC reading:");

    Serial.print("Temperature: ");
    Serial.print(currentReading.temperatureF);
    Serial.println(" F");

    Serial.print("Humidity: ");
    Serial.print(currentReading.humidity);
    Serial.println(" %");

    Serial.print("Vibration: ");
    Serial.println(currentReading.vibration);

    Serial.print("Airflow: ");
    Serial.println(currentReading.airflow);

    Serial.print("Status: ");
    Serial.println(currentReading.status.c_str());

    Serial.print("Time: ");
    Serial.print(currentReading.timeMs);
    Serial.println(" ms");

    delay(2000);
}