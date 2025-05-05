#pragma once
#include "Arduino.h"
#include "declarations.h"
#include "user_info.h"

// Variable definitions
int StartShow = 0;
int EndShow = 5;
NeoPixelBus<COLOR_ORDER, LED_TYPE>* pixels = NULL;
long pixelsInterval = 50;
unsigned long ShowInterval = 6000;
unsigned long colorWipePreviousMillis = 0;
unsigned long theaterChasePreviousMillis = 0;
unsigned long theaterChaseRainbowPreviousMillis = 0;
unsigned long rainbowPreviousMillis = 0;
unsigned long rainbowCyclesPreviousMillis = 0;
unsigned long ShowPreviousMillis = 0;
int theaterChaseQ = 0;
int theaterChaseRainbowQ = 0;
int theaterChaseRainbowCycles = 0;
int rainbowCycles = 0;
int rainbowCycleCycles = 0;
int Showcount = 0;
int brightness = 255;
uint16_t currentPixel = 0;
uint8_t colorIndex = 0;
uint8_t power = 1;
uint8_t autoplay = 1;
float color[3];
RgbColor Red = RgbColor(255, 0, 0);
RgbColor Green = RgbColor(0, 255, 0);
RgbColor Blue = RgbColor(0, 0, 255);
RgbColor White = RgbColor(255);
RgbColor Black = RgbColor(0);
RgbColor OrangeRed = RgbColor(255, 69, 0);
RgbColor Orange = RgbColor(255, 165, 0);
RgbColor Goldenrod = RgbColor(218, 165, 32);
RgbColor Yellow = RgbColor(255, 255, 0);
RgbColor Lime = RgbColor(50, 205, 50);
RgbColor Aqua = RgbColor(0, 255, 255);
RgbColor Teal = RgbColor(0, 128, 128);
RgbColor Navy = RgbColor(0, 0, 128);
RgbColor RoyalBlue = RgbColor(65, 105, 225);
RgbColor Purple = RgbColor(128, 0, 128);
RgbColor Indigo = RgbColor(75, 0, 130);
RgbColor Magenta = RgbColor(255, 0, 255);
RgbColor Pink = RgbColor(255, 192, 203);
RgbColor LightPink = RgbColor(255, 182, 193);
RgbColor CornflowerBlue = RgbColor(100, 149, 237);
RgbColor LightBlue = RgbColor(173, 216, 230);
RgbColor currentColor = Red;
