#include <Arduino.h>
#include "Configuration.h"
#include "CommThread.h"

#define TIMEOUT 300



Configuration::Configuration() {
  int i;
  for(i = 0; i < PARAM_COUNT; i++) {
    this->parameters[i] = 0;
  }
}

#define MESS_FIELD_OPC	0
#define MESS_FIELD_PARAM	0

uint8_t Configuration::processMessage(char *message)
{
  uint8_t opcode = message[MESS_FIELD_OPC];
  uint8_t parameter = message[MESS_FIELD_PARAM];
  //uint8_t value = message[2];

  switch (opcode) {
    case MESS_GET:
      return this->parameters[parameter];
    case MESS_SET:
      uint8_t value = message[2];
      this->parameters[parameter] = value;

      return value;
  }
}
