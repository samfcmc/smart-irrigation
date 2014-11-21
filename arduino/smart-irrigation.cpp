#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include "BlinkLedThread.h"
#include "CommThread.h"
#include "ConfigThread.h"

// Common data
#include "common.h"

// System-relevant (low level) data
int LED_PIN = 13;
int TIMER_INTERVAL = 1000;

// Threads
CommThread *commThread = CommThread::getInstance();
ConfigThread configThread;
ThreadController threadController;

//Buffer
char buffer[BUFF_SIZE];
char test[] = {0};

/*
 * Testing callbacks
 */
void onSent(int size) {
	digitalWrite(LED_PIN, HIGH);
}

void onMessageReceived(char *message, int size) {
	commThread->sendMessage(test, 1, onSent);
}

void setup() {
  	// Init pins
	pinMode(LED_PIN, OUTPUT);
	
	// Init threads
	commThread->init();
	commThread->setOnMessageReceived(onMessageReceived);

	// Add Threads to Controller
	threadController.add(commThread);
}



void loop() {
  	threadController.run();
}