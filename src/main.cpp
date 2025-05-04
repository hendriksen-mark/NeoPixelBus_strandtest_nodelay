#include <Arduino.h>
#include <NeoPixelBus.h>
#include <DebugLog.h>
#include "variables.h"

#if defined(IR_enable)
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
IRrecv irReceiver(RECV_PIN);
#include "Commands.h"
#endif

#if defined(IR_enable)
void handleIrInput()
{
	InputCommand command = readCommand(defaultHoldDelay);

	if (command != InputCommand::None) {
		LOG_DEBUG("command:", (int)command);
	}

	switch (command) {
	case InputCommand::RedUp:
	case InputCommand::GreenUp:
	case InputCommand::BlueUp:
	case InputCommand::RedDown:
	case InputCommand::GreenDown:
	case InputCommand::BlueDown:
	case InputCommand::None: {
		break;
	}
	case InputCommand::Palette: {
		setPattern(random(EndShow));
		break;
	}
	case InputCommand::Up: {
		adjustPattern(true);
		break;
	}
	case InputCommand::Down: {
		adjustPattern(false);
		break;
	}
	case InputCommand::Left: {
		adjustSpeed(false);
		break;
	}
	case InputCommand::Right: {
		adjustSpeed(true);
		break;
	}
	case InputCommand::Power: {
		setPower(power == 0 ? 1 : 0);
		break;
	}
	case InputCommand::PowerOn: {
		setPower(1);
		break;
	}
	case InputCommand::PowerOff: {
		setPower(0);
		break;
	}
	case InputCommand::BrightnessUp: {
		adjustBrightness(true);
		break;
	}
	case InputCommand::BrightnessDown: {
		adjustBrightness(false);
		break;
	}
	case InputCommand::Brightness: {
		adjustBrightness(true);
		break;
	}
	case InputCommand::Select: {
		setBrightness(random(255));
		break;
	}
	case InputCommand::PlayMode: {  //toggle pause/play
		setAutoplay(!autoplay);
		break;
	}

							   //pattern buttons

	case InputCommand::Pattern1: {
		setPattern(0);
		break;
	}
	case InputCommand::Pattern2: {
		setPattern(1);
		break;
	}
	case InputCommand::Pattern3: {
		setPattern(2);
		break;
	}
	case InputCommand::Pattern4: {
		setPattern(3);
		break;
	}
	case InputCommand::Pattern5: {
		setPattern(4);
		break;
	}
	case InputCommand::Pattern6: {
		setPattern(5);
		break;
	}
	case InputCommand::Pattern7: {
		setPattern(6);
		break;
	}
	case InputCommand::Pattern8: {
		setPattern(7);
		break;
	}
	case InputCommand::Pattern9: {
		setPattern(8);
		break;
	}
	case InputCommand::Pattern10: {
		setPattern(9);
		break;
	}
	case InputCommand::Pattern11: {
		setPattern(10);
		break;
	}
	case InputCommand::Pattern12: {
		setPattern(11);
		break;
	}

								// color buttons

	case InputCommand::Red: {
		setColor(Red);
		break;
	}
	case InputCommand::RedOrange: {
		setColor(OrangeRed);
		break;
	}
	case InputCommand::Orange: {
		setColor(Orange);
		break;
	}
	case InputCommand::YellowOrange: {
		setColor(Goldenrod);
		break;
	}
	case InputCommand::Yellow: {
		setColor(Yellow);
		break;
	}

	case InputCommand::Green: {
		setColor(Green);
		break;
	}
	case InputCommand::Lime: {
		setColor(Lime);
		break;
	}
	case InputCommand::Aqua: {
		setColor(Aqua);
		break;
	}
	case InputCommand::Teal: {
		setColor(Teal);
		break;
	}
	case InputCommand::Navy: {
		setColor(Navy);
		break;
	}

	case InputCommand::Blue: {
		setColor(Blue);
		break;
	}
	case InputCommand::RoyalBlue: {
		setColor(RoyalBlue);
		break;
	}
	case InputCommand::Purple: {
		setColor(Purple);
		break;
	}
	case InputCommand::Indigo: {
		setColor(Indigo);
		break;
	}
	case InputCommand::Magenta: {
		setColor(Magenta);
		break;
	}

	case InputCommand::White: {
		setColor(White);
		break;
	}
	case InputCommand::Pink: {
		setColor(Pink);
		break;
	}
	case InputCommand::LightPink: {
		setColor(LightPink);
		break;
	}
	case InputCommand::BabyBlue: {
		setColor(CornflowerBlue);
		break;
	}
	case InputCommand::LightBlue: {
		setColor(LightBlue);
		break;
	}
	}
}
#endif

void setup() {
	Serial.begin(115200);
#if defined(ESP8266)
	pixels = new NeoPixelBus<COLOR_ORDER, LED_TYPE>(NUMPIXELS);
#elif defined(ESP32)
	pixels = new NeoPixelBus<COLOR_ORDER, LED_TYPE>(NUMPIXELS, PIXELSPIN);
#endif
	currentPixel = 0;
	Showcount = StartShow;

	pixels->Begin(); // This initializes the NeoPixel library.
	for (int i = 0; i < NUMPIXELS; i++) {
		pixels->SetPixelColor(i, Black);
	}
	pixels->Show(); // This sends the updated pixel color to the hardware.
	Serial.println("Showcount = " + String(Showcount));
#if defined(IR_enable)
	irReceiver.enableIRIn(); // Start the receiver
#endif
}

void loop() {
#if defined(IR_enable)
	handleIrInput();
#endif
	if (power == 0) {
		pixels->ClearTo(Black);
		pixels->Show();
		return;
	}
	if (autoplay == 1) {
		if ((unsigned long)(millis() - ShowPreviousMillis) >= ShowInterval) {
			adjustPattern(true);
			ShowPreviousMillis = millis();
		}
	}

	switch (Showcount) {
	case 0:
		if ((unsigned long)(millis() - colorWipePreviousMillis) >= pixelsInterval) {
			colorWipePreviousMillis = millis();
			colorWipe(currentColor);
		}
		break;
	case 1:
		if ((unsigned long)(millis() - theaterChasePreviousMillis) >= pixelsInterval) {
			theaterChasePreviousMillis = millis();
			theaterChase(currentColor); // Red
		}
		break;
	case 2:
		if ((unsigned long)(millis() - theaterChaseRainbowPreviousMillis) >= pixelsInterval) {
			theaterChaseRainbowPreviousMillis = millis();
			theaterChaseRainbow();
		}
		break;
	case 3:
		if ((unsigned long)(millis() - rainbowPreviousMillis) >= pixelsInterval) {
			rainbowPreviousMillis = millis();
			rainbow();
		}
		break;
	case 4:
		if ((unsigned long)(millis() - rainbowCyclesPreviousMillis) >= pixelsInterval) {
			rainbowCyclesPreviousMillis = millis();
			rainbowCycle();
		}
		break;
	case 5:
		setSolidColor(currentColor);
		break;
	default:
		break;
	}
}

void setPattern(uint8_t value) {
	if (value >= EndShow)
		value = EndShow - 1;

	LOG_DEBUG("setPattern:", value);
	Showcount = value;
}

void adjustPattern(bool up) {
	if (up)
		Showcount++;
	else
		Showcount--;

	// wrap around at the ends
	if (Showcount < 0)
		Showcount = EndShow;
	if (Showcount >= EndShow)
		Showcount = 0;

	LOG_DEBUG("adjustPattern:", Showcount);
}

void adjustSpeed(bool up) {
	if (up)
		pixelsInterval++;
	else
		pixelsInterval--;

	// wrap around at the ends
	if (pixelsInterval < 0)
		pixelsInterval = 0;
	if (pixelsInterval >= 255)
		pixelsInterval = 255;

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
	autoplay = value == 0 ? 0 : 1;

	LOG_DEBUG("setAutoplay:", autoplay);
}

void setColor(RgbColor c) {
	// Scale the color components by brightness
	currentColor = RgbColor(
		(uint8_t)((c.R * brightness) / 255),
		(uint8_t)((c.G * brightness) / 255),
		(uint8_t)((c.B * brightness) / 255)
	);
}

void setSolidColor(RgbColor c) {
	bool needsUpdate = false;
	for (int i = 0; i < NUMPIXELS; i++) {
		if (pixels->GetPixelColor(i) != c) {
			pixels->SetPixelColor(i, c);
			needsUpdate = true;
		}
	}
	if (needsUpdate) {
		pixels->Show();
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
