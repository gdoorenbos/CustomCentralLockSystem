#include "PushButtonDriver.h"
#include "GpioDriver.h"

PushButtonDriver::PushButtonDriver(GpioDriver* pinDriver)
    : GenericInternalPullupPin(pinDriver)
{
}

PushButtonDriver::~PushButtonDriver()
{
}

bool PushButtonDriver::isPressed() const
{
    return isLogicHigh();
}
