#include "gyro.h"

Adafruit_MPU6050 mpu;

void initializeMpu6050(){
  if (!mpu.begin()) {
  Serial.println("Sensor init failed");
  while (1)
    yield();
  }
  Serial.println("Found a MPU-6050 sensor");
}
