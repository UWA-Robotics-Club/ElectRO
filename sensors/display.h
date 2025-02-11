#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

#include <Wire.h>

#include "logo.h"

#if (SSD1306_LCDHEIGHT != 32)
 #error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define SCREEN_ADDRESS 0x3C

extern Adafruit_SSD1306 display;

void initializeDisplay();

void displayLogo();

void setDefaultTextSize();

void doSplashScreen();