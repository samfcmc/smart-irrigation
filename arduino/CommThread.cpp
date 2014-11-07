#include <Arduino.h>
#include "CommThread.h"



CommThread::CommThread(): Thread() {
  _state = STATE_IDLE;
}




void CommThread::run()
{

}





bool CommThread::messageAvailable()
{
  /* TODO */
}

bool CommThread::isFree()
{
  /* TODO */
}

void CommThread::getMessage(void *buffer, int num)
{
  /* TODO */
}

void CommThread::sendMessage(void *buffer, int num)
{
  /* TODO */
}

