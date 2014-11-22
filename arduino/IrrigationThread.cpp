#include <Arduino.h>
#include "IrrigationThread.h"

IrrigationThread::IrrigationThread(Configuration *configuration, int pin, int interval): Thread() {
	this->configuration = configuration;
	this->watering = false;
	this->pin = pin;
	setInterval(interval);
	pinMode(pin, OUTPUT);
}

void IrrigationThread::run() {
	uint8_t currentHumidity = this->configuration->getCurrentHumidity();
	uint8_t humidityMin = this->configuration->getHumidityMin();
	uint8_t humidityMax = this->configuration->getHumidityMax();

	if(!this->watering) {
		if(currentHumidity < humidityMin) {
			this->setWateringState(true);
		}
	}
	else {
		if(currentHumidity > humidityMin) {
			this->setWateringState(false);
		}
	}

}

void IrrigationThread::setWateringState(bool state) {
	this->watering = state;
	digitalWrite(this->pin, state);
}