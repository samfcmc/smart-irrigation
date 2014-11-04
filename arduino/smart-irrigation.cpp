#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>

class BlinkLedThread: public Thread {
	
public:
	int _pin;
	bool _state;

	BlinkLedThread(int pin, int interval): Thread() {
		pinMode(_pin, OUTPUT);
		setInterval(interval);
		_pin = pin;
		_state = false;
	}

	void run() {
		_state = !_state;
		digitalWrite(_pin, _state);
		runned();	
	}
};

int LED_PIN = 13;
int TIMER_INTERVAL = 1000;

Thread *blinkLedThread = new BlinkLedThread(LED_PIN, TIMER_INTERVAL);
ThreadController *threadController = new ThreadController();

void setup() {                
	Serial.begin(9600);
	threadController->add(blinkLedThread);
}

void loop() {
  	threadController->run();
}