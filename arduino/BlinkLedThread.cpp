#include <Arduino.h>
#include "BlinkLedThread.h"

BlinkLedThread::BlinkLedThread(int pin, int interval): Thread() {
	pinMode(_pin, OUTPUT);
	setInterval(interval);
	_pin = pin;
	_state = false;
}

void BlinkLedThread::run() {
	_state = !_state;
	digitalWrite(_pin, _state);
	runned();	
}