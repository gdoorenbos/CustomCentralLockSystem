#ifndef ARDUINO_INTERNAL_PULLUP_PIN_H
#define ARDUINO_INTERNAL_PULLUP_PIN_H

#include "InternalPullupPin.h"

class ArduinoInternalPullupPin : public InternalPullupPin
{
public:
    ArduinoInternalPullupPin(int pin);
    ~ArduinoInternalPullupPin();

private:
    // intentionally not implemented
    ArduinoInternalPullupPin();
};

#endif
