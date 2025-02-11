#include <SPI.h>
#include <ArduinoJson.h>

#include "sonar.h"
#include "rc.h"
#include "gyro.h"
#include "tof.h"
#include "display.h"
#include "i2c_config.h"
#include "websocket_config.h"

void setup()
{
  Serial.begin(115200);

  initWebsocket();

  initializeWire();

  initializeDisplay();

  initializeMpu6050();

  initializeTofSensor();

  initializeControllerPins();

  doSplashScreen();
}

void loop()
{
  webSocket.loop();

  String jsonData = getSensorDataAsJson();
  webSocket.sendTXT(jsonData);

  displayTofSensorData();

  displaySonarSensorData();

  displayMpuSensorData();

  displayControllerData();

  displayAndDelay(300);
}

String getSensorDataAsJson() {
  // Create a JSON document
  StaticJsonDocument<256> jsonDoc;

  // ToF Sensor
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  jsonDoc["tof"] = (measure.RangeStatus != 4) ? measure.RangeMilliMeter : -1;

  // Sonar Sensor
  jsonDoc["sonar"] = sonar.ping_cm();

  // Gyroscope and Accelerometer
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  JsonObject gyro = jsonDoc.createNestedObject("gyro");
  gyro["x"] = g.gyro.x;
  gyro["y"] = g.gyro.y;
  gyro["z"] = g.gyro.z;

  JsonObject accel = jsonDoc.createNestedObject("accel");
  accel["x"] = a.acceleration.x;
  accel["y"] = a.acceleration.y;
  accel["z"] = a.acceleration.z;

  // RC Channels
  RcChannelValues rcChannels = readChannels();
  JsonObject channels = jsonDoc.createNestedObject("channels");
  channels["ch1"] = rcChannels.ch1;
  channels["ch2"] = rcChannels.ch2;
  channels["ch3"] = rcChannels.ch3;
  channels["ch4"] = rcChannels.ch4;

  // Serialize the JSON document to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  return jsonString;
}

void displayAndDelay(int mils){
  display.display();
  Serial.println("-----------------------------------");
  delay(mils);
}

void displayTofSensorData(){
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  display.clearDisplay();
  display.setCursor(0,0);
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    display.print("ToF:");
    display.print(measure.RangeMilliMeter);
    display.print("mm ");

    Serial.print("ToF:");
    Serial.print(measure.RangeMilliMeter);
    Serial.println("mm");
  } else {
    display.println("Out of Range");
    display.display();
    return;
  }
}

void displaySonarSensorData(){
  int cm_dist = sonar.ping_cm();
  display.print("Ping: ");
  display.print(cm_dist);
  display.println("cm");

  Serial.print("Ping: ");
  Serial.print(cm_dist);
  Serial.println("cm");
}

void displayMpuSensorData(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Gyroscope ");
  Serial.print("X: ");
  Serial.print(g.gyro.x, 1);
  Serial.print(" rps, ");
  Serial.print("Y: ");
  Serial.print(g.gyro.y, 1);
  Serial.print(" rps, ");
  Serial.print("Z: ");
  Serial.print(g.gyro.z, 1);
  Serial.println(" rps");

  Serial.print("Accelerometer ");
  Serial.print("X: ");
  Serial.print(a.acceleration.x, 1);
  Serial.print(" m/s^2, ");
  Serial.print("Y: ");
  Serial.print(a.acceleration.y, 1);
  Serial.print(" m/s^2, ");
  Serial.print("Z: ");
  Serial.print(a.acceleration.z, 1);
  Serial.println(" m/s^2");

  display.print(g.gyro.x, 1);
  display.print(", ");
  display.print(g.gyro.y, 1);
  display.print(", ");
  display.print(g.gyro.z, 1);
  display.println("");

  display.print(a.acceleration.x, 1);
  display.print(", ");
  display.print(a.acceleration.y, 1);
  display.print(", ");
  display.print(a.acceleration.z, 1);
  display.println("");
}

void displayControllerData() {
  RcChannelValues rcChannels = readChannels();

  // Print to Serial Monitor
  Serial.print("Ch1: ");
  Serial.print(rcChannels.ch1);
  Serial.print(" | Ch2: ");
  Serial.print(rcChannels.ch2);
  Serial.print(" | Ch3: ");
  Serial.print(rcChannels.ch3);
  Serial.print(" | Ch4: ");
  Serial.println(rcChannels.ch4);

  // Memory intensive because of the overhead, currently not an issue with big memory boards
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%4d|%4d|%4d|%4d", rcChannels.ch1, rcChannels.ch2, rcChannels.ch3, rcChannels.ch4);
  display.println(buffer);

  // // CPU intensive because of the loop
  // printPadded(rcChannels.ch1, 4);
  // display.print("|");
  // printPadded(rcChannels.ch2, 4);
  // display.print("|");
  // printPadded(rcChannels.ch3, 4);
  // display.print("|");
  // printPadded(rcChannels.ch4, 4);
}

void printPadded(int value, int width) {
  int padding = width - String(value).length();
  for (int i = 0; i < padding; i++) {
    display.print(" ");
  }
  display.print(value);
}
