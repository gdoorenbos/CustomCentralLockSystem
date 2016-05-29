#ifndef POWER_LOCKS_DRIVER_F150_CUSTOM
#define POWER_LOCKS_DRIVER_F150_CUSTOM

#include <PowerLocksDriver.h>

class PowerLocksDriverF150Custom : public PowerLocksDriver
{
public:
    PowerLocksDriverF150Custom();
    ~PowerLocksDriverF150Custom();

    void lockDoors();
    void unlockDoors();
};

#endif