 🌍 Landslide Monitoring System using Bluetooth via mobile 

This project is a Landslide Monitoring System that uses an MPU6050 sensor, soil moisture sensor, and rain sensor to detect environmental conditions that may lead to a landslide. The collected data is displayed on an LCD screen and transmitted to a *mobile device via Bluetooth. An alert system using a buzzer and Bluetooth messages is also integrated for real-time warnings.

 📸 Project Overview

*Monitors soil moisture, rainfall, and ground movement
* Detects potential landslide indicators
* Sends live data to a mobile phone via Bluetooth
* Displays data on a 16x2 LCD
* Triggers buzzer and alerts on abnormal readings

🧰 Components Used

| Component                 | Description                        |
| ------------------------- | ---------------------------------- |
| Arduino Uno               | Microcontroller Board              |
| MPU6050                   | Accelerometer and Gyroscope sensor |
| Soil Moisture Sensor      | To detect soil wetness             |
| Rain Sensor               | To detect rain presence            |
| HC-05 Bluetooth           | Bluetooth Module for communication |
| 16x2 I2C LCD              | Display unit                       |
| Buzzer                    | Sound alert                        |
| Jumper Wires & Breadboard | For connections                    |

🔧 How It Works
1. Soil Moisture Sensor reads the wetness of the soil.
2. Rain Sensor detects the presence of rainfall.
3. MPU6050 detects ground movement via acceleration values.
4. LCD displays real-time sensor data.
5. Bletooth (HC-05)sends data to mobile app or serial terminal.
6. If soil is too wet or rainfall is detected:

   * LCD shows a warning.
   * Buzzer sounds.
   * Bluetooth sends alert to connected mobile.
 
 💻 Code Features

* Reads analog sensor data using `analogRead()`
* Uses `LiquidCrystal_I2C` for efficient LCD display
* Utilizes `SoftwareSerial` for Bluetooth communication
* Handles MPU6050 readings via I2C
* Implements thresholds for alert conditions

📱 Mobile Connection

You can connect this system to your **Android mobile** using apps like:

* Serial Bluetooth Terminal
* Arduino Bluetooth Controller

Once paired with the HC-05 module (default password: `1234`), you will start receiving real-time data and alerts on your mobile screen

 📦 Installation

1. Connect all hardware components as per the circuit.
2. Upload the Arduino sketch to your Arduino board.
3. Open Serial Monitor or connect to your mobile app via Bluetooth.
4. Monitor sensor values and receive alerts.

🔍 Future Improvements

* Add GPS for location tracking.
* Integrate with cloud for remote monitoring.
* Use SMS or IoT modules for long-range alerting.

 📄 License

This project is open-source and free to use under the [MIT License](LICENSE).
