#ifndef IRRIGATION_THREAD
#define IRRIGATION_THREAD

#include <Arduino.h>
#include <Thread.h>
#include "Configuration.h"
#include "AnalogSensor.h"

#define DEFAULT_PIN	13
#define DEFAULT_INTERVAL	5000

class IrrigationThread: public Thread {

private:
	Configuration *configuration;
	bool watering;
	int _coilValvePin;

	HumiditySensor     _humiditySensor;
	TemperatureSensor  _temperatureSensor;

public:
	IrrigationThread(Configuration *configuration, int pin = DEFAULT_PIN, int interval = DEFAULT_INTERVAL);
	
	void run();

	void setWateringState(bool state);
};

#endif