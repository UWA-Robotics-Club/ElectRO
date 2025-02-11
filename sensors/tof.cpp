#include "tof.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void initializeTofSensor(){
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
}