#include "ArduinoInternalPullupPin.h"
#include "ArduinoGpioDriver.h"

ArduinoInternalPullupPin::ArduinoInternalPullupPin(int pin)
    : GenericInternalPullupDriver(new ArduinoGpioDriver(pin))
{
}

ArduinoInternalPullupPin::~ArduinoInternalPullupPin()
{
}
