#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include "BlinkLedThread.h"
#include "CommThread.h"

int LED_PIN = 13;
int TIMER_INTERVAL = 1000;

BlinkLedThread blinkLedThread(LED_PIN, TIMER_INTERVAL);
CommThread commThread;
ThreadController threadController;
char buffer[BUFF_SIZE];

void setup() {                
	Serial.begin(9600);
	pinMode(LED_PIN, OUTPUT);
	// Add threads to thread controller
	//threadController.add(&blinkLedThread);
	threadController.add(&commThread);
}

void loop() {
	if(commThread.hasMessageAvailable()) {
		commThread.getMessage(buffer, BUFF_SIZE);
		buffer[BUFF_SIZE - 1] = '\0';
		Serial.println(buffer);
	}
  	threadController.run();
}