#include "ArduinoInternalPullupPin.h"
#include "ArduinoGpioDriver.h"

ArduinoInternalPullupPin::ArduinoInternalPullupPin(int pin)
    : InternalPullupPin(new ArduinoGpioDriver(pin))
{
}

ArduinoInternalPullupPin::~ArduinoInternalPullupPin()
{
}
