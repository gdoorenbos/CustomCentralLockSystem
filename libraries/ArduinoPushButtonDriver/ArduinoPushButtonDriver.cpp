#include "ArduinoPushButtonDriver.h"
#include "ArduinoGpioDriver.h"

ArduinoPushButtonDriver::ArduinoPushButtonDriver(int pin)
    : PushButtonDriver(new ArduinoGpioDriver(pin))
{
}

ArduinoGpioDriver::~ArduinoGpioDriver()
{
}
