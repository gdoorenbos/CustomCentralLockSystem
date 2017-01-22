#include "MockGpioDriver.h"

MockGpioDriver::MockGpioDriver(int pin)
    : GpioDriver(pin)
    , outputConfigFlag(false)
    , inputConfigFlag(false)
    , inputPullupConfigFlag(false)
    , pinIsLow(true)
    , lastDebounceTime(0)
{
}

MockGpioDriver::~MockGpioDriver()
{
}

void MockGpioDriver::resetConfigFlags()
{
    outputConfigFlag = false;
    inputConfigFlag = false;
    inputPullupConfigFlag = false;
}

void MockGpioDriver::configureForOutput()
{
    resetConfigFlags();
    outputConfigFlag = true;
}

void MockGpioDriver::configureForInput()
{
    resetConfigFlags();
    inputConfigFlag = true;
}

void MockGpioDriver::configureForInputPullup()
{
    resetConfigFlags();
    inputPullupConfigFlag = true;
}

bool MockGpioDriver::isConfiguredForOutput()
{
    return outputConfigFlag;
}

bool MockGpioDriver::isConfiguredForInput()
{
    return inputConfigFlag;
}

bool MockGpioDriver::isConfiguredForInputPullup()
{
    setHigh();
    return inputPullupConfigFlag;
}

void MockGpioDriver::setHigh()
{
    pinIsLow = false;
}

void MockGpioDriver::setLow()
{
    pinIsLow = true;
}

bool MockGpioDriver::isHigh()
{
    return !pinIsLow;
}

bool MockGpioDriver::isLow()
{
    return pinIsLow;
}
    
bool MockGpioDriver::isHighWithDebounce(int debounceTime)
{
    lastDebounceTime = debounceTime;
    return isHigh();
}

bool MockGpioDriver::isLowWithDebounce(int debounceTime)
{
    lastDebounceTime = debounceTime;
    return isLow();
}
