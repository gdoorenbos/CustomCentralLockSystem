#include "GenericOutputPin.h"
#include "GpioDriver.h"

GenericOutputPin::GenericOutputPin(GpioDriver* pinDriver)
    : _pinDriver(pinDriver)
{
    _pinDriver->configureForOutput();
    _pinDriver->setLow();
}

GenericOutputPin::~GenericOutputPin()
{
    delete _pinDriver;
}

void GenericOutputPin::setLow()
{
    _pinDriver->setLow();
}

void GenericOutputPin::setHigh()
{
    _pinDriver->setHigh();
}
