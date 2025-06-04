#include "handleIrInput.h"
#include <DebugLog.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "declarations.h"
#include "variables.h"
#include "Commands.h"

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
		setPattern(random(numEffects));
		break;
	}
	case InputCommand::Up: {
		setAutoplay(false);
		adjustPattern(true);
		break;
	}
	case InputCommand::Down: {
		setAutoplay(false);
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

	case InputCommand::Pattern1: {
		setAutoplay(false);
		setPattern(0);
		break;
	}
	case InputCommand::Pattern2: {
		setAutoplay(false);
		setPattern(1);
		break;
	}
	case InputCommand::Pattern3: {
		setAutoplay(false);
		setPattern(2);
		break;
	}
	case InputCommand::Pattern4: {
		setAutoplay(false);
		setPattern(3);
		break;
	}
	case InputCommand::Pattern5: {
		setAutoplay(false);
		setPattern(4);
		break;
	}
	case InputCommand::Pattern6: {
		setAutoplay(false);
		setPattern(5);
		break;
	}
	case InputCommand::Pattern7: {
		setAutoplay(false);
		setPattern(6);
		break;
	}
	case InputCommand::Pattern8: {
		setAutoplay(false);
		setPattern(7);
		break;
	}
	case InputCommand::Pattern9: {
		setAutoplay(false);
		setPattern(8);
		break;
	}
	case InputCommand::Pattern10: {
		setAutoplay(false);
		setPattern(9);
		break;
	}
	case InputCommand::Pattern11: {
		setAutoplay(false);
		setPattern(10);
		break;
	}
	case InputCommand::Pattern12: {
		setAutoplay(false);
		setPattern(11);
		break;
	}

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