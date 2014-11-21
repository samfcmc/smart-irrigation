#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include "BlinkLedThread.h"
#include "CommThread.h"
#include "ConfigThread.h"

#include "common.h"
// Common data
CommThread commThread;
ConfigThread configThread;


// System-relevant (low level) data
int LED_PIN = 13;
int TIMER_INTERVAL = 1000;

BlinkLedThread blinkLedThread(LED_PIN, TIMER_INTERVAL);
ThreadController threadController;
char buffer[BUFF_SIZE];

/*
 * Testing callbacks
 */
void onSent(int size) {
	digitalWrite(LED_PIN, HIGH);
}

void onMessageReceived(char *message, int size) {
	message[size - 1] = '\n';
	commThread.sendMessage(message, size, onSent);
}

void setup() {
  	// Init pins
	pinMode(LED_PIN, OUTPUT);
	
	// Init threads
	commThread.init();
	commThread.setOnMessageReceived(onMessageReceived);

	// Add Threads to Controller
	threadController.add(&commThread);
}



void loop() {
  	threadController.run();
}