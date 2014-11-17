#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include "BlinkLedThread.h"
#include "CommThread.h"

#include "common.h"
// Common data
CommThread commThread;


// System-relevant (low level) data
int LED_PIN = 13;
int TIMER_INTERVAL = 1000;

BlinkLedThread blinkLedThread(LED_PIN, TIMER_INTERVAL);
ThreadController threadController;
char buffer[BUFF_SIZE];

void setup() {
	//Tell connected client that Arduino is ready
	Serial.begin(9600);
	Serial.write('a');
  
  
	pinMode(LED_PIN, OUTPUT);
	// Add threads to thread controller
	//threadController.add(&blinkLedThread);
	threadController.add(&commThread);
}

void loop() {
	if(commThread.hasMessageAvailable()) {
		commThread.getMessage(buffer, BUFF_SIZE);
		//buffer[BUFF_SIZE - 1] = '\0';
		commThread.sendMessage(buffer);
	}
  	threadController.run();
}