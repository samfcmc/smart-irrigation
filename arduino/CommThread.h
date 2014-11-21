#include <Thread.h>

#define BUFF_SIZE	16
#define DEFAULT_RATE	9600

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
	int messageSize;
	int currentIndex;
	bool messageAvailable;
	long lastReceivedTimestamp;
	void (*onMessageReceived)(char*,int);
	void (*onMessageSent)(int);

public:
	CommThread();
	
	void init(int rate = DEFAULT_RATE);
	bool hasMessageAvailable();
	bool isFree();
	void getMessage(char *buffer, int size);
	void sendMessage(char *buffer, int size, void (*callback)(int) = NULL);
	void setOnMessageReceived(void (*callback)(char*, int size));

	void run();
};