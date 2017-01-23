#include "MockGpioDriver.h"

MockGpioDriver::MockGpioDriver()
    : GpioDriver()
    , outputConfigFlag(false)
    , inputConfigFlag(false)
    , inputPullupConfigFlag(false)
    , pinIsLow(true)
    , lastDebounceTime(0)
    , log("")
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
    setHigh();
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
    return inputPullupConfigFlag;
}

void MockGpioDriver::setHigh()
{
    log += "H";
    pinIsLow = false;
}

void MockGpioDriver::setLow()
{
    log += "L";
    pinIsLow = true;
}

bool MockGpioDriver::isHigh() const
{
    return !pinIsLow;
}

bool MockGpioDriver::isLow() const
{
    return pinIsLow;
}
    
bool MockGpioDriver::isHighWithDebounce(int debounceTime) const
{
    lastDebounceTime = debounceTime;
    return isHigh();
}

bool MockGpioDriver::isLowWithDebounce(int debounceTime) const
{
    lastDebounceTime = debounceTime;
    return isLow();
}

std::string MockGpioDriver::getLog()
{
    return log;
}

void MockGpioDriver::clearLog()
{
    log = "";
}
