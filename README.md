# ESP32 HVAC Health Monitoring System

An embedded-system prototype designed to monitor HVAC operating conditions using temperature, humidity, and vibration sensing.

The system uses an ESP32 to collect sensor data, evaluate operating conditions, and provide local status notifications through an OLED display, indicator LEDs, and an audible buzzer.

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
