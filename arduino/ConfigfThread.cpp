#include <Arduino.h>
#include "ConfigfThread.h"
#include "CommThread.h"

#include "common.h"

#define TIMEOUT 300

ConfigfThread::ConfigfThread(): Thread()
{
  
}

void ConfigfThread::run()
{
  if (commThread.hasMessageAvailable()) {
  }
}
