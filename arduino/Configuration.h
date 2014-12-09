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
	uint8_t parameters[PARAM_COUNT];

public:

	Configuration();

	uint8_t processMessage(char *message);

	inline uint8_t getCurrentHumidity() {
		return this->parameters[CURRENT_HUMIDITY];
	}
    inline void setCurrentHumidity(uint8_t value) {
        this->parameters[CURRENT_HUMIDITY] = value;
    }

	inline uint8_t getHumidityMin() {
		return this->parameters[HUMIDITY_MIN];
	}
	inline uint8_t getHumidityMax() {
		return this->parameters[HUMIDITY_MAX];
	}
};

#endif