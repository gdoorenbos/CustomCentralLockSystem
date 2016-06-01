#include "MockPowerLocksDriver.h"

MockPowerLocksDriver::MockPowerLocksDriver()
    : doorsAreLocked(false)
{
}

MockPowerLocksDriver::~MockPowerLocksDriver()
{
}

void MockPowerLocksDriver::lockDoors() const
{
    doorsAreLocked = true;
}

void MockPowerLocksDriver::unlockDoors() const
{
    doorsAreLocked = false;
}

bool MockPowerLocksDriver::areDoorsLocked() const
{
    return doorsAreLocked;
}
