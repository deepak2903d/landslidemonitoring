#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <MPU6050.h>  // Include the MPU6050 library

// SoftwareSerial for Bluetooth module
SoftwareSerial BTSerial(10, 11); // RX, TX

// Initialize the LiquidCrystal_I2C library with the I2C address and 16x2 dimensions
LiquidCrystal_I2C lcd(0x27, 16, 2);

MPU6050 mpu;  // Create MPU6050 object

const int soilMoisturePin = A0; // Pin for soil moisture sensor
const int rainSensorPin = A1; // Pin for rain sensor
const int buzzerPin = 9; // Pin for buzzer

int soilMoistureValue = 0; // Variable to store moisture level
int rainSensorValue = 0; // Variable to store rain sensor value
const int moistureThreshold = 500; // Set a threshold for dryness
const int rainThreshold = 300; // Set a threshold for rain detection

void setup() {
    Serial.begin(9600); // Open serial port for debugging
    BTSerial.begin(9600); // Open Bluetooth serial port
    pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
    
    lcd.begin(); // Initialize the LCD
    lcd.backlight(); // Turn on the backlight
    lcd.setCursor(0, 0); // Set the cursor to the first row, first column
    lcd.print("Soil & Rain Monitor");

    // Initialize MPU6050
    Wire.begin();
    mpu.initialize();
    if (mpu.testConnection()) {
        Serial.println("MPU6050 connected successfully");
    } else {
        Serial.println("MPU6050 connection failed");
    }
}

void loop() {
    // Read soil moisture level
    soilMoistureValue = analogRead(soilMoisturePin);

    // Read rain sensor value
    rainSensorValue = analogRead(rainSensorPin);

    // Read accelerometer values from MPU6050
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);

    // Print values for debugging in Serial Monitor
    Serial.print("Soil Moisture Level: ");
    Serial.println(soilMoistureValue);
    Serial.print("Rain Sensor Value: ");
    Serial.println(rainSensorValue);
    Serial.print("Accel X: ");
    Serial.println(ax);
    Serial.print("Accel Y: ");
    Serial.println(ay);
    Serial.print("Accel Z: ");
    Serial.println(az);

    // Send values via Bluetooth
    BTSerial.print("Soil Moisture Level: ");
    BTSerial.println(soilMoistureValue);
    BTSerial.print("Rain Sensor Value: ");
    BTSerial.println(rainSensorValue);
    BTSerial.print("Accel X: ");
    BTSerial.println(ax);
    BTSerial.print("Accel Y: ");
    BTSerial.println(ay);
    BTSerial.print("Accel Z: ");
    BTSerial.println(az);

    // Update LCD with sensor values
    lcd.setCursor(0, 1); // Move cursor to the second row
    lcd.print("Soil: ");
    lcd.print(soilMoistureValue);
    lcd.print(" Rain: ");
    lcd.print(rainSensorValue);

    // Check if the soil moisture level is below the threshold
    if (soilMoistureValue < moistureThreshold) {
        lcd.setCursor(0, 1); // Move cursor to the second row
        lcd.print("Alert: SO WET "); // Display alert on LCD
        tone(buzzerPin, 1000); // Sound buzzer at 1 kHz
        BTSerial.println("Alert: Soil Moisture is HIGH!"); // Send alert via Bluetooth
        delay(5000); // Wait 5 seconds before checking again
    } else {
        lcd.setCursor(0, 1); // Move cursor to the second row
        lcd.print("Soil Moisture OK "); // Display normal status on LCD
        noTone(buzzerPin); // Stop buzzer
    }

    // Check if rain is detected
    if (rainSensorValue < rainThreshold) {
        lcd.setCursor(0, 1);
        lcd.print("Alert: Rain Detected! ");
        tone(buzzerPin, 500); // Sound buzzer at 500 Hz
        BTSerial.println("Alert: Rain Detected!"); // Send alert via Bluetooth
        delay(5000); // Wait 5 seconds before checking again
    } else {
        lcd.setCursor(0, 1); // Update display if no rain
        lcd.print("No Rain           ");
        noTone(buzzerPin); // Stop buzzer if no rain
    }

    delay(1000); // Delay for a second before next reading
}