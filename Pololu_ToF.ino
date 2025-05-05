#include <Wire.h>
#include "VL53L0X.h" // Include the VL53L0X library you provided

// Define VL53L0X sensor objects
VL53L0X sensor1;
VL53L0X sensor2;
VL53L0X sensor3;

// Define shutdown pins for each sensor
const int shdnPin1 = 2;
const int shdnPin2 = 3;
const int shdnPin3 = 4;

// Define I2C addresses for each sensor
const uint8_t sensor1Address = 0x30; // You can choose any valid 7-bit I2C address
const uint8_t sensor2Address = 0x31;
const uint8_t sensor3Address = 0x32;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Initialize I2C bus

  // Initialize sensors
  initializeSensor(sensor1, shdnPin1, sensor1Address);
  initializeSensor(sensor2, shdnPin2, sensor2Address);
  initializeSensor(sensor3, shdnPin3, sensor3Address);

  Serial.println("Three VL53L0X sensors initialized");
}

void loop() {
  // Read range from each sensor
  uint16_t range1 = sensor1.readRangeSingleMillimeters();
  uint16_t range2 = sensor2.readRangeSingleMillimeters();
  uint16_t range3 = sensor3.readRangeSingleMillimeters();

  // Print the results
  Serial.print("Sensor 1: ");
  if (sensor1.timeoutOccurred()) {
    Serial.print("Timeout");
  } else {
    Serial.print(range1);
    Serial.print(" mm");
  }

  Serial.print("  |  Sensor 2: ");
  if (sensor2.timeoutOccurred()) {
    Serial.print("Timeout");
  } else {
    Serial.print(range2);
    Serial.print(" mm");
  }

  Serial.print("  |  Sensor 3: ");
  if (sensor3.timeoutOccurred()) {
    Serial.print("Timeout");
  } else {
    Serial.print(range3);
    Serial.print(" mm");
  }

  Serial.println();

  delay(100); // Small delay for readability
}

void initializeSensor(VL53L0X &sensor, int shdnPin, uint8_t newAddress) {
  // Enable the sensor by setting the SHDN pin high
  pinMode(shdnPin, OUTPUT);
  digitalWrite(shdnPin, LOW);  // Keep it low for reset
  delay(10);
  digitalWrite(shdnPin, HIGH); // Enable the sensor
  delay(10);

  // Initialize the sensor and set a new address
  sensor.setBus(&Wire); // Give the sensor the Wire object to use
  if (!sensor.init()) {
    Serial.print("Failed to initialize sensor on pin ");
    Serial.println(shdnPin);
    while (1); // Stop execution if initialization fails
  }
  sensor.setAddress(newAddress);
  delay(10); // Address change takes time
}