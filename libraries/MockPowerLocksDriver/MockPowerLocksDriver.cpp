#include "MockPowerLocksDriver.h"

MockPowerLocksDriver::MockPowerLocksDriver()
    : doorsAreLocked(false)
{
}

MockPowerLocksDriver::~MockPowerLocksDriver()
{
}

void MockPowerLocksDriver::lockDoors()
{
    doorsAreLocked = true;
}

void MockPowerLocksDriver::unlockDoors()
{
    doorsAreLocked = false;
}

bool MockPowerLocksDriver::areDoorsLocked() const
{
    return doorsAreLocked;
}
