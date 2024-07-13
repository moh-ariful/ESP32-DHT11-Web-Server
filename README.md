# ESP32-DHT11-Web-Server

This project demonstrates how to create a web server using an ESP32 microcontroller to monitor temperature and humidity in real-time. The data is gathered from a DHT11 sensor and displayed on a web page using Chart.js for graphical representation. The project also includes WiFiManager for easy configuration of WiFi settings.

## Features
- **Real-time Monitoring**: Continuously reads temperature and humidity from a DHT11 sensor.
- **Web Server**: Hosts a web page on the ESP32 to display sensor data.
- **Graphical Display**: Utilizes Chart.js to create real-time graphs of temperature data.
- **WiFi Configuration**: Easy WiFi setup using WiFiManager library.
- **Alerts**: Displays a warning on the web page if the temperature exceeds a defined threshold.

## Components Used
- **ESP32**
- **DHT11 Temperature and Humidity Sensor**
- **WiFiManager Library**
- **Chart.js for Graphing**

## How to Use
1. **Setup Hardware**: Connect the DHT11 sensor to pin 33 of the ESP32.
2. **Upload Code**: Upload the provided Arduino code to the ESP32.
3. **WiFi Setup**: On first run, connect to the ESP32 access point and configure your WiFi settings.
4. **Access Web Server**: Open a web browser and navigate to the ESP32's IP address to view the temperature and humidity data.
