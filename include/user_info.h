#pragma once
#include "Arduino.h"

const bool apMode = false;

// AP mode password
const char WiFiAPPSK[] = "";

// Wi-Fi network to connect to (if not in AP mode)
const char* ssid = "";
const char* password = "";

#define COLOR_ORDER   NeoGrbFeature
#define NUMPIXELS      5

#if defined(ESP8266)
#define LED_TYPE	Neo800KbpsMethod
#define RECV_PIN	2  // pin for ir rec
#elif defined(ESP32)
#define LED_TYPE	NeoEsp32Rmt0Ws2812xMethod
#define PIXELSPIN	18 //  pin for led strip
#define RECV_PIN	5  // pin for ir rec
#endif

// ten seconds per color palette makes a good demo
// 20-120 is better for deployment
uint8_t secondsPerPalette = 10;
