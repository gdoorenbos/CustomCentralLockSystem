#include "GpioHandler.h"

GpioHandler::GpioHandler()
{
}

GpioHandler::~GpioHandler()
{
}

void GpioHandler::setPin(int pin, bool value)
{
    if(value)
        setPinHigh(pin);
    else
        setPinLow(pin);
}
