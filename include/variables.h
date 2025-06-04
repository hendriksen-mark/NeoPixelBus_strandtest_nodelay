#pragma once
#include "Arduino.h"
#include "declarations.h"
#include "user_info.h"

// Variable declarations
extern int StartShow;
extern NeoPixelBus<COLOR_ORDER, LED_TYPE>* pixels;
extern unsigned long pixelsInterval;
extern unsigned long ShowInterval;
extern unsigned long effectPreviousMillis;
extern unsigned long ShowPreviousMillis;
extern int theaterChaseQ;
extern int theaterChaseRainbowQ;
extern int theaterChaseRainbowCycles;
extern int rainbowCycles;
extern int rainbowCycleCycles;
extern int currentShow;
extern int brightness;
extern uint16_t currentPixel;
extern uint8_t colorIndex;
extern uint8_t power;
extern uint8_t autoplay;
extern float color[3];
extern RgbColor Red;
extern RgbColor Green;
extern RgbColor Blue;
extern RgbColor White;
extern RgbColor Black;
extern RgbColor OrangeRed;
extern RgbColor Orange;
extern RgbColor Goldenrod;
extern RgbColor Yellow;
extern RgbColor Lime;
extern RgbColor Aqua;
extern RgbColor Teal;
extern RgbColor Navy;
extern RgbColor RoyalBlue;
extern RgbColor Purple;
extern RgbColor Indigo;
extern RgbColor Magenta;
extern RgbColor Pink;
extern RgbColor LightPink;
extern RgbColor CornflowerBlue;
extern RgbColor LightBlue;
extern RgbColor currentColor;
