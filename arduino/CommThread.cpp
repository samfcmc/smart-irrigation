#include <Arduino.h>
#include "CommThread.h"

#define TIMEOUT 300

CommThread::CommThread(): Thread() {
  this->state = STATE_IDLE;
  this->currentIndex = 0;
  this->messageAvailable = false;
  this->startedRXTimestamp = 0;
}

void CommThread::run()
{
	long sinceStartedRX;

	if(this->state == STATE_IDLE && Serial.available()) {
		//Received a message
		this->state = STATE_RX;
		this->messageAvailable = false;
		this->startedRXTimestamp = millis();
		this->currentIndex = 0;
	}
	else if(this->state == STATE_RX) {
		//Receiving a message
		if(Serial.available()) {
			if(this->currentIndex < BUFF_SIZE) {
				//Didn't reach buffer limit
				this->inBuffer[this->currentIndex] = Serial.read();
				this->currentIndex++;	
			}
			else {
				//Reached buffer limit
				//Just ignore remaining bytes
				Serial.read();
			}
		}
		else {
			sinceStartedRX = millis() - this->startedRXTimestamp;
			if(sinceStartedRX > TIMEOUT) {
				//Stop receiving a message
				this->state = STATE_IDLE;
				this->messageAvailable = true;
				this->inBuffer[this->currentIndex] = '\0';
			}
		}
	}
}


bool CommThread::hasMessageAvailable()
{
	return this->messageAvailable;
}

bool CommThread::isFree()
{
	return this->state == STATE_IDLE;
}

void CommThread::getMessage(char *buffer, int size)
{
  strncpy(buffer, this->inBuffer, size);
  this->messageAvailable = false;
}

void CommThread::sendMessage(char *buffer, int size)
{
  /* TODO */
}

