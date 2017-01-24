#include "InternalPullupPin.h"
#include "GpioDriver.h"

InternalPullupPin::InternalPullupPin(GpioDriver* pinDriver)
    : _pinDriver(pinDriver)
{
    pinSetup();
}

InternalPullupPin::~InternalPullupPin()
{
    delete _pinDriver;
}

void InternalPullupPin::pinSetup()
{
    _pinDriver->configureForInputPullup();
}

bool InternalPullupPin::isLogicHigh() const
{
    return _pinDriver->isLowWithDebounce();
}

bool InternalPullupPin::isLogicLow() const
{
    return _pinDriver->isHighWithDebounce();
}
