#include "display.h"

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

void initializeDisplay(){
  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
}

void displayLogo(){
  display.clearDisplay();
  display.drawBitmap(0, 0, urc_logo_bitmap, 128, 32, WHITE);
  display.display();
}

void setDefaultTextSize(){
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void doSplashScreen(){
  displayLogo();
  delay(1000);
  setDefaultTextSize();
}