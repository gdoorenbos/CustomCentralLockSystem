#include "ArduinoOutputPin.h"
#include "ArduinoGpioDriver.h"

ArduinoOutputPin::ArduinoOutputPin(int pin)
    : GenericOutputPin(ArduinoGpioDriver(pin))
{
}

ArduinoOutputPin::~ArduinoOutputPin();
{
}
