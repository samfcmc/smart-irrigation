#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include "CommThread.h"
#include "Configuration.h"
#include "IrrigationThread.h"

// System-relevant (low level) data
int LED_PIN = 13;
int TIMER_INTERVAL = 1000;

// Threads
CommThread *commThread = CommThread::getInstance();
Configuration configuration;
IrrigationThread irrigationThread(&configuration, LED_PIN);
ThreadController threadController;

//Buffer
char buffer[BUFF_SIZE];
char response[] = {0};

/*
 * Testing callbacks
 */
void onSent(int size) {
}

void onMessageReceived(char *message, int size) {
	response[0] = configuration.processMessage(message);
	commThread->sendMessage(response, 1, onSent);
}

void setup() {
	// Init threads
	commThread->init();
	commThread->setOnMessageReceived(onMessageReceived);

	// Add Threads to Controller
	threadController.add(commThread);
	threadController.add(&irrigationThread);
}

void loop() {
  	threadController.run();
}