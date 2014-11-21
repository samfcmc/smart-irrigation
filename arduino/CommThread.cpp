#include <Arduino.h>
#include "CommThread.h"

#define TIMEOUT 300

CommThread *CommThread::instance = NULL;

CommThread::CommThread(): Thread() {
  this->state = STATE_IDLE;
  this->currentIndex = 0;
  this->messageAvailable = false;
  this->lastReceivedTimestamp = 0;
  this->onMessageReceived = NULL;
  this->onMessageSent = NULL;
}

CommThread *CommThread::getInstance() {
	if(!CommThread::instance) {
		CommThread::instance = new CommThread();
	}
	return CommThread::instance;
}

void CommThread::init(int rate) {
	Serial.begin(rate);
	Serial.write('a');
}

void CommThread::run()
{
	long sinceStartedRX;

	if(this->state == STATE_IDLE && Serial.available()) {
		//Received a message
		this->state = STATE_RX;
		this->messageAvailable = false;
		this->lastReceivedTimestamp = millis();
		this->currentIndex = 0;
	}
	else if(this->state == STATE_RX) {
		//Receiving a message
		if(Serial.available()) {
			char received = Serial.read();
			if(this->currentIndex < BUFF_SIZE) {
				//Didn't reach buffer limit
				this->inBuffer[this->currentIndex] = received;
				this->currentIndex++;	
			}
			this->lastReceivedTimestamp = millis();
		}
		else {
			sinceStartedRX = millis() - this->lastReceivedTimestamp;
			if(sinceStartedRX > TIMEOUT) {
				//Stop receiving a message
				this->state = STATE_IDLE;
				this->messageAvailable = true;
				this->inBuffer[this->currentIndex - 1] = '\0';
				if(this->onMessageReceived) {
					this->onMessageReceived(this->inBuffer, this->currentIndex);
				}
			}
		}
	}
	else if(this->state == STATE_WX) {
		char toSend;
		if(this->currentIndex < this->messageSize && this->currentIndex < BUFF_SIZE) {
			toSend = this->outBuffer[this->currentIndex];
			Serial.write(toSend);
			this->currentIndex++;
		}
		else {
			// Message sent
			if(this->onMessageSent) {
				this->onMessageSent(this->currentIndex);
			}
			this->state = STATE_IDLE;
			this->currentIndex = 0;
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

void CommThread::sendMessage(char *buffer, int size, void (*callback)(int))
{
  strncpy(this->outBuffer, buffer, size);
  this->state = STATE_WX;
  this->currentIndex = 0;
  this->onMessageSent = callback;
  this->messageSize =  size;
}

