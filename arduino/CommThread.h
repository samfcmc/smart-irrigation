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
	char outBuffer[BUFF_SIZE];
	int currentIndex;
	bool messageAvailable;
	long lastReceivedTimestamp;

public:
	CommThread();
	
	bool hasMessageAvailable();
	bool isFree();
	void getMessage(char *buffer, int size);
	void sendMessage(char *buffer);

	void run();
};