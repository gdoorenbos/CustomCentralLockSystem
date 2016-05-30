#ifndef POWER_LOCKS_DRIVER_H
#define POWER_LOCKS_DRIVER_H

class PowerLocksDriver
{
protected:
    // don't instantiate this class directly
    PowerLocksDriver();

public:
    virtual ~PowerLocksDriver();
    virtual void lockDoors() const = 0;
    virtual void unlockDoors() const = 0;
};

#endif
