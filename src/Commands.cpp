#define DEBUGLOG_DEFAULT_LOG_LEVEL_TRACE
#include "Commands.h"
#include "declarations.h"
#include <DebugLog.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// Variable definitions
bool sparkfunRemoteEnabled = true;
bool adafruitRemoteEnabled = true;
bool etopxizuRemoteEnabled = true;
bool B_K_LIGHTRemoteEnabled = true;
bool wokwiRemoteEnabled = true;

unsigned long lastIrCode = 0;
unsigned int holdStartTime = 0;
unsigned int defaultHoldDelay = 500;
bool isHolding = false;
unsigned int zeroStartTime = 0;
unsigned int zeroDelay = 120;

unsigned long decodeIRCode() {

	decode_results results;

	results.value = 0;

	// Attempt to read an IR code ?
	if (irReceiver.decode(&results)) {
		// delay(20);

		if (results.value != 0) {
			//LOG_DEBUG("decodeIRCode:", (bool)results.value);
		}

		// Prepare to receive the next IR code
		irReceiver.resume();
	}

	return results.value;
}

// Read an IR code
// Function will return 0 if no IR code available
unsigned long readIRCode() {

	// Is there an IR code to read ?
	unsigned long code = decodeIRCode();
	if (code == 0) {
		// No code so return 0
		return 0;
	}

	// Keep reading until code changes
	while (decodeIRCode() == code) {
		;
	}
	LOG_DEBUG("readIRCode:", code);
	return code;
}

InputCommand getCommand(unsigned long input) {
	if (adafruitRemoteEnabled) {
		switch (input) {
		case IRCODE_ADAFRUIT_UP:
			return InputCommand::Up;

		case IRCODE_ADAFRUIT_DOWN:
			return InputCommand::Down;

		case IRCODE_ADAFRUIT_LEFT:
			return InputCommand::Left;

		case IRCODE_ADAFRUIT_RIGHT:
			return InputCommand::Right;

		case IRCODE_ADAFRUIT_ENTER_SAVE:
			return InputCommand::Select;

		case IRCODE_ADAFRUIT_STOP_MODE:
		case IRCODE_ADAFRUIT_1:
			return InputCommand::PlayMode;

		case IRCODE_ADAFRUIT_2:
			return InputCommand::Palette;

		case IRCODE_ADAFRUIT_PLAY_PAUSE:
			return InputCommand::Power;

		case IRCODE_ADAFRUIT_VOLUME_UP:
			return InputCommand::BrightnessUp;

		case IRCODE_ADAFRUIT_VOLUME_DOWN:
			return InputCommand::BrightnessDown;
		}
	}

	if (sparkfunRemoteEnabled) {
		switch (input) {
		case IRCODE_SPARKFUN_UP:
			return InputCommand::Up;

		case IRCODE_SPARKFUN_DOWN:
			return InputCommand::Down;

		case IRCODE_SPARKFUN_LEFT:
			return InputCommand::Left;

		case IRCODE_SPARKFUN_RIGHT:
			return InputCommand::Right;

		case IRCODE_SPARKFUN_SELECT:
			return InputCommand::Select;

		case IRCODE_SPARKFUN_POWER:
			return InputCommand::Brightness;

		case IRCODE_SPARKFUN_A:
			return InputCommand::PlayMode;

		case IRCODE_SPARKFUN_B:
			return InputCommand::Palette;
		}
	}

	if (etopxizuRemoteEnabled) {
		switch (input) {
		case IRCODE_ETOPXIZU_QUICK:
			return InputCommand::Up;

		case IRCODE_ETOPXIZU_SLOW:
			return InputCommand::Down;

		case IRCODE_ETOPXIZU_PLAY_PAUSE:
			return InputCommand::PlayMode;

		case IRCODE_ETOPXIZU_POWER:
			return InputCommand::Power;

		case IRCODE_ETOPXIZU_BRIGHTNESS_UP:
			return InputCommand::BrightnessUp;
		case IRCODE_ETOPXIZU_BRIGHTNESS_DOWN:
			return InputCommand::BrightnessDown;

		case IRCODE_ETOPXIZU_DIY1:
			return InputCommand::Pattern1;
		case IRCODE_ETOPXIZU_DIY2:
			return InputCommand::Pattern2;
		case IRCODE_ETOPXIZU_DIY3:
			return InputCommand::Pattern3;
		case IRCODE_ETOPXIZU_DIY4:
			return InputCommand::Pattern4;
		case IRCODE_ETOPXIZU_DIY5:
			return InputCommand::Pattern5;
		case IRCODE_ETOPXIZU_DIY6:
			return InputCommand::Pattern6;
		case IRCODE_ETOPXIZU_JUMP3:
			return InputCommand::Pattern7;
		case IRCODE_ETOPXIZU_JUMP7:
			return InputCommand::Pattern8;
		case IRCODE_ETOPXIZU_FADE3:
			return InputCommand::Pattern9;
		case IRCODE_ETOPXIZU_FADE7:
			return InputCommand::Pattern10;
		case IRCODE_ETOPXIZU_FLASH:
			return InputCommand::Pattern11;
		case IRCODE_ETOPXIZU_AUTO:
			return InputCommand::Pattern12;

		case IRCODE_ETOPXIZU_RED_UP:
			return InputCommand::RedUp;
		case IRCODE_ETOPXIZU_RED_DOWN:
			return InputCommand::RedDown;

		case IRCODE_ETOPXIZU_GREEN_UP:
			return InputCommand::GreenUp;
		case IRCODE_ETOPXIZU_GREEN_DOWN:
			return InputCommand::GreenDown;

		case IRCODE_ETOPXIZU_BLUE_UP:
			return InputCommand::BlueUp;
		case IRCODE_ETOPXIZU_BLUE_DOWN:
			return InputCommand::BlueDown;

		case IRCODE_ETOPXIZU_RED:
			return InputCommand::Red;
		case IRCODE_ETOPXIZU_RED_ORANGE:
			return InputCommand::RedOrange;
		case IRCODE_ETOPXIZU_ORANGE:
			return InputCommand::Orange;
		case IRCODE_ETOPXIZU_YELLOW_ORANGE:
			return InputCommand::YellowOrange;
		case IRCODE_ETOPXIZU_YELLOW:
			return InputCommand::Yellow;

		case IRCODE_ETOPXIZU_GREEN:
			return InputCommand::Green;
		case IRCODE_ETOPXIZU_LIME:
			return InputCommand::Lime;
		case IRCODE_ETOPXIZU_AQUA:
			return InputCommand::Aqua;
		case IRCODE_ETOPXIZU_TEAL:
			return InputCommand::Teal;
		case IRCODE_ETOPXIZU_NAVY:
			return InputCommand::Navy;

		case IRCODE_ETOPXIZU_BLUE:
			return InputCommand::Blue;
		case IRCODE_ETOPXIZU_ROYAL_BLUE:
			return InputCommand::RoyalBlue;
		case IRCODE_ETOPXIZU_PURPLE:
			return InputCommand::Purple;
		case IRCODE_ETOPXIZU_INDIGO:
			return InputCommand::Indigo;
		case IRCODE_ETOPXIZU_MAGENTA:
			return InputCommand::Magenta;

		case IRCODE_ETOPXIZU_WHITE:
			return InputCommand::White;
		case IRCODE_ETOPXIZU_PINK:
			return InputCommand::Pink;
		case IRCODE_ETOPXIZU_LIGHT_PINK:
			return InputCommand::LightPink;
		case IRCODE_ETOPXIZU_BABY_BLUE:
			return InputCommand::BabyBlue;
		case IRCODE_ETOPXIZU_LIGHT_BLUE:
			return InputCommand::LightBlue;
		}
	}

	if (B_K_LIGHTRemoteEnabled) {
		switch (input) {
		case IRCODE_B_K_LIGHT_OFF:
			return InputCommand::PowerOff;
		case IRCODE_B_K_LIGHT_ON:
			return InputCommand::PowerOn;

		case IRCODE_B_K_LIGHT_BRIGHTNESS_UP:
			return InputCommand::BrightnessUp;
		case IRCODE_B_K_LIGHT_BRIGHTNESS_DOWN:
			return InputCommand::BrightnessDown;

		case IRCODE_B_K_LIGHT_RED:
			return InputCommand::Red;
		case IRCODE_B_K_LIGHT_RED_ORANGE:
			return InputCommand::RedOrange;
		case IRCODE_B_K_LIGHT_ORANGE:
			return InputCommand::Orange;
		case IRCODE_B_K_LIGHT_YELLOW_ORANGE:
			return InputCommand::YellowOrange;
		case IRCODE_B_K_LIGHT_YELLOW:
			return InputCommand::Yellow;

		case IRCODE_B_K_LIGHT_GREEN:
			return InputCommand::Lime;
		case IRCODE_B_K_LIGHT_LIME:
			return InputCommand::Green;
		case IRCODE_B_K_LIGHT_AQUA:
			return InputCommand::Aqua;
		case IRCODE_B_K_LIGHT_TEAL:
			return InputCommand::Teal;
		case IRCODE_B_K_LIGHT_NAVY:
			return InputCommand::Navy;

		case IRCODE_B_K_LIGHT_BLUE:
			return InputCommand::Blue;
		case IRCODE_B_K_LIGHT_ROYAL_BLUE:
			return InputCommand::RoyalBlue;
		case IRCODE_B_K_LIGHT_PURPLE:
			return InputCommand::Purple;
		case IRCODE_B_K_LIGHT_INDIGO:
			return InputCommand::Indigo;
		case IRCODE_B_K_LIGHT_PINK:
			return InputCommand::Pink;

		case IRCODE_B_K_LIGHT_WHITE:
			return InputCommand::White;
		case IRCODE_B_K_LIGHT_FLASH:
			return InputCommand::Up;
		case IRCODE_B_K_LIGHT_STROBE:
			return InputCommand::Down;
		case IRCODE_B_K_LIGHT_FADE:
			return InputCommand::PlayMode;
		case IRCODE_B_K_LIGHT_SMOOTH:
			return InputCommand::Palette;
		}
	}
	if (wokwiRemoteEnabled) {
		switch (input) {
		case IRCODE_WOKWI_POWER:
			return InputCommand::Power;

		case IRCODE_WOKWI_MENU:
			return InputCommand::Palette;

		case IRCODE_WOKWI_TEST:
			return InputCommand::Up;

		case IRCODE_WOKWI_PLUS:
			return InputCommand::BrightnessUp;

		case IRCODE_WOKWI_BACK:
			return InputCommand::Down;

		case IRCODE_WOKWI_PREV:
			return InputCommand::Left;

		case IRCODE_WOKWI_PLAY:
			return InputCommand::PlayMode;

		case IRCODE_WOKWI_FORW:
			return InputCommand::Right;

		case IRCODE_WOKWI_0:
			return InputCommand::Pattern1;

		case IRCODE_WOKWI_MIN:
			return InputCommand::BrightnessDown;

		case IRCODE_WOKWI_C:
			return InputCommand::Select;

		case IRCODE_WOKWI_1:
			return InputCommand::Pattern2;

		case IRCODE_WOKWI_2:
			return InputCommand::Pattern3;

		case IRCODE_WOKWI_3:
			return InputCommand::Pattern4;
			
		case IRCODE_WOKWI_4:
			return InputCommand::Pattern5;
			
		case IRCODE_WOKWI_5:
			return InputCommand::Pattern6;
			
		case IRCODE_WOKWI_6:
			return InputCommand::Pattern7;
			
		case IRCODE_WOKWI_7:
			return InputCommand::Pattern8;
			
		case IRCODE_WOKWI_8:
			return InputCommand::Pattern9;
			
		case IRCODE_WOKWI_9:
			return InputCommand::Pattern10;
		}
	}

	return InputCommand::None;
}

unsigned long readIRCode(unsigned int holdDelay) {
	// read the raw code from the sensor
	unsigned long irCode = readIRCode();

	//LOG_DEBUG(millis());
	//LOG_DEBUG("\t");
	//LOG_DEBUG(irCode);

	// don't return a short click until we know it's not a long hold
	// we'll have to wait for holdDelay ms to pass before returning a non-zero IR code
	// then, after that delay, as long as the button is held, we can keep returning the code
	// every time until it's released

	// the ir remote only sends codes every 107 ms or so (avg 106.875, max 111, min 102),
	// so the ir sensor will return 0 even if a button is held
	// so we have to wait longer than that before returning a non-zero code
	// in order to detect that a button has been released and is no longer held

	// only reset after we've gotten 0 back for more than the ir remote send interval
	unsigned int zeroTime = 0;

	if (irCode == 0) {
		zeroTime = millis() - zeroStartTime;
		if (zeroTime >= zeroDelay && lastIrCode != 0) {
			//LOG_DEBUG("zero delay has elapsed, returning last ir code");
			// the button has been released for longer than the zero delay
			// start over delays over and return the last code
			irCode = lastIrCode;
			lastIrCode = 0;
			return irCode;
		}

		return 0;
	}

	// reset the zero timer every time a non-zero code is read
	zeroStartTime = millis();

	unsigned int heldTime = 0;

	if (irCode == IRCODE_SPARKFUN_HELD || irCode == IRCODE_ADAFRUIT_HELD || irCode == IRCODE_B_K_LIGHT_HELD) {
		switch (getCommand(lastIrCode)) {
		case InputCommand::BlueDown:
		case InputCommand::BlueUp:
		case InputCommand::GreenDown:
		case InputCommand::GreenUp:
		case InputCommand::RedDown:
		case InputCommand::RedUp:
		case InputCommand::BrightnessDown:
		case InputCommand::BrightnessUp: {
			// has the hold delay passed?
			heldTime = millis() - holdStartTime;
			if (heldTime >= holdDelay) {
				isHolding = true;
				//LOG_DEBUG("hold delay has elapsed, returning last ir code");
				return lastIrCode;
			}
			else if (holdStartTime == 0) {
				isHolding = false;
				holdStartTime = millis();
			}
		}
		case InputCommand::Up:
		case InputCommand::Down:
		case InputCommand::Left:
		case InputCommand::Right:
		case InputCommand::Select:
		case InputCommand::Brightness:
		case InputCommand::PlayMode:
		case InputCommand::Palette:
		case InputCommand::Power:
		case InputCommand::PowerOn:
		case InputCommand::PowerOff:
		case InputCommand::Pattern1:
		case InputCommand::Pattern2:
		case InputCommand::Pattern3:
		case InputCommand::Pattern4:
		case InputCommand::Pattern5:
		case InputCommand::Pattern6:
		case InputCommand::Pattern7:
		case InputCommand::Pattern8:
		case InputCommand::Pattern9:
		case InputCommand::Pattern10:
		case InputCommand::Pattern11:
		case InputCommand::Pattern12:
		case InputCommand::Red:
		case InputCommand::RedOrange:
		case InputCommand::Orange:
		case InputCommand::YellowOrange:
		case InputCommand::Yellow:
		case InputCommand::Green:
		case InputCommand::Lime:
		case InputCommand::Aqua:
		case InputCommand::Teal:
		case InputCommand::Navy:
		case InputCommand::Blue:
		case InputCommand::RoyalBlue:
		case InputCommand::Purple:
		case InputCommand::Indigo:
		case InputCommand::Magenta:
		case InputCommand::White:
		case InputCommand::Pink:
		case InputCommand::LightPink:
		case InputCommand::BabyBlue:
		case InputCommand::LightBlue:
		case InputCommand::None: {
			// no code to return
			return 0;
		}
		}
	}
	else {
		// not zero, not IRCODE_SPARKFUN_HELD
		// store it for use later, until the hold and zero delays have elapsed
		holdStartTime = millis();
		isHolding = false;
		lastIrCode = irCode;
		return 0;
	}

	return 0;
}

void heldButtonHasBeenHandled() {
	lastIrCode = 0;
	isHolding = false;
	holdStartTime = 0;
}

unsigned long waitForIRCode() {

	unsigned long irCode = readIRCode();
	while ((irCode == 0) || (irCode == 0xFFFFFFFF)) {
		delay(200);
		irCode = readIRCode();
	}
	return irCode;
}

InputCommand readCommand() {
	return getCommand(readIRCode());
}

InputCommand readCommand(unsigned int holdDelay) {
	return getCommand(readIRCode(holdDelay));
}
