#include <Arduino.h>
#include "AnalogSensor.h"

#define TIMEOUT 300



AnalogSensor::AnalogSensor(int pin, float scale) {
  _pin = pin;
  _scale = scale;
}

int AnalogSensor::readSensor()
{
  int res;
  if ((res = analogRead(_pin)) != _lastRes)
  {
    _lastRes = res;
    _physicalValue = (int)((float)res*_scale);
  }
  return _physicalValue;
}
