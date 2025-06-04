#pragma once
#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "Arduino.h"
#include <NeoPixelBus.h>

// Variable declarations
extern int StartShow;
extern const uint8_t numEffects;
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
extern uint8_t power;
extern uint8_t autoplay;
extern float color[3];
extern RgbColor currentColor;
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

// Function declarations
// Effects
void colorWipe();
void rainbow();
void rainbowCycle();
void theaterChase();
void theaterChaseRainbow();
void twinkle();
void confetti();
void meteorRain();
void pulse();
void sparkle();
void letterHighlight();
// Effects helpers
void handleIrInput();
RgbColor Wheel(byte);
void setPattern(uint8_t);
void adjustPattern(bool);
void adjustSpeed(bool);
void adjustBrightness(bool);
void setPower(uint8_t);
void setAutoplay(uint8_t);
void setBrightness(uint8_t);
void setColor(RgbColor);

#endif // DECLARATIONS_H
