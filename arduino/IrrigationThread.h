#ifndef IRRIGATION_THREAD
#define IRRIGATION_THREAD

#include <Thread.h>
#include "Configuration.h"

#define DEFAULT_PIN	13
#define DEFAULT_INTERVAL	5000

class IrrigationThread: public Thread {

private:
	Configuration *configuration;
	bool watering;
	int pin;

public:
	IrrigationThread(Configuration *configuration, int pin = DEFAULT_PIN, int interval = DEFAULT_INTERVAL);
	
	void run();

	void setWateringState(bool state);
};

#endif