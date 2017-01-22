#ifndef ARDUINO_PUSH_BUTTON_DRIVER_H
#define ARDUINO_PUSH_BUTTON_DRIVER_H

#include "PushButtonDriver.h"

class ArduinoPushButtonDriver : public PushButtonDriver
{
public:
    ArduinoPushButtonDriver(int pin);
    ~ArduinoPushButtonDriver();

private:
    // intentionally not implemented
    ArduinoPushButtonDriver();
};

#endif
