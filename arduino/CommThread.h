#include <Thread.h>

#define BUFF_SIZE	16

enum State { 
    STATE_IDLE,
    STATE_RX,
    STATE_WX,
};

class CommThread: public Thread {

private:
	State state;

	char inBuffer[BUFF_SIZE];
	char outBuff [BUFF_SIZE];
	int currentIndex;
	bool messageAvailable;
	long startedRXTimestamp;

public:
	CommThread();
	
	bool hasMessageAvailable();
	bool isFree();
	void getMessage(char *buffer, int size);
	void sendMessage(char *buffer, int size);

	void run();
};