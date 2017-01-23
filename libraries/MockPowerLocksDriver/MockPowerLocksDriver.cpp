#include "MockPowerLocksDriver.h"
#include "MockGpioDriver.h"

MockPowerLocksDriver::MockPowerLocksDriver(MockGpioDriver* lockPinDriver, MockGpioDriver* unlockPinDriver)
    : PowerLocksDriver(lockPinDriver, unlockPinDriver)
    , doorsAreLocked(false)
{
}

MockPowerLocksDriver::MockPowerLocksDriver()
    : PowerLocksDriver(new MockGpioDriver(), new MockGpioDriver())
    , doorsAreLocked(false)
{
}

MockPowerLocksDriver::~MockPowerLocksDriver()
{
}

void MockPowerLocksDriver::lockDoors()
{
    PowerLocksDriver::lockDoors();
    doorsAreLocked = true;
}

void MockPowerLocksDriver::unlockDoors()
{
    PowerLocksDriver::unlockDoors();
    doorsAreLocked = false;
}

void MockPowerLocksDriver::waitForLocksToSettle()
{
}

bool MockPowerLocksDriver::areDoorsLocked() const
{
    return doorsAreLocked;
}
