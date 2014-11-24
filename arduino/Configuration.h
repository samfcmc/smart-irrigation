#ifndef CONFIGURARION
#define CONFIGURARION

#include <Thread.h>
#include "CommThread.h"

/*
 * Protocol for setting registers:
 *  Two commands: GET and SET.
 *  Each of them includes the parameter id.
 */
enum Opcode {
  MESS_GET = 1,
  MESS_SET = 2,
};

enum Parameters {
	CURRENT_TEMPERATURE = 0,
	CURRENT_HUMIDITY = 1,
	TEMPERATURE_MIN = 2,
	TEMPERATURE_MAX = 3,
	HUMIDITY_MIN = 4,
	HUMIDITY_MAX = 5,
};
#define PARAM_COUNT	6

class Configuration {
private:
	int parameters[PARAM_COUNT];

public:

	Configuration();

	uint8_t processMessage(char *message);

	inline int getCurrentHumidity() {
		return this->parameters[CURRENT_HUMIDITY];
	}

	inline int getHumidityMin() {
		return this->parameters[HUMIDITY_MIN];
	}

	inline int getHumidityMax() {
		return this->parameters[HUMIDITY_MAX];
	}

	inline void setHumidity(int value) {
		this->parameters[CURRENT_HUMIDITY] = value;
	}
};

#endif