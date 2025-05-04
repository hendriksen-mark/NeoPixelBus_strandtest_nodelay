#pragma once
const bool apMode = false;

// AP mode password
const char WiFiAPPSK[] = "";

// Wi-Fi network to connect to (if not in AP mode)
const char* ssid = "";
const char* password = "";

#define LED_TYPE      Neo800KbpsMethod
#define COLOR_ORDER   NeoGrbFeature
#define NUMPIXELS      5

#if defined(ESP8266)
	#define PIXELSPIN 13 // pin for led strip
	#define RECV_PIN 2  // pin for ir rec
#elif defined(ESP32)
	#define PIXELSPIN 18 //  pin for led strip
	#define RECV_PIN 5  // pin for ir rec
#endif

// uncomment to enable IRremote
#define IR_enable

// ten seconds per color palette makes a good demo
// 20-120 is better for deployment
uint8_t secondsPerPalette = 10;
