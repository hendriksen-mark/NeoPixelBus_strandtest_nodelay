#include <Arduino.h>
#include <NeoPixelBus.h>
#include <DebugLog.h>
#include "variables.h"
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
IRrecv irReceiver(RECV_PIN);
#include "handleIrInput.h"

// Effect function pointer type
typedef void (*EffectFunc)();

// Array of effect functions (no wrappers needed)
EffectFunc effects[] = {
	colorWipe,
	theaterChase,
	theaterChaseRainbow,
	rainbow,
	rainbowCycle,
	twinkle,
	confetti,
	meteorRain,
	pulse,
	sparkle,
	letterHighlight
};

const uint8_t numEffects = sizeof(effects) / sizeof(effects[0]);

void setup() {
	Serial.begin(115200);
	LOG_SET_LEVEL(DebugLogLevel::LVL_TRACE);
#if defined(ESP8266)
	pixels = new NeoPixelBus<COLOR_ORDER, LED_TYPE>(NUMPIXELS);
#elif defined(ESP32)
	pixels = new NeoPixelBus<COLOR_ORDER, LED_TYPE>(NUMPIXELS, PIXELSPIN);
#endif
	currentPixel = 0;
	currentShow = StartShow;

	pixels->Begin(); // This initializes the NeoPixel library.
	for (int i = 0; i < NUMPIXELS; i++) {
		pixels->SetPixelColor(i, Black);
	}
	pixels->Show(); // This sends the updated pixel color to the hardware.
	irReceiver.enableIRIn(); // Start the receiver
}

void loop() {
	handleIrInput();
	if (power == 0) {
		pixels->ClearTo(Black);
		pixels->Show();
		return;
	}

	if (autoplay == 1) {
		if ((unsigned long)(millis() - ShowPreviousMillis) >= ShowInterval) {
			ShowPreviousMillis = millis();
			if (currentShow == 0 || currentShow == 1) {
				// Cycle through Red, Green, Blue, and White
				switch (colorIndex) {
				case 0:
					setColor(Red); // Red
					break;
				case 1:
					setColor(Green); // Green
					break;
				case 2:
					setColor(Blue); // Blue
					break;
				case 3:
					setColor(White); // White
					break;
				case 4:
					colorIndex = 0;
					setColor(Red); // Red
					adjustPattern(true);
					break;
				}

				colorIndex++;
			}
			else {
				colorIndex = 0;
				adjustPattern(true);
			}
		}
	}

	// Use a single timer for all effects
	if (currentShow >= 0 && currentShow < numEffects) {
		if ((unsigned long)(millis() - effectPreviousMillis) >= pixelsInterval) {
			effectPreviousMillis = millis();
			effects[currentShow]();
		}
	}
}

void setPattern(uint8_t value) {
	if (value > numEffects) value = numEffects;
	else if (value < StartShow) value = StartShow;

	LOG_DEBUG("setPattern:", value);
	currentShow = value;
}

void adjustPattern(bool up) {
	if (up)
		currentShow++;
	else
		currentShow--;

	// wrap around at the ends
	if (currentShow < StartShow)
		currentShow = numEffects;
	if (currentShow > numEffects)
		currentShow = StartShow;

	LOG_DEBUG("adjustPattern:", currentShow);
}

void adjustSpeed(bool up) {
	if (up)
		pixelsInterval--;
	else
		pixelsInterval++;

	// wrap around at the ends
	if (pixelsInterval < 0)
		pixelsInterval = 255;
	if (pixelsInterval > 255)
		pixelsInterval = 0;

	LOG_DEBUG("adjustSpeed:", pixelsInterval);
}

void setPower(uint8_t value) {
	power = value == 0 ? 0 : 1;

	LOG_DEBUG("setPower:", power);
}

void adjustBrightness(bool up) {
	if (up)
		brightness++;
	else
		brightness--;

	if (brightness < 0)
		brightness = 0;
	else if (brightness > 255)
		brightness = 255;

	LOG_DEBUG("adjustBrightness:", brightness);
}

void setBrightness(uint8_t value) {
	if (value > 255)
		value = 255;
	else if (value < 0) value = 0;

	brightness = value;
	LOG_DEBUG("setBrightness:", brightness);
}

void setAutoplay(uint8_t value) {
	autoplay = value;

	LOG_DEBUG("setAutoplay:", autoplay);
}

void setColor(RgbColor c) {
	// Scale the color components by brightness
	currentColor = RgbColor(
		(uint8_t)((c.R * brightness) / 255),
		(uint8_t)((c.G * brightness) / 255),
		(uint8_t)((c.B * brightness) / 255)
	);
	LOG_DEBUG("setColor:", currentColor.R, currentColor.G, currentColor.B);
}

// Fill the dots one after the other with a color
void colorWipe() {
	pixels->SetPixelColor(currentPixel, currentColor);
	pixels->Show();
	currentPixel++;
	if (currentPixel == NUMPIXELS) {
		currentPixel = 0;
	}
}

void rainbow() {
	for (uint16_t i = 0; i < NUMPIXELS; i++) {
		pixels->SetPixelColor(i, Wheel((i + rainbowCycles) & 255));
	}
	pixels->Show();
	rainbowCycles++;
	if (rainbowCycles >= 256) rainbowCycles = 0;
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle() {
	uint16_t i;

	//for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
	for (i = 0; i < NUMPIXELS; i++) {
		pixels->SetPixelColor(i, Wheel(((i * 256 / NUMPIXELS) + rainbowCycleCycles) & 255));
	}
	pixels->Show();

	rainbowCycleCycles++;
	if (rainbowCycleCycles >= 256 * 5) rainbowCycleCycles = 0;
}

//Theatre-style crawling lights.
void theaterChase() {
	for (int i = 0; i < NUMPIXELS; i = i + 3) {
		pixels->SetPixelColor(i + theaterChaseQ, currentColor);  //turn every third pixel on
	}
	pixels->Show();
	for (int i = 0; i < NUMPIXELS; i = i + 3) {
		pixels->SetPixelColor(i + theaterChaseQ, 0);      //turn every third pixel off
	}
	theaterChaseQ++;
	if (theaterChaseQ >= 3) theaterChaseQ = 0;
}


//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow() {
	for (int i = 0; i < NUMPIXELS; i = i + 3) {
		pixels->SetPixelColor(i + theaterChaseRainbowQ, Wheel((i + theaterChaseRainbowCycles) % 255)); //turn every third pixel on
	}

	pixels->Show();
	for (int i = 0; i < NUMPIXELS; i = i + 3) {
		pixels->SetPixelColor(i + theaterChaseRainbowQ, 0);      //turn every third pixel off
	}
	theaterChaseRainbowQ++;
	theaterChaseRainbowCycles++;
	if (theaterChaseRainbowQ >= 3) theaterChaseRainbowQ = 0;
	if (theaterChaseRainbowCycles >= 256) theaterChaseRainbowCycles = 0;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
RgbColor Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		color[0] = (255 - WheelPos * 3) * brightness / 255;
		color[1] = 0;
		color[2] = (WheelPos * 3) * brightness / 255;
		return RgbColor((uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2]);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		color[0] = 0;
		color[1] = (WheelPos * 3) * brightness / 255;
		color[2] = (255 - WheelPos * 3) * brightness / 255;
		return RgbColor((uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2]);
	}
	WheelPos -= 170;
	color[0] = (WheelPos * 3) * brightness / 255;
	color[1] = (255 - WheelPos * 3) * brightness / 255;
	color[2] = 0;
	return RgbColor((uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2]);
}

void twinkle() {
	for (int i = 0; i < NUMPIXELS; i++) {
		if (random(10) == 0) {
			pixels->SetPixelColor(i, currentColor);
		} else {
			pixels->SetPixelColor(i, Black);
		}
	}
	pixels->Show();
}

// Confetti effect: random colored speckles that blink and fade smoothly
void confetti() {
	// Fade all pixels slightly
	for (int i = 0; i < NUMPIXELS; i++) {
		RgbColor c = pixels->GetPixelColor(i);
		// Fade by 10/255 per frame
		uint8_t r = (uint8_t)((int)c.R * 245 / 255);
		uint8_t g = (uint8_t)((int)c.G * 245 / 255);
		uint8_t b = (uint8_t)((int)c.B * 245 / 255);
		pixels->SetPixelColor(i, RgbColor(r, g, b));
	}
	// Add a random colored pixel
	int pos = random(NUMPIXELS);
	uint8_t r = (uint8_t)random(0, brightness);
	uint8_t g = (uint8_t)random(0, brightness);
	uint8_t b = (uint8_t)random(0, brightness);
	pixels->SetPixelColor(pos, RgbColor(r, g, b));
	pixels->Show();
}

// Meteor Rain effect: a bright dot moves across the strip with fading tails
void meteorRain() {
	static int meteorPos = 0;
	static int meteorDir = 1; // 1 = forward, -1 = backward

	// Fade all pixels slightly
	for (int i = 0; i < NUMPIXELS; i++) {
		RgbColor c = pixels->GetPixelColor(i);
		uint8_t r = (uint8_t)((int)c.R * 200 / 255);
		uint8_t g = (uint8_t)((int)c.G * 200 / 255);
		uint8_t b = (uint8_t)((int)c.B * 200 / 255);
		pixels->SetPixelColor(i, RgbColor(r, g, b));
	}

	// Draw meteor
	pixels->SetPixelColor(meteorPos, currentColor);
	pixels->Show();

	// Move meteor
	meteorPos += meteorDir;
	if (meteorPos >= NUMPIXELS) {
		meteorPos = NUMPIXELS - 1;
		meteorDir = -1;
	} else if (meteorPos < 0) {
		meteorPos = 0;
		meteorDir = 1;
	}
}

// Pulse/Breathing effect: all LEDs fade in and out together
void pulse() {
	static int pulseValue = 0;
	static int pulseDirection = 1;
	pulseValue += pulseDirection * 5;
	if (pulseValue >= 255) {
		pulseValue = 255;
		pulseDirection = -1;
	} else if (pulseValue <= 0) {
		pulseValue = 0;
		pulseDirection = 1;
	}
	RgbColor c(
		(uint8_t)((currentColor.R * pulseValue) / 255),
		(uint8_t)((currentColor.G * pulseValue) / 255),
		(uint8_t)((currentColor.B * pulseValue) / 255)
	);
	for (int i = 0; i < NUMPIXELS; i++) {
		pixels->SetPixelColor(i, c);
	}
	pixels->Show();
}

// Sparkle effect: random LEDs flash white briefly
void sparkle() {
	static int sparkleTimer = 0;
	// Dim all LEDs slightly
	for (int i = 0; i < NUMPIXELS; i++) {
		RgbColor c = pixels->GetPixelColor(i);
		uint8_t r = (uint8_t)((int)c.R * 200 / 255);
		uint8_t g = (uint8_t)((int)c.G * 200 / 255);
		uint8_t b = (uint8_t)((int)c.B * 200 / 255);
		pixels->SetPixelColor(i, RgbColor(r, g, b));
	}
	// Occasionally flash a random LED white
	if (++sparkleTimer % 3 == 0) {
		int pos = random(NUMPIXELS);
		pixels->SetPixelColor(pos, White);
	}
	pixels->Show();
}

// Letter highlight effect: one LED at a time, then all, then off, repeat
void letterHighlight() {
	static int phase = 0; // 0: one-by-one, 1: all on, 2: all off
	static int idx = 0;
	static unsigned long lastChange = 0;
	const unsigned long stepDelay = 300; // ms per step

	if (millis() - lastChange < stepDelay) return;
	lastChange = millis();

	if (phase == 0) {
		// Light up one LED at a time
		pixels->ClearTo(Black);
		if (idx < NUMPIXELS) {
			pixels->SetPixelColor(idx, currentColor);
			idx++;
		} else {
			phase = 1;
			idx = 0;
		}
	} else if (phase == 1) {
		// All on
		pixels->ClearTo(currentColor);
		phase = 2;
	} else {
		// All off
		pixels->ClearTo(Black);
		phase = 0;
		idx = 0;
	}
	pixels->Show();
}
