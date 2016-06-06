#include "MockPushButtonDriver.h"

MockPushButtonDriver::MockPushButtonDriver()
    : buttonIsPressed(false)
{
}

MockPushButtonDriver::~MockPushButtonDriver()
{
}

void MockPushButtonDriver::press()
{
    buttonIsPressed = true;
}

void MockPushButtonDriver::release()
{
    buttonIsPressed = false;
}

bool MockPushButtonDriver::isPressed() const
{
    return buttonIsPressed;
}
