#include <Arduino.h>
#include "ConfigThread.h"
#include "CommThread.h"

#include "common.h"

#define TIMEOUT 300

ConfigThread::ConfigThread(): Thread()
{
  this->commThread = CommThread::getInstance();
}

/*
 * Protocol for setting registers:
 *  Two commands: GET and SET.
 *  Each of them includes the parameter id.
 */
enum Opcode {
  MESS_GET = 1,
  MESS_SET = 2,
};

void ConfigThread::run()
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
}
