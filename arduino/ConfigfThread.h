#include <Thread.h>

#define BUFF_SIZE	16

enum State { 
    STATE_IDLE,
    STATE_RX,
    STATE_WX,
};

class ConfigfThread: public Thread {

private:
	State state;


public:
	ConfigfThread();
	

	void run();
};