#include <Arduino.h>
#include <Wire.h>

// Feature Branch Test
void setup()
{
    Serial.begin(9600);
    delay(1000);

    Wire.begin(21, 22);

    Serial.println();
    Serial.println("Starting I2C scan...");
}

void loop()
{
    int deviceCount = 0;

    Serial.println();
    Serial.println("Scanning I2C bus...");

    for (uint8_t address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        uint8_t error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");

            if (address < 16)
            {
                Serial.print("0");
            }

            Serial.println(address, HEX);
            deviceCount++;
        }
    }

    if (deviceCount == 0)
    {
        Serial.println("No I2C devices found.");
    }
    else
    {
        Serial.print("Total devices found: ");
        Serial.println(deviceCount);
    }

    Serial.println("Scan complete.");

    delay(5000);
}