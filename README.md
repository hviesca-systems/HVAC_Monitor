# ESP32 HVAC Health Monitoring System

An embedded-system prototype designed to monitor HVAC operating conditions using temperature, humidity, and vibration sensing.

The system uses an ESP32 to collect sensor data, evaluate operating conditions, and provide local status notifications through an OLED display, indicator LEDs, and an audible buzzer.

## Project Status

**Active development**

The current prototype successfully reads environmental and vibration data, classifies the system condition, and produces local visual and audible alerts. Future development will focus on improving physical installation, power delivery, data collection, enclosure design, and long-term testing.

## Project Objectives

- Monitor HVAC temperature and humidity conditions.
- Detect abnormal vibration that may indicate mechanical problems.
- Classify operating conditions as normal, warning, or danger.
- Present system status locally without requiring an internet connection.
- Support hardware troubleshooting through dedicated diagnostic programs.
- Create a modular foundation for future data logging and long-term condition monitoring.

## Current Features

- ESP32-based sensor processing and system control.
- Temperature and humidity measurement using an SHT31 sensor.
- Analog vibration monitoring with configurable warning and danger thresholds.
- Real-time measurements and system status displayed on an I2C OLED.
- Green, yellow, and red LED status indication.
- Audible warning through an active buzzer.
- Automatic classification of normal, warning, and danger conditions.
- Dedicated I2C scanner for sensor and display diagnostics.
- PlatformIO-based firmware organization and dependency management.
