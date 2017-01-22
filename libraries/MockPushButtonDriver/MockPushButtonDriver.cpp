#include "MockPushButtonDriver.h"
#include "MockGpioDriver.h"

MockPushButtonDriver::MockPushButtonDriver()
    : PushButtonDriver(new MockGpioDriver())
{
}

MockPushButtonDriver::~MockPushButtonDriver()
{
}

void MockPushButtonDriver::press()
{
    _pinDriver->setLow();
}

void MockPushButtonDriver::release()
{
    _pinDriver->setHigh();
}
