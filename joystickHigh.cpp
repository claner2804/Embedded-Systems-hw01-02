#include <avr/io.h>
#include "JoystickHigh.h"
#include "Arduino.h"

#define ABS(x)		((x)>=0 ? (x) : -(x))


JoystickLow::JoystickLow(int pinX, int pinY, int pinButton)
	: pinX(pinX), pinY(pinY) {
}

void JoystickLow::begin() {
	DDRE = DDRE & ~(1 << PE2); // PE2 als Digitaleingang konfigurieren
	PORTE = PORTE & ~(1 << PE2); // Pullup-Widerstand für PE2 ausschalten
}

void JoystickLow::update() {
	posX = getPosX(true);
	posY = getPosY(true);
	button = getButton(true);
}

int16_t JoystickLow::getPosX(bool immediate) {
	if (immediate) {
		int16_t value = map(analogRead(pinX), 0, 1023, -512, 512);
		if (ABS(value) <= deadzone) {
			value = 0;
		}
		return value;
	} else {
		return posX;
	}
}

int16_t JoystickLow::getPosY(bool immediate) {
	if (immediate) {
		int16_t value = map(analogRead(pinY), 0, 1023, -512, 512);
		if (ABS(value) <= deadzone) {
			value = 0;
		}
		return value;
	} else {
		return posY;
	}
}

bool JoystickLow::getButton(bool immediate) {
	if (immediate) {
		return PINE & (1 << PE2);
	} else {
		return button;
	}
}

void JoystickLow::setDeadzone(int16_t deadzone) {
	this->deadzone = ABS(deadzone);
}

int16_t JoystickLow::getDeadzone() {
	return deadzone;
}