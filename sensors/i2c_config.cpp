#include "i2c_config.h"

void initializeWire() {
  Wire.begin(SDA_PIN, SCL_PIN);
}