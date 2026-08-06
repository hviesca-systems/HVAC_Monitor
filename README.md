# ESP32 HVAC Machine Health Monitoring System

An ESP32-based embedded monitoring prototype that measures HVAC temperature, humidity, and vibration conditions, displays live readings locally, generates visual and audible status alerts, and records operating data to a microSD card in CSV format.

The project combines embedded C++, sensor integration, hardware diagnostics, automated status-classification testing, local user feedback, persistent data logging, and a professional Git/GitHub development workflow.

## Project Status

**Current release milestone: `v0.1.0` preparation**

The verified prototype currently integrates:

- SHT31 temperature and humidity sensing
- MPU6050 acceleration-based vibration monitoring
- SSD1306 OLED display output
- Green, yellow, and red status LEDs
- Active-buzzer danger alerts
- Automatic `NORMAL`, `WARNING`, and `DANGER` classification
- microSD data logging using SPI
- Native Unity tests for the environmental-status classifier
- Dedicated I2C and microSD diagnostic firmware

The current system has been tested on physical hardware using PlatformIO and the Arduino framework. Temperature, humidity, vibration estimate, operating status, and elapsed time are stored in `/hvac_readings.csv`.

Airflow is not currently measured. The earlier placeholder airflow value was removed so the firmware reports only values produced by installed hardware. Differential-pressure or airflow sensing remains planned for a later, calibrated project phase.

## Project Objectives

- Monitor HVAC temperature, humidity, and vibration conditions using installed sensors.
- Classify temperature and humidity conditions as `NORMAL`, `WARNING`, or `DANGER`.
- Present live measurements and system status through an OLED display.
- Provide local visual and audible alerts using LEDs and an active buzzer.
- Record verified sensor measurements and status information to a microSD card.
- Continue core monitoring when removable storage is unavailable.
- Support hardware troubleshooting through dedicated diagnostic firmware.
- Maintain modular embedded C++ firmware and reusable classification logic.
- Validate classification behavior through native automated tests.
- Document hardware interfaces, firmware behavior, testing, and known limitations.
- Establish a foundation for future vibration calibration, airflow sensing, trend analysis, and field testing.

## Current Implementation

- ESP32 development using PlatformIO and the Arduino framework.
- SHT31 temperature and humidity sensor at I2C address `0x45`.
- MPU6050 accelerometer at I2C address `0x68`.
- SSD1306 OLED display at I2C address `0x3C`.
- Shared I2C bus using GPIO 21 for SDA and GPIO 22 for SCL.
- Live temperature, humidity, and acceleration-based vibration readings.
- Celsius-to-Fahrenheit temperature conversion.
- Detection and reporting of failed SHT31 readings.
- Automatic environmental classification as `NORMAL`, `WARNING`, or `DANGER`.
- Reusable `StatusClassifier` C++ module containing the classification thresholds and decision algorithm.
- Severity precedence in which `DANGER` overrides `WARNING`, and `WARNING` overrides `NORMAL`.
- Native Unity tests covering temperature boundaries, humidity boundaries, and severity precedence.
- Structured measurement storage using the `HVACReading` C++ structure.
- Elapsed-time collection using `millis()`.
- SSD1306 OLED output for live measurements and status.
- Green, yellow, and red LED status indicators.
- Active-buzzer alert during `DANGER` conditions.
- microSD initialization and CSV logging over SPI.
- Graceful continuation of monitoring when SD initialization fails.
- Dedicated I2C scanner and microSD diagnostic firmware.
- Serial Monitor output at 115200 baud.
- PlatformIO-based library and dependency management.

## Status Classification

The firmware classifies each valid temperature and humidity reading using the reusable `classifyStatus()` function.

### Temperature Thresholds

| Temperature range | Status |
|---|---|
| Below 50°F | `DANGER` |
| 50°F to below 60°F | `WARNING` |
| 60°F through 90°F | `NORMAL` |
| Above 90°F through 100°F | `WARNING` |
| Above 100°F | `DANGER` |

### Humidity Thresholds

| Relative humidity range | Status |
|---|---|
| Below 20% | `DANGER` |
| 20% to below 30% | `WARNING` |
| 30% through 65% | `NORMAL` |
| Above 65% through 75% | `WARNING` |
| Above 75% | `DANGER` |

When temperature and humidity produce different severity levels, the classifier applies the following precedence:

```text
DANGER > WARNING > NORMAL
```

For example, a warning-level temperature combined with danger-level humidity produces an overall `DANGER` result.

These values are the current prototype thresholds used for firmware development and testing. Future system testing may determine whether they should be adjusted or made configurable.

## Technology Stack

### Hardware

- ESP32 development board
- SHT31 temperature and humidity sensor
- MPU6050 accelerometer
- SSD1306 128 x 64 OLED display
- microSD card module
- FAT32-formatted microSD card
- Green, yellow, and red LEDs
- Current-limiting resistors
- Active buzzer
- Breadboard and jumper wires
- Digital multimeter

### Software and Frameworks

- C and C++
- Arduino framework
- PlatformIO
- Visual Studio Code
- Git and GitHub
- Unity native test framework

### Libraries

- Adafruit SHT31 Library
- Adafruit MPU6050
- Adafruit Unified Sensor
- Adafruit GFX Library
- Adafruit SSD1306
- Wire
- SPI
- SD
- FS
- Project-local `StatusClassifier` library

### Communication Interfaces

- I2C for the SHT31, MPU6050, and OLED
- SPI for the microSD module
- GPIO for LEDs and the active buzzer
- UART serial communication for diagnostics and live output

## Current System Architecture

The firmware follows a multi-input, multi-output embedded-data pipeline:

1. The ESP32 initializes serial communication, the I2C bus, and the SPI bus.
2. The microSD card is initialized. If initialization fails, monitoring continues without data logging.
3. The SSD1306 OLED, SHT31 sensor, and MPU6050 sensor are initialized.
4. The firmware reads temperature and humidity from the SHT31.
5. Invalid SHT31 readings are detected before further processing.
6. Temperature is converted from Celsius to Fahrenheit.
7. Acceleration data is collected from the MPU6050.
8. A vibration estimate is calculated from acceleration magnitude relative to gravity.
9. Temperature and humidity are passed to the `StatusClassifier` module.
10. The classifier returns `NORMAL`, `WARNING`, or `DANGER`.
11. The current measurements, status, and elapsed time are stored in an `HVACReading` structure.
12. The OLED displays the current measurements and status.
13. The LEDs and buzzer provide local status feedback.
14. The reading is appended to `/hvac_readings.csv` when the microSD card is available.
15. The same reading is reported through the Serial Monitor.
16. The process repeats approximately every two seconds.

```text
SHT31 Sensor --------\
                      \
MPU6050 Sensor --------> ESP32 Firmware
                           |
                           | validation, conversion,
                           | vibration estimate, and classification
                           v
                    HVACReading Structure
                           |
          +----------------+----------------+
          |                |                |
          v                v                v
     OLED Display     LEDs and Buzzer   Serial Monitor
                           |
                           v
                    Local Status Alert

HVACReading Structure
          |
          | SPI
          v
   microSD CSV Logging
```

## Firmware Data Model

The firmware stores one HVAC sample using the following fields:

| Field | Type | Current purpose |
|---|---|---|
| `temperatureF` | `float` | Live temperature in degrees Fahrenheit |
| `humidity` | `float` | Live relative humidity percentage |
| `vibration` | `float` | Acceleration-based vibration estimate in meters per second squared |
| `status` | `std::string` | Calculated environmental-condition label |
| `timeMs` | `unsigned long` | Elapsed time since the ESP32 started, in milliseconds |

The `HVACReading` structure groups all values belonging to one observation into a single object. The same object is passed to the OLED, status-output, Serial Monitor, and microSD logging functions.

Airflow is intentionally absent from the data model because the current prototype does not contain calibrated airflow-sensing hardware.

## Repository Structure

```text
HVAC_Monitor/
|-- .vscode/
|   `-- extensions.json
|-- diagnostics/
|   |-- I2C_Scanner.cpp
|   `-- SD_Card_Test.cpp
|-- include/
|-- lib/
|   `-- StatusClassifier/
|       `-- src/
|           |-- StatusClassifier.cpp
|           `-- StatusClassifier.h
|-- src/
|   `-- main.cpp
|-- test/
|   `-- test_status_classifier/
|       `-- test_main.cpp
|-- .gitignore
|-- platformio.ini
`-- README.md
```

### Directory Responsibilities

- `src/` contains the primary ESP32 firmware.
- `diagnostics/` contains focused hardware-troubleshooting programs.
- `include/` is reserved for project header files.
- `lib/StatusClassifier/` contains the reusable environmental-classification module.
- `test/test_status_classifier/` contains native Unity tests for boundaries and severity precedence.
- `platformio.ini` defines the board, framework, serial speed, and library dependencies.
- `.gitignore` prevents generated build files and local development artifacts from entering the repository.

## Current Hardware Configuration

### I2C Bus

| Device | Connection | ESP32 configuration |
|---|---|---|
| SHT31 | SDA | GPIO 21 |
| SHT31 | SCL | GPIO 22 |
| SHT31 | I2C address | `0x45` |
| MPU6050 | SDA | GPIO 21 |
| MPU6050 | SCL | GPIO 22 |
| MPU6050 | I2C address | `0x68` |
| SSD1306 OLED | SDA | GPIO 21 |
| SSD1306 OLED | SCL | GPIO 22 |
| SSD1306 OLED | I2C address | `0x3C` |

### Status Outputs

| Output | ESP32 pin |
|---|---|
| Green LED | GPIO 27 |
| Yellow LED | GPIO 26 |
| Red LED | GPIO 25 |
| Active buzzer | GPIO 14 |

### microSD SPI Bus

| microSD connection | ESP32 pin |
|---|---|
| SCK / CLK | GPIO 18 |
| MISO | GPIO 19 |
| MOSI | GPIO 23 |
| CS | GPIO 5 |
| VCC | 3.3 V |
| GND | GND |

### Development Configuration

| Setting | Value |
|---|---|
| Serial Monitor speed | 115200 baud |
| Primary PlatformIO environment | `esp32dev` |
| I2C diagnostic environment | `i2c_scanner` |
| microSD diagnostic environment | `sd_card_test` |

The wiring and I2C address must be verified against the specific sensor breakout being used before uploading firmware.

## Build and Run

### Prerequisites

- Visual Studio Code
- PlatformIO IDE extension
- USB data cable compatible with the ESP32
- ESP32 development board
- SHT31 temperature and humidity sensor
- MPU6050 accelerometer
- SSD1306 128 x 64 OLED display
- microSD card module
- FAT32-formatted microSD card
- Green, yellow, and red LEDs
- Current-limiting resistors
- Active buzzer
- Breadboard and jumper wires

### PlatformIO Workflow

1. Clone or download the repository.
2. Open the repository folder in Visual Studio Code.
3. Allow PlatformIO to install the platform and library dependencies defined in `platformio.ini`.
4. Verify the wiring and device addresses before applying power.
5. Connect the ESP32 using a USB data cable.
6. Build the main `esp32dev` environment.
7. Upload the firmware to the ESP32.
8. Open the Serial Monitor at 115200 baud.
9. Confirm successful initialization of the microSD card, OLED, SHT31, and MPU6050.
10. Verify live OLED and Serial Monitor readings.
11. Confirm that the status LEDs and buzzer respond to the calculated status.
12. Power down the ESP32 before removing the microSD card.
13. Open `/hvac_readings.csv` and verify that measurements were appended correctly.

### Command-Line Workflow

Build the main firmware:

```powershell
pio run -e esp32dev
```

Upload the main firmware:

```powershell
pio run -e esp32dev --target upload
```

Open the Serial Monitor:

```powershell
pio device monitor --baud 115200
```

Build and upload the I2C diagnostic firmware:

```powershell
pio run -e i2c_scanner
pio run -e i2c_scanner --target upload
```

Build and upload the microSD diagnostic firmware:

```powershell
pio run -e sd_card_test
pio run -e sd_card_test --target upload
```

The command-line workflow requires the PlatformIO Core command-line tools to be available in the terminal environment.

### Native Unit Tests

The status-classification algorithm can be tested on the development computer without connecting an ESP32:

```powershell
pio test -e native
```

The current test suite evaluates:

- 8 temperature-boundary scenarios
- 8 humidity-boundary scenarios
- 5 severity-precedence scenarios

The ESP32 firmware can be compiled separately with:

```powershell
pio run -e esp32dev
```

## CSV Data Logging

When the microSD card initializes successfully, the firmware creates or appends to:

```text
/hvac_readings.csv
```

The logger uses the following column order:

```csv
time_ms,temperature_f,humidity_percent,vibration_mps2,status
```

Example records:

```csv
1425,86.58,57.29,0.39,NORMAL
3506,86.58,57.42,0.34,NORMAL
5587,86.54,57.43,0.33,NORMAL
```

| Column | Description |
|---|---|
| `time_ms` | Elapsed milliseconds since the ESP32 started |
| `temperature_f` | SHT31 temperature measurement in degrees Fahrenheit |
| `humidity_percent` | SHT31 relative humidity measurement |
| `vibration_mps2` | MPU6050 acceleration-based vibration estimate |
| `status` | Environmental classification returned by `StatusClassifier` |

The header is written only when the file is empty. Existing measurements are preserved, and new readings are appended after each monitoring cycle.

The file is closed after every completed record to reduce the chance of losing multiple readings during an unexpected shutdown. The ESP32 should still be powered down before physically removing the microSD card.

## Known Measurement Limitations

- Temperature and humidity are measured directly by the SHT31.
- Vibration is calculated from live MPU6050 acceleration data, but it is currently an uncalibrated motion estimate rather than a validated machine-vibration metric.
- The vibration estimate uses acceleration magnitude relative to gravity and does not yet use RMS analysis, filtering, frequency analysis, or equipment-specific thresholds.
- Airflow is not measured and is not included in the firmware data model or CSV log.
- `timeMs` records elapsed milliseconds since startup rather than real calendar date and time.
- Temperature and humidity status thresholds are prototype values and may require adjustment after field testing.
- The breadboard implementation is a development prototype and is not ready for permanent HVAC installation.

## Roadmap

### Near-Term Development

- Mount the MPU6050 securely and collect repeatable baseline vibration data.
- Replace the single-sample vibration estimate with a windowed measurement such as RMS vibration.
- Compare equipment-off, startup, normal-operation, and abnormal-motion data.
- Develop documented vibration thresholds based on collected measurements.
- Add real timestamps using network time or a real-time clock module.
- Add configurable data-logging intervals and session identifiers.
- Improve SD-card error reporting and recovery behavior.

### Hardware Development

- Improve power delivery for operation away from a computer.
- Replace temporary breadboard connections with a more secure prototype assembly.
- Design and print a protective enclosure with sensor ventilation and microSD access.
- Add strain relief and secure mounting for external wiring.
- Evaluate differential-pressure sensing for filter restriction and airflow-related monitoring.
- Calibrate any future airflow or pressure measurements before adding them to the data model.

### Data Analysis

- Import logged CSV measurements into Python.
- Plot temperature, humidity, and vibration trends over time.
- Compare data from multiple operating sessions.
- Identify startup, shutdown, and unusual vibration events.
- Evaluate basic anomaly-detection methods after collecting sufficient real-world data.

### Long-Term Goal

Develop the breadboard prototype into a documented, calibrated, and enclosed HVAC condition-monitoring device suitable for controlled field testing.
