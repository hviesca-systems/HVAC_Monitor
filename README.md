# ESP32 HVAC Health Monitoring System

An ESP32-based embedded-systems project that currently monitors HVAC temperature and humidity, with vibration sensing, airflow analysis, local alerts, and condition classification planned for later development.

The current PlatformIO firmware reads live data from an SHT31 sensor, stores measurements in a structured C++ data model, detects sensor-read failures, and reports results through the Serial Monitor. The project is being expanded incrementally as a practical study of embedded C++, data structures, algorithms, system architecture, and professional Git workflows.

## Project Status

**Active development - PlatformIO reimplementation**

This repository is a structured reimplementation of an earlier Arduino IDE prototype. The system is being rebuilt incrementally in VS Code and PlatformIO to improve the firmware architecture, documentation, testing workflow, and understanding of embedded C++, data structures, algorithms, and system design.

The current firmware reads live temperature and humidity data from an SHT31 sensor. Vibration, airflow, and operating-status values are currently simulated while the corresponding hardware and classification logic are developed.

## Project Objectives

- Monitor HVAC temperature and humidity conditions.
- Detect abnormal vibration that may indicate mechanical problems.
- Measure or estimate HVAC airflow conditions.
- Classify operating conditions as normal, warning, or danger.
- Present system status locally without requiring an internet connection.
- Support hardware troubleshooting through dedicated diagnostic programs.
- Create a modular foundation for data logging and long-term condition monitoring.
- Develop the project using maintainable embedded-software architecture.

## Current Implementation

- ESP32 development using PlatformIO and the Arduino framework.
- SHT31 temperature and humidity sensor initialization at I2C address `0x45`.
- I2C communication using GPIO 21 for SDA and GPIO 22 for SCL.
- Live temperature and humidity measurements.
- Celsius-to-Fahrenheit temperature conversion.
- Detection and reporting of failed SHT31 readings.
- Structured measurement storage using the `HVACReading` C++ structure.
- Timestamp collection using `millis()`.
- Serial Monitor output at 115200 baud.
- Dedicated I2C scanner for sensor and display diagnostics.
- PlatformIO-based library and dependency management.

## Technology Stack

### Hardware

- ESP32 development board
- SHT31 temperature and humidity sensor
- I2C communication bus

### Software

- C++
- Arduino framework
- PlatformIO
- Visual Studio Code
- Git and GitHub
- Adafruit SHT31 library

## Current System Architecture

The current firmware follows a simple embedded-data pipeline:

1. The ESP32 initializes serial communication and the I2C bus.
2. The SHT31 sensor is initialized at I2C address `0x45`.
3. The firmware reads temperature and humidity measurements.
4. Invalid sensor readings are detected before further processing.
5. Temperature is converted from Celsius to Fahrenheit.
6. Measurements and placeholder values are stored in an `HVACReading` structure.
7. The current reading is reported through the Serial Monitor.
8. The process repeats every two seconds.

```text
SHT31 Sensor
     |
     | I2C
     v
ESP32 Firmware
     |
     | validation and conversion
     v
HVACReading Data Structure
     |
     | formatted output
     v
Serial Monitor
```

## Firmware Data Model

The firmware currently stores one HVAC sample using the following fields:

| Field | Type | Current purpose |
|---|---|---|
| `temperatureF` | `float` | Live temperature in degrees Fahrenheit |
| `humidity` | `float` | Live relative humidity percentage |
| `vibration` | `float` | Simulated vibration value |
| `airflow` | `int` | Simulated airflow value |
| `status` | `std::string` | Simulated system-condition label |
| `timeMs` | `unsigned long` | Time since the ESP32 started, in milliseconds |

The `HVACReading` structure acts as the firmware's current data model. It groups the values belonging to one HVAC observation into a single object rather than storing them as unrelated variables.

As the project develops, this structure can be passed to functions responsible for:

- Condition classification
- OLED output
- Alert generation
- Data logging
- Historical analysis

## Repository Structure

```text
HVAC_Monitor/
|-- .vscode/
|   `-- extensions.json
|-- diagnostics/
|   `-- I2C_Scanner.cpp
|-- include/
|-- lib/
|-- src/
|   `-- main.cpp
|-- test/
|-- .gitignore
|-- platformio.ini
`-- README.md
```

### Directory Responsibilities

- `src/` contains the primary ESP32 firmware.
- `diagnostics/` contains focused hardware-troubleshooting programs.
- `include/` is reserved for project header files.
- `lib/` is reserved for project-specific reusable libraries.
- `test/` is reserved for automated or hardware-assisted tests.
- `platformio.ini` defines the board, framework, serial speed, and library dependencies.
- `.gitignore` prevents generated build files and local development artifacts from entering the repository.

## Current Hardware Configuration

| Connection | ESP32 configuration |
|---|---|
| SHT31 SDA | GPIO 21 |
| SHT31 SCL | GPIO 22 |
| SHT31 I2C address | `0x45` |
| Serial Monitor speed | 115200 baud |
| PlatformIO environment | `esp32dev` |

The wiring and I2C address must be verified against the specific sensor breakout being used before uploading firmware.

## Build and Run

### Prerequisites

- Visual Studio Code
- PlatformIO IDE extension
- USB data cable compatible with the ESP32
- ESP32 development board
- SHT31 temperature and humidity sensor

### PlatformIO Workflow

1. Clone or download the repository.
2. Open the repository folder in Visual Studio Code.
3. Allow PlatformIO to install the platform and library dependencies defined in `platformio.ini`.
4. Connect the ESP32 to the computer using a USB data cable.
5. Build the `esp32dev` environment.
6. Upload the firmware to the ESP32.
7. Open the Serial Monitor at 115200 baud.
8. Verify that the SHT31 initializes and begins reporting live readings.

### Command-Line Workflow

```powershell
pio run
pio run --target upload
pio device monitor --baud 115200
```

The command-line workflow requires the PlatformIO Core command-line tools to be available in the terminal environment.

## Simulated Data

The current firmware uses placeholder values for portions of the developing data model:

- Vibration level
- Airflow reading
- Overall system status

These placeholders allow the program structure, serial output, and `HVACReading` data structure to be developed before the corresponding sensors and decision algorithms are integrated.

## Planned Features

- Physical vibration-sensor integration.
- Airflow-sensing implementation.
- Configurable warning and danger thresholds.
- Automatic normal, warning, and danger classification.
- Real-time OLED measurements and system status.
- Green, yellow, and red LED status indicators.
- Audible alerts using an active buzzer.
- Local data logging.
- Improved power delivery and physical installation.
- Protective enclosure design.
- Long-term HVAC condition testing.
