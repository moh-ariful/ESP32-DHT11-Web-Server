# ESP32 PIR Sensor with Buzzer and LED Web Server

This project demonstrates how to use an ESP32 to create a web server that interfaces with a PIR sensor (model SR602), a buzzer, and an LED. When motion is detected by the PIR sensor, the buzzer sounds for 1 second and the LED blinks for 3 seconds. The web server displays a message indicating that an object has been detected.

## Components Used

- ESP32 Development Board
- PIR Sensor (model SR602)
- Buzzer
- LED
- Resistor (220 ohm or 330 ohm)
- Connecting wires
- Breadboard

## Circuit Diagram

1. **PIR Sensor**:
    - VCC: 3.3V
    - GND: GND
    - OUT: GPIO 33

2. **Buzzer**:
    - Positive (long leg): GPIO 27
    - Negative (short leg): GND

3. **LED**:
    - Anode (long leg): GPIO 25 (through a 220 ohm or 330 ohm resistor)
    - Cathode (short leg): GND

## Installation

1. Clone the repository:

2. Install the required libraries in your Arduino IDE:
    - WiFi
    - WiFiManager

3. Open the `PIR_602_Buzzer_LED.ino` file in your Arduino IDE.

4. Upload the code to your ESP32 board.

## Code Overview

The provided code sets up a web server on the ESP32 that detects motion using a PIR sensor and responds by activating a buzzer and an LED. The web server displays a message when motion is detected.

### Key Functions

- **setup()**: Initializes serial communication, sets pin modes, connects to WiFi using WiFiManager, and starts the web server.
- **loop()**: Checks for motion detected by the PIR sensor and handles the buzzer and LED activation. Manages client connections to the web server and updates the web page.

### Web Server

The web server serves a simple HTML page that refreshes every 5 seconds and displays a message when motion is detected.

## Usage

1. Connect the components as described in the circuit diagram.
2. Power on the ESP32.
3. Connect to the WiFi network created by the ESP32 (default SSID: `ESP32_AP`).
4. Open a web browser and navigate to the IP address displayed in the serial monitor.
5. The web page will display a message when motion is detected by the PIR sensor.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Feel free to submit issues and enhancement requests.

## Acknowledgments

- This project was created using the [Arduino IDE](https://www.arduino.cc/en/Main/Software).
- Special thanks to [Next Koding Enterprise](http://nextkoding.com) for providing resources and inspiration.

