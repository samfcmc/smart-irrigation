#include <Arduino.h>
#include "Configuration.h"
#include "CommThread.h"

//#include "common.h"

#define TIMEOUT 300

/*ConfigThread::ConfigThread(): Thread()
{
  this->commThread = CommThread::getInstance();
}*/

Configuration::Configuration() {
  int i;
  for(i = 0; i < PARAM_COUNT; i++) {
    this->parameters[i] = 0;
  }
}

/*void ConfigThread::run()
{
  if (commThread->hasMessageAvailable()) {
    union {
      char messBuff[BUFF_SIZE];
      struct {
	uint8_t opcode;
      } mess_generic;
      struct {
	uint8_t opcode;
	uint8_t param_id;
      } mess_get;
      struct {
	uint8_t opcode;
	uint8_t param_id;
	uint8_t val;
      } mess_set;
    } buff;
    
    commThread->getMessage(buff.messBuff, BUFF_SIZE);
    
    switch (buff.mess_generic.opcode) {
      case MESS_GET:
	break;
      case MESS_SET:
	_params[buff.mess_set.param_id] = buff.mess_set.val;
	break;
    }
  }
}*/

uint8_t Configuration::processMessage(char *message) {
  uint8_t opcode = message[0];
  uint8_t parameter = message[1];
  //uint8_t value = message[2];

  switch (opcode) {
    case MESS_GET:
      return this->parameters[parameter];
    case MESS_SET:
      uint8_t value = message[2];
      this->parameters[parameter] = value;

      return value;
  }
    
    /*switch (buff.mess_generic.opcode) {
      case MESS_GET:
  break;
      case MESS_SET:
  _params[buff.mess_set.param_id] = buff.mess_set.val;
  break;
    }
  }*/
}
