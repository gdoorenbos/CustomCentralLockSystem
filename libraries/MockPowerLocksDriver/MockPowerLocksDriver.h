#ifndef MOCK_POWER_LOCKS_DRIVER_H
#define MOCK_POWER_LOCKS_DRIVER_H

#include "PowerLocksDriver.h"
class MockGpioDriver;

class MockPowerLocksDriver : public PowerLocksDriver
{
public:
    MockPowerLocksDriver(MockGpioDriver* lockPinDriver, MockGpioDriver* unlockPinDriver);
    MockPowerLocksDriver();
    ~MockPowerLocksDriver();

    // overridden
    void lockDoors();
    void unlockDoors();
    void waitForLocksToSettle();

    // mock method to check status
    bool areDoorsLocked() const;

private:
    bool doorsAreLocked;
};

#endif
