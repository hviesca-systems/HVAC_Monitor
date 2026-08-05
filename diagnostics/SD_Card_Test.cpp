#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

constexpr int SD_CS_PIN = 5;

void setup()
{
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("Starting microSD card diagnostics...");

  SPI.begin(18, 19, 23, SD_CS_PIN);

  if (!SD.begin(SD_CS_PIN))
  {
    Serial.println("microSD card initialization failed!");
    Serial.println("Check card format, wiring, and CS pin.");
    return;
  }

  Serial.println("microSD card initialization successful.");

  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE)
  {
    Serial.println("No microSD card detected.");
    return;
  }

  Serial.print("Card Type: ");

  switch (cardType)
  {
    case CARD_MMC:
      Serial.println("MMC");
      break;

    case CARD_SD:
      Serial.println("SDSC");
      break;

    case CARD_SDHC:
      Serial.println("SDHC");
      break;

    default:
      Serial.println("Unknown");
      break;
  }

  uint64_t cardSizeMb =
      SD.cardSize() / (1024ULL * 1024ULL);

  Serial.print("Card Size: ");
  Serial.print(cardSizeMb);
  Serial.println(" MB");

  File testFile = SD.open("/sd_test.txt", FILE_WRITE);

  if (!testFile)
  {
    Serial.println("Failed to open sd_test.txt");
    return;
  }

  testFile.println("ESP32 microSD test successful.");
  testFile.close();

  Serial.println("Test file written successfully.");
}

void loop()
{
}
