#include <Thread.h>

#define BUFF_SIZE	16

typedef enum { 
    STATE_IDLE,
} State;

class CommThread: public Thread {

private:
	State _state;

	char _inBuffer[BUFF_SIZE];
	char _outBuff [BUFF_SIZE];

public:
	CommThread();
	
	bool messageAvailable

	void run();
};