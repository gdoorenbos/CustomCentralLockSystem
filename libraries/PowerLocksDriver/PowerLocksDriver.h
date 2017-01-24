#ifndef POWER_LOCKS_DRIVER_H
#define POWER_LOCKS_DRIVER_H

#include "GenericOutputPin.h"

class GpioDriver;

/* This driver controls an H-Bridge with two digital inputs. When one
 * input is pulled high the locks will lock, and when the other input
 * is pulled high the locks will unlock. The resting state should be 
 * both inputs low. At no point should both inputs be pulled high at 
 * the same time. 
 */
class PowerLocksDriver
{
public:
    PowerLocksDriver(GpioDriver* lockCmdPin, GpioDriver* unlockCmdPin);
    virtual ~PowerLocksDriver();

    virtual void lockDoors();
    virtual void unlockDoors();

    virtual void waitForLocksToSettle() = 0;

private:
    GenericOutputPin _lockCmdPin;
    GenericOutputPin _unlockCmdPin;

    // only _lockCmdPin or _unlockCmdPin should be passed to this method.
    void pulseCommandPin(GenericOutputPin &commandPin);

    // intentionally not implemented
    PowerLocksDriver();
};

#endif
