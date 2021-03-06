#include <Arduino.h>
#include "IrrigationThread.h"

IrrigationThread::IrrigationThread(Configuration *configuration, int _coilValvePin, int interval):
  Thread(), _humiditySensor(A1), _temperatureSensor(A2)
{
	this->configuration = configuration;
	this->watering = false;
	this->_coilValvePin = _coilValvePin;
	setInterval(interval);
	pinMode(_coilValvePin, OUTPUT);
}

void IrrigationThread::run()
{
	// Humidity stuff
	this->configuration->setCurrentHumidity(_humiditySensor.readSensor());
	int currentHumidity = this->configuration->getCurrentHumidity();
	int humidityMin = this->configuration->getHumidityMin();
	int humidityMax = this->configuration->getHumidityMax();
	
//Serial.print(F("H:"));Serial.print(currentHumidity, DEC);Serial.print(F(";m:"));Serial.print(humidityMin, DEC);Serial.print(F(";M:"));Serial.println(humidityMax, DEC);

	if(!this->watering) {
		if(currentHumidity < humidityMin) {
			this->setWateringState(true);
		}
	}
	else {
		if(currentHumidity > humidityMax) { 
			this->setWateringState(false);
		}
	}
	
	
	// Temperture stuff
	this->configuration->setCurrentTemperature(_temperatureSensor.readSensor());
}

void IrrigationThread::setWateringState(bool state)
{
	this->watering = state;
	digitalWrite(_coilValvePin, state ? HIGH : LOW);
}
