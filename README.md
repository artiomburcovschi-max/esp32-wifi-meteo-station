# esp32-wifi-meteo-station
My ESP32 weather station with a BME280 sensor, a 1.3" OLED screen, and Wi-Fi data output to my phone via Blynk IoT.
# ESP32 Dual-Network Weather Station (OLED 1.3" + Blynk IoT)

An autonomous smart weather station built with ESP32 that measures temperature, humidity, and atmospheric pressure. It displays data on a local 1.3" OLED screen and simultaneously streams it to a smartphone via Wi-Fi using the Blynk IoT platform.

## Features
- **Dual Wi-Fi Network Support**: Automatically switches to a backup Wi-Fi network if the primary router goes offline or losing signal.
- **Hardware Isolation**: The OLED display and BME280 sensor are separated onto two independent hardware I2C buses (`Wire` and `TwoWire`) to prevent signal noise and system freezes.
- **Dynamic Blynk UI Styling**: Automatically changes the temperature widget color in the mobile app depending on current climate conditions (Blue for cold, Green for optimal, Red for hot).
- **Standalone Mode**: Can easily work without Blynk. Just comment out the Blynk lines as mentioned in the source code comments.

## Hardware Configuration
- **Microcontroller**: ESP32 Dev Module
- **Sensor**: BME280 (I2C)
- **Display**: 1.3" OLED on SH1106 chip (I2C)

### Pinout Diagram
- **BME280 Sensor:** VCC -> 3.3V | GND -> GND | SDA -> G21 | SCL -> G22
- **1.3" OLED (SH1106):** VCC -> 5V (VIN) | GND -> GND | SDA -> G16 | SCK -> G17

## How to Setup and Flash !!!!!!

If you are new to ESP32 and Arduino IDE, follow these steps to get everything working:

### 1. Install Arduino IDE
- Download and install the latest version of **Arduino IDE** from the official website.

### 2. Install ESP32 Board Support
By default, Arduino IDE only supports original Arduino boards. To add ESP32 support:
1. Open Arduino IDE, go to **File** -> **Preferences**.
2. In the "Additional boards manager URLs" field, paste this link:
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Go to **Tools** -> **Board** -> **Boards Manager...**, search for **esp32** (by Espressif Systems), and click **Install**.

### 3. Install Drivers (Fixing the COM Port Issue)
If you connect your ESP32 to the PC via USB and cannot see the COM port (e.g., COM3, COM4) in the Tools menu, your computer lacks the USB-to-UART bridge driver. 
Look at the tiny square chip near the USB port on your ESP32 board and download the corresponding driver:
- **CP2102 / CP2104 chip**: Download and install the **Silicon Labs CP210x Driver**.
- **CH340 / CH341 chip**: Download and install the **WCH CH340 Driver**.

### 4. Flash the Code
1. Open the `.ino` file in Arduino IDE.
2. Select your board: **Tools** -> **Board** -> **esp32** -> **ESP32 Dev Module** (or your specific model).
3. Select the correct port: **Tools** -> **Port**.
4. Set the upload speed to **115200** or **921600**.
5. Fill in your Wi-Fi credentials and Blynk token in the code, then click the **Upload** button (the arrow icon).

## Software Dependencies
Make sure you have installed the following libraries in your Arduino IDE before uploading:
- `Wire`
- `Adafruit_GFX`
- `Adafruit_SH110X`
- `Adafruit_BME280`
- `Blynk` (by Volodymyr Shymanskyy)

## License
This project is licensed under the MIT License - feel free to use, modify, and distribute!
