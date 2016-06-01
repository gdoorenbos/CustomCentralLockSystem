#ifndef MOCK_POWER_LOCKS_DRIVER_H
#define MOCK_POWER_LOCKS_DRIVER_H

#include <PowerLocksDriver.h>

class MockPowerLocksDriver : public PowerLocksDriver
{
public:
    MockPowerLocksDriver();
    ~MockPowerLocksDriver();

    // inherited
    void lockDoors() const;
    void unlockDoors() const;

    // mock method to check status
    bool areDoorsLocked() const;

private:
    bool doorsAreLocked;
};

#endif
