#include "PowerLocksDriver.h"
#include "GpioDriver.h"

PowerLocksDriver::PowerLocksDriver(GpioDriver* lockCmdPin, GpioDriver* unlockCmdPin)
    : _lockCmdPin(GenericOutputPin(lockCmdPin))
    , _unlockCmdPin(GenericOutputPin(unlockCmdPin))
{
}

PowerLocksDriver::~PowerLocksDriver()
{
}

void PowerLocksDriver::pulseCommandPin(GenericOutputPin &commandPin)
{
    commandPin.setHigh();
    waitForLocksToSettle();
    commandPin.setLow();
}

void PowerLocksDriver::lockDoors()
{
    pulseCommandPin(_lockCmdPin);
}

void PowerLocksDriver::unlockDoors()
{
    pulseCommandPin(_unlockCmdPin);
}
