#include <Arduino.h>
#include <Thread.h>
#include <ThreadController.h>
#include "BlinkLedThread.h"

int LED_PIN = 13;
int TIMER_INTERVAL = 1000;

BlinkLedThread blinkLedThread(LED_PIN, TIMER_INTERVAL);
ThreadController threadController;

void setup() {                
	Serial.begin(9600);
	threadController.add(&blinkLedThread);
}

void loop() {
  	threadController.run();
}