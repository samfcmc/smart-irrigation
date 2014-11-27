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
#define MESS_FIELD_PARAM	1
#define MESS_FIELD_VALUE 2

// Endianess conversion
#define serial2arduino(VAL)        VAL

uint8_t Configuration::processMessage(char *message)
{
  uint8_t opcode = message[MESS_FIELD_OPC];
  //int parameter = serial2arduino(*(int*)&message[MESS_FIELD_PARAM]);
  uint8_t parameter = message[MESS_FIELD_PARAM];
  switch (opcode) {
    case MESS_GET:
      return this->parameters[parameter];
    case MESS_SET:
      uint8_t value = message[MESS_FIELD_VALUE];
      this->parameters[parameter] = value;

      return value;
  }
}
