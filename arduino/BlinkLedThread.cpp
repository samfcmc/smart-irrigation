#include <Arduino.h>
#include "BlinkLedThread.h"

BlinkLedThread::BlinkLedThread(int pin, int interval): Thread() {
	_pin = pin;
	_state = false;
	setInterval(interval);
	pinMode(_pin, OUTPUT);
}

void BlinkLedThread::run() {
	_state = !_state;
	digitalWrite(_pin, _state);
	runned();	
}