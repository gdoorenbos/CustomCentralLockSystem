#ifndef ARDUINO_POWER_LOCKS_DRIVER_H
#define ARDUINO_POWER_LOCKS_DRIVER_H

#include "PowerLocksDriver.h"

class ArduinoPowerLocksDriver : public PowerLocksDriver
{
public:
    ArduinoPowerLocksDriver(int lockPin, int unlockPin);
    ~ArduinoPowerLocksDriver();

    // overridden - delays for 0.7s, the OEM standard
    void waitForLocksToSettle();

private:
    // intentionally not implemented
};

#endif
