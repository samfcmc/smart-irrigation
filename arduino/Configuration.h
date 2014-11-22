#ifndef CONFIGURARION
#define CONFIGURARION

#include <Thread.h>
#include "CommThread.h"

#define PARAM_COUNT	6

/*
// The following is for when we have two twin parameters:
//  maximum and minimum threshold... For example in moisture.
//  In that case we can simply declare a array of 2 elements.
#define MAX 0
#define MIN 1
*/

/*
 * Protocol for setting registers:
 *  Two commands: GET and SET.
 *  Each of them includes the parameter id.
 */
enum Opcode {
  MESS_GET = 1,
  MESS_SET = 2,
};

/*enum irrigation_parameter {
  MIN_MOISTURE,
  MAX_MOISTURE,
  
  PARAM_COUNT
};*/

enum Parameters {
	CURRENT_TEMPERATURE = 0,
	CURRENT_HUMIDITY = 1,
	TEMPERATURE_MIN = 2,
	TEMPERATURE_MAX = 3,
	HUMIDITY_MIN = 4,
	HUMIDITY_MAX = 5,
};

class Configuration {

private:
    uint8_t parameters[PARAM_COUNT];

public:

	Configuration();
	//void addObserver(Thread*);

	uint8_t processMessage(char *message);
};

#endif