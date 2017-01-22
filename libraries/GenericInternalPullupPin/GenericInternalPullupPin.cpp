#include "GenericInternalPullupPin.h"
#include "GpioDriver.h"

GenericInternalPullupPin::GenericInternalPullupPin(GpioDriver* pinDriver)
    : _pinDriver(pinDriver)
{
    pinSetup();
}

GenericInternalPullupPin::~GenericInternalPullupPin()
{
    delete _pinDriver;
}

void GenericInternalPullupPin::pinSetup()
{
    _pinDriver->configureForInputPullup();
}

bool GenericInternalPullupPin::isLogicHigh()
{
    return _pinDriver->isLowWithDebounce();
}

bool GenericInternalPullupPin::isLogicLow()
{
    return _pinDriver->isHighWithDebounce();
}
