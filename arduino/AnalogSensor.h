#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#include <Thread.h>
#include "CommThread.h"



/**
 * Class to read analog sensors connected to analog pins that
 * give us analog inputs.
 * 
 * Reminder!: Resistive sensors and pressure buttons require pull-down
 *            resistors, to avoid high-impedance inputs, and unless you
 *            want a short-circuit!
 *            Potentiometers don't need pull-down resistors.
 */
class AnalogSensor {
private:
        int _pin;
        float _scale;
        
        int _lastRes;
        int _physicalValue;

public:
        /**
         * Argument "pin" specifies the
         * Argument "scale" is to allow convertions.
         *    Analog reads normally give 1024 for 5V.
         *    Argument "scale" should be MAX_PHYSICAL/2014, being MAX_PHYSICAL
         *    the pysical quantity that corresponds to a 0 ohm sensor
         *    resistance (assuming the other terminal is connected to a 5V pin.
         */
        AnalogSensor(int pin, float scale = 1);
        
        int getPhysicalValue() {
          return _physicalValue;
        }

        int readSensor();
};

class HumiditySensor : public AnalogSensor {
public:
        HumiditySensor(int pin) : AnalogSensor(pin, 1) {  }
};

#endif