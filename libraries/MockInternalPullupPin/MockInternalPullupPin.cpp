#include "MockInternalPullupPin.h"
#include "MockGpioDriver.h"

MockInternalPullupPin::MockInternalPullupPin(MockGpioDriver* pinDriver)
    : InternalPullupPin(pinDriver)
{
}

MockInternalPullupPin::MockInternalPullupPin()
    : InternalPullupPin(new MockGpioDriver())
{
}

MockInternalPullupPin::~MockInternalPullupPin()
{
}

void MockInternalPullupPin::setLogicHigh()
{
    _pinDriver->setLow();
}

void MockInternalPullupPin::setLogicLow()
{
    _pinDriver->setHigh();
}
