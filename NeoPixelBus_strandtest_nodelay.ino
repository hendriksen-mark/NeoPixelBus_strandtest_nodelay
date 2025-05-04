#include <NeoPixelBus.h>

#define PIXELSPIN   6
#define NUMPIXELS   8
int StartShow = 0;
int EndShow = 10;

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>* pixels = NULL;

unsigned long pixelsInterval = 50; // the time we need to wait
unsigned long ShowInterval = 60000; // show time in millis
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

uint16_t currentPixel = 0;// what pixel are we operating on

float color[3];
RgbColor red = RgbColor(255, 0, 0);
RgbColor green = RgbColor(0, 255, 0);
RgbColor blue = RgbColor(0, 0, 255);
RgbColor white = RgbColor(255);
RgbColor black = RgbColor(0);

void setup() {
	Serial.begin(115200);
	pixels = new NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>(NUMPIXELS, PIXELSPIN);
	currentPixel = 0;
	Showcount = StartShow;

	pixels->Begin(); // This initializes the NeoPixel library.
	for (int i = 0; i < NUMPIXELS; i++) {
		pixels->SetPixelColor(i, black);
	}
	pixels->Show(); // This sends the updated pixel color to the hardware.
	Serial.println("Showcount = " + String(Showcount));

}

void loop () {
	if ((unsigned long)(millis() - ShowPreviousMillis) >= ShowInterval) {
		ShowPreviousMillis = millis();
		Showcount++;
		Serial.println("Showcount = " + String(Showcount));
		if (Showcount > EndShow || Showcount < StartShow) {
			Showcount = StartShow;
		}
	}

	switch (Showcount) {
		case 0:
			if ((unsigned long)(millis() - colorWipePreviousMillis) >= pixelsInterval) {
				colorWipePreviousMillis = millis();
				colorWipe(red);
			}
			break;
		case 1:
			if ((unsigned long)(millis() - colorWipePreviousMillis) >= pixelsInterval) {
				colorWipePreviousMillis = millis();
				colorWipe(green);
			}
			break;
		case 2:
			if ((unsigned long)(millis() - colorWipePreviousMillis) >= pixelsInterval) {
				colorWipePreviousMillis = millis();
				colorWipe(blue);
			}
			break;
		case 3:
			if ((unsigned long)(millis() - colorWipePreviousMillis) >= pixelsInterval) {
				colorWipePreviousMillis = millis();
				colorWipe(white);
			}
			break;
		case 4:
			if ((unsigned long)(millis() - theaterChasePreviousMillis) >= pixelsInterval) {
				theaterChasePreviousMillis = millis();
				theaterChase(red); // Red
			}
			break;
		case 5:
			if ((unsigned long)(millis() - theaterChasePreviousMillis) >= pixelsInterval) {
				theaterChasePreviousMillis = millis();
				theaterChase(green); // Green
			}
			break;
		case 6:
			if ((unsigned long)(millis() - theaterChasePreviousMillis) >= pixelsInterval) {
				theaterChasePreviousMillis = millis();
				theaterChase(blue); // Blue
			}
			break;
		case 7:
			if ((unsigned long)(millis() - theaterChasePreviousMillis) >= pixelsInterval) {
				theaterChasePreviousMillis = millis();
				theaterChase(white); // White
			}
			break;
		case 8:
			if ((unsigned long)(millis() - theaterChaseRainbowPreviousMillis) >= pixelsInterval) {
				theaterChaseRainbowPreviousMillis = millis();
				theaterChaseRainbow();
			}
			break;
		case 9:
			if ((unsigned long)(millis() - rainbowPreviousMillis) >= pixelsInterval) {
				rainbowPreviousMillis = millis();
				rainbow();
			}
			break;
		case 10:
			if ((unsigned long)(millis() - rainbowCyclesPreviousMillis) >= pixelsInterval) {
				rainbowCyclesPreviousMillis = millis();
				rainbowCycle();
			}

	}
}

// Fill the dots one after the other with a color
void colorWipe(RgbColor c) {
	pixels->SetPixelColor(currentPixel, c);
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
void theaterChase(RgbColor c) {
	for (int i = 0; i < NUMPIXELS; i = i + 3) {
		pixels->SetPixelColor(i + theaterChaseQ, c);  //turn every third pixel on
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
		pixels->SetPixelColor(i + theaterChaseRainbowQ, Wheel( (i + theaterChaseRainbowCycles) % 255)); //turn every third pixel on
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
	for (int i = 0; i, 3; i++) {
		WheelPos = 255 - WheelPos;
		if (WheelPos < 85) {
			color[0] = 255 - WheelPos * 3;
			color[1] = 0;
			color[2] = WheelPos * 3;
			return RgbColor((uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2]);
		}
		if (WheelPos < 170) {
			WheelPos -= 85;
			color[0] = 0;
			color[1] = WheelPos * 3;
			color[2] = 255 - WheelPos * 3;
			return RgbColor((uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2]);
		}
		WheelPos -= 170;
		color[0] = WheelPos * 3;
		color[1] = 255 - WheelPos * 3;
		color[2] = 0;
		return RgbColor((uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2]);
	}
}
