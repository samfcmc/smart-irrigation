#include <Thread.h>

class BlinkLedThread: public Thread {

private:
	int _pin;
	bool _state;
	
public:
	BlinkLedThread(int pin, int interval);

	void run();
};