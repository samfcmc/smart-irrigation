#include <Thread.h>

#define BUFF_SIZE	16

/*
// The following is for when we have two twin parameters:
//  maximum and minimum threshold... For example in moisture.
//  In that case we can simply declare a array of 2 elements.
#define MAX 0
#define MIN 1
*/

enum irrigation_parameter {
  MIN_MOISTURE,
  MAX_MOISTURE,
  
  PARAM_COUNT
};

class ConfigThread: public Thread {

private:
	//list<Thread*> observers;

public:
        int _params[PARAM_COUNT];

	ConfigThread();
	//void addObserver(Thread*);

	void run();
};
