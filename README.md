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
