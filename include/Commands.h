/*
	 Tree v2: https://github.com/evilgeniuslabs/tree-v2
	 Copyright (C) 2015 Jason Coon

	 This program is free software: you can redistribute it and/or modify
	 it under the terms of the GNU General Public License as published by
	 the Free Software Foundation, either version 3 of the License, or
	 (at your option) any later version.

	 This program is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	 GNU General Public License for more details.

	 You should have received a copy of the GNU General Public License
	 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Arduino.h"

enum class InputCommand {
	None,
	Up,
	Down,
	Left,
	Right,
	Select,
	Brightness,
	PlayMode,
	Palette,
	Power,
	PowerOn,
	PowerOff,
	BrightnessUp,
	BrightnessDown,

	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4,
	Pattern5,
	Pattern6,
	Pattern7,
	Pattern8,
	Pattern9,
	Pattern10,
	Pattern11,
	Pattern12,

	RedUp,
	RedDown,
	GreenUp,
	GreenDown,
	BlueUp,
	BlueDown,

	Red,
	RedOrange,
	Orange,
	YellowOrange,
	Yellow,

	Green,
	Lime,
	Aqua,
	Teal,
	Navy,

	Blue,
	RoyalBlue,
	Purple,
	Indigo,
	Magenta,

	White,
	Pink,
	LightPink,
	BabyBlue,
	LightBlue,
};

// IR Raw Key Codes for SparkFun remote
#define IRCODE_SPARKFUN_POWER  0x10EFD827 // 284153895
#define IRCODE_SPARKFUN_A      0x10EFF807 //
#define IRCODE_SPARKFUN_B      0x10EF7887
#define IRCODE_SPARKFUN_C      0x10EF58A7
#define IRCODE_SPARKFUN_UP     0x10EFA05F // 284139615
#define IRCODE_SPARKFUN_LEFT   0x10EF10EF
#define IRCODE_SPARKFUN_SELECT 0x10EF20DF
#define IRCODE_SPARKFUN_RIGHT  0x10EF807F
#define IRCODE_SPARKFUN_DOWN   0x10EF00FF
#define IRCODE_SPARKFUN_HELD   0xFFFFFFFF

// IR Raw Key Codes for Adafruit remote
#define IRCODE_ADAFRUIT_HELD        0x7FFFFFFF // 4294967295
#define IRCODE_ADAFRUIT_VOLUME_UP   0x00FD40BF // 16597183
#define IRCODE_ADAFRUIT_PLAY_PAUSE  0x00FD807F // 16613503
#define IRCODE_ADAFRUIT_VOLUME_DOWN 0x00FD00FF // 16580863
#define IRCODE_ADAFRUIT_SETUP       0x00FD20DF // 16589023
#define IRCODE_ADAFRUIT_UP          0x00FDA05F // 16621663
#define IRCODE_ADAFRUIT_STOP_MODE   0x00FD609F // 16605343
#define IRCODE_ADAFRUIT_LEFT        0x00FD10EF // 16584943
#define IRCODE_ADAFRUIT_ENTER_SAVE  0x00FD906F // 16617583
#define IRCODE_ADAFRUIT_RIGHT       0x00FD50AF // 16601263
#define IRCODE_ADAFRUIT_0_10_PLUS   0x00FD30CF // 16593103
#define IRCODE_ADAFRUIT_DOWN        0x00FDB04F // 16625743
#define IRCODE_ADAFRUIT_BACK        0x00FD708F // 16609423
#define IRCODE_ADAFRUIT_1           0x00FD08F7 // 16582903
#define IRCODE_ADAFRUIT_2           0x00FD8877 // 16615543
#define IRCODE_ADAFRUIT_3           0x00FD48B7 // 16599223
#define IRCODE_ADAFRUIT_4           0x00FD28D7 // 16591063
#define IRCODE_ADAFRUIT_5           0x00FDA857 // 16623703
#define IRCODE_ADAFRUIT_6           0x00FD6897 // 16607383
#define IRCODE_ADAFRUIT_7           0x00FD18E7 // 16586983
#define IRCODE_ADAFRUIT_8           0x00FD9867 // 16619623
#define IRCODE_ADAFRUIT_9           0x00FD58A7 // 16603303

// IR Raw Key Codes for eTopxizu 44Key IR Remote Controller for 5050 3528 RGB LED Light Strip
#define IRCODE_ETOPXIZU_HELD            0x7FFFFFFF // 4294967295
#define IRCODE_ETOPXIZU_POWER           16712445
#define IRCODE_ETOPXIZU_PLAY_PAUSE      16745085
#define IRCODE_ETOPXIZU_BRIGHTNESS_UP   16726725
#define IRCODE_ETOPXIZU_BRIGHTNESS_DOWN 16759365

#define IRCODE_ETOPXIZU_DIY1            16724175
#define IRCODE_ETOPXIZU_DIY2            16756815
#define IRCODE_ETOPXIZU_DIY3            16740495
#define IRCODE_ETOPXIZU_DIY4            16716015
#define IRCODE_ETOPXIZU_DIY5            16748655
#define IRCODE_ETOPXIZU_DIY6            16732335

#define IRCODE_ETOPXIZU_JUMP3           16720095
#define IRCODE_ETOPXIZU_JUMP7           16752735
#define IRCODE_ETOPXIZU_FADE3           16736415
#define IRCODE_ETOPXIZU_FADE7           16769055
#define IRCODE_ETOPXIZU_FLASH           16764975
#define IRCODE_ETOPXIZU_AUTO            16773135

#define IRCODE_ETOPXIZU_QUICK           16771095
#define IRCODE_ETOPXIZU_SLOW            16762935

#define IRCODE_ETOPXIZU_RED_UP          16722135
#define IRCODE_ETOPXIZU_RED_DOWN        16713975

#define IRCODE_ETOPXIZU_GREEN_UP        16754775
#define IRCODE_ETOPXIZU_GREEN_DOWN      16746615

#define IRCODE_ETOPXIZU_BLUE_UP         16738455
#define IRCODE_ETOPXIZU_BLUE_DOWN       16730295

#define IRCODE_ETOPXIZU_RED             16718565
#define IRCODE_ETOPXIZU_RED_ORANGE      16722645
#define IRCODE_ETOPXIZU_ORANGE          16714485
#define IRCODE_ETOPXIZU_YELLOW_ORANGE   16726215
#define IRCODE_ETOPXIZU_YELLOW          16718055

#define IRCODE_ETOPXIZU_GREEN           16751205
#define IRCODE_ETOPXIZU_LIME            16755285
#define IRCODE_ETOPXIZU_AQUA            16747125
#define IRCODE_ETOPXIZU_TEAL            16758855
#define IRCODE_ETOPXIZU_NAVY            16750695

#define IRCODE_ETOPXIZU_BLUE            16753245
#define IRCODE_ETOPXIZU_ROYAL_BLUE      16749165
#define IRCODE_ETOPXIZU_PURPLE          16757325
#define IRCODE_ETOPXIZU_INDIGO          16742535
#define IRCODE_ETOPXIZU_MAGENTA         16734375

#define IRCODE_ETOPXIZU_WHITE           16720605
#define IRCODE_ETOPXIZU_PINK            16716525
#define IRCODE_ETOPXIZU_LIGHT_PINK      16724685
#define IRCODE_ETOPXIZU_BABY_BLUE       16775175
#define IRCODE_ETOPXIZU_LIGHT_BLUE      16767015

// IR Raw Key Codes for B_K_LIGHT remote
#define IRCODE_B_K_LIGHT_HELD             0xFFFFFFFFFFFFFFFF
#define IRCODE_B_K_LIGHT_BRIGHTNESS_UP    0xF700FF
#define IRCODE_B_K_LIGHT_BRIGHTNESS_DOWN  0xF7807F
#define IRCODE_B_K_LIGHT_OFF              0xF740BF
#define IRCODE_B_K_LIGHT_ON               0xF7C03F
#define IRCODE_B_K_LIGHT_RED              0xF720DF
#define IRCODE_B_K_LIGHT_RED_ORANGE       0xF710EF
#define IRCODE_B_K_LIGHT_ORANGE           0xF730CF
#define IRCODE_B_K_LIGHT_YELLOW_ORANGE    0xF708F7
#define IRCODE_B_K_LIGHT_YELLOW           0xF728D7
#define IRCODE_B_K_LIGHT_GREEN            0xF7A05F
#define IRCODE_B_K_LIGHT_LIME             0xF7906F
#define IRCODE_B_K_LIGHT_AQUA             0xF7B04F
#define IRCODE_B_K_LIGHT_TEAL             0xF78877
#define IRCODE_B_K_LIGHT_NAVY             0xF7A857
#define IRCODE_B_K_LIGHT_BLUE             0xF7609F
#define IRCODE_B_K_LIGHT_ROYAL_BLUE       0xF750AF
#define IRCODE_B_K_LIGHT_PURPLE           0xF7708F
#define IRCODE_B_K_LIGHT_INDIGO           0xF748B7
#define IRCODE_B_K_LIGHT_PINK             0xF76897
#define IRCODE_B_K_LIGHT_WHITE            0xF7E01F
#define IRCODE_B_K_LIGHT_FLASH            0xF7D02F
#define IRCODE_B_K_LIGHT_STROBE           0xF7F00F
#define IRCODE_B_K_LIGHT_FADE             0xF7C837
#define IRCODE_B_K_LIGHT_SMOOTH           0xF7E817

// IR Raw Key Codes for Wokwi remote
#define IRCODE_WOKWI_POWER                16729530
#define IRCODE_WOKWI_MENU                 16730040
#define IRCODE_WOKWI_TEST                 16729275
#define IRCODE_WOKWI_PLUS                   16728255
#define IRCODE_WOKWI_BACK                 16729020
#define IRCODE_WOKWI_PREV                 16713720
#define IRCODE_WOKWI_PLAY                 16717290
#define IRCODE_WOKWI_FORW                16714230
#define IRCODE_WOKWI_0                    16717545
#define IRCODE_WOKWI_MIN                 16718310
#define IRCODE_WOKWI_C                    16715250
#define IRCODE_WOKWI_1                    16714995
#define IRCODE_WOKWI_2                    16718055
#define IRCODE_WOKWI_3                    16735905
#define IRCODE_WOKWI_4                    16713975
#define IRCODE_WOKWI_5                    16719075
#define IRCODE_WOKWI_6                    16734885
#define IRCODE_WOKWI_7                    16728765
#define IRCODE_WOKWI_8                    16732845
#define IRCODE_WOKWI_9                    16730805

extern bool sparkfunRemoteEnabled;
extern bool adafruitRemoteEnabled;
extern bool etopxizuRemoteEnabled;
extern bool B_K_LIGHTRemoteEnabled;
extern bool wokwiRemoteEnabled;

extern unsigned long lastIrCode;
extern unsigned int holdStartTime;
extern unsigned int defaultHoldDelay;
extern bool isHolding;
extern unsigned int zeroStartTime;
extern unsigned int zeroDelay;

// Function declarations
unsigned long decodeIRCode();
unsigned long readIRCode();
unsigned long readIRCode(unsigned int holdDelay);
enum class InputCommand;
InputCommand getCommand(unsigned long input);
void heldButtonHasBeenHandled();
unsigned long waitForIRCode();
InputCommand readCommand();
InputCommand readCommand(unsigned int holdDelay);
