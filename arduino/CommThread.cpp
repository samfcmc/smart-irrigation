#include <Arduino.h>
#include "CommThread.h"

#define TIMEOUT 300

CommThread::CommThread(): Thread() {
  this->state = STATE_IDLE;
  this->currentIndex = 0;
  this->messageAvailable = false;
  this->lastReceivedTimestamp = 0;

  //Tell connected client that Arduino is ready
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
			}
		}
	}
	else if(this->state == STATE_WX) {
		char toSend;
		if(this->currentIndex < BUFF_SIZE) {
			toSend = this->outBuffer[this->currentIndex];
			if(toSend == '\0') {
				Serial.println("");		
			}
			else {
				Serial.print(toSend);
			}
			this->currentIndex++;
		}
		else {
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

void CommThread::sendMessage(char *buffer)
{
  strncpy(this->outBuffer, buffer, BUFF_SIZE);
  this->outBuffer[BUFF_SIZE - 1] = '\0';
  this->state = STATE_WX;
  this->currentIndex = 0;
}

