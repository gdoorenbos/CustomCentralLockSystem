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

void MockPushButtonDriver::unpress()
{
    buttonIsPressed = false;
}

bool MockPushButtonDriver::isButtonPressed() const
{
    return buttonIsPressed;
}
