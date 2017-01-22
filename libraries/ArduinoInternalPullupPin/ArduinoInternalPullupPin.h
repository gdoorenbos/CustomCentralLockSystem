#ifndef ARDUINO_INTERNAL_PULLUP_PIN_H
#define ARDUINO_INTERNAL_PULLUP_PIN_H

#include "GenericInternalPullupPin.h"

class ArduinoInternalPullupPin : GenericInternalPullupPin
{
public:
    ArduinoInternalPullupPin(int pin);
    ~ArduinoInternalPullupPin();

private:
    // intentionally not implemented
    ArduinoInternalPullupPin();
}

#endif
