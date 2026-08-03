#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_SHT31.h>
#include <string>
#include <StatusClassifier.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

constexpr int OLED_WIDTH = 128;
constexpr int OLED_HEIGHT = 64;
constexpr int OLED_RESET = -1;
constexpr uint8_t OLED_ADDRESS = 0x3C;

constexpr int GREEN_LED_PIN = 27;
constexpr int YELLOW_LED_PIN = 26;
constexpr int RED_LED_PIN = 25;
constexpr int BUZZER_PIN = 14;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Wire.begin(21, 22); // SDA, SCL

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
  {
    Serial.println("OLED display not found");

    while (true)
    {
      delay(1000);
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("HVAC Monitor");
  display.println("OLED initialized");
  display.display();

  Serial.println("OLED display initialized successfully");

  if (!sht31.begin(0x45))
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

void updateDisplay(const HVACReading& reading)
{
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);

  display.println("HVAC Monitor");
  display.println();

  display.print("Temp: ");
  display.print(reading.temperatureF, 1);
  display.println(" F");

  display.print("Humidity: ");
  display.print(reading.humidity, 1);
  display.println(" %");

  display.print("Status: ");
  display.println(reading.status.c_str());

  display.display();
}

void updateStatusOutput(const string& status)
{
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  if (status == "DANGER")
  {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else if (status == "WARNING")
  {
    digitalWrite(YELLOW_LED_PIN, HIGH);
  }
  else
  {
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
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
    updateDisplay(currentReading);
    updateStatusOutput(currentReading.status);

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