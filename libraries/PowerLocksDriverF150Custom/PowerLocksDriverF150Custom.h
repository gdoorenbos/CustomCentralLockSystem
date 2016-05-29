#ifndef POWER_LOCKS_DRIVER_F150_CUSTOM
#define POWER_LOCKS_DRIVER_F150_CUSTOM

#include <PowerLocksDriver.h>

class PowerLocksDriverF150Custom : public PowerLocksDriver
{
public:
    /** This driver controls an H-Bridge with two digital inputs. When one
     *  input is pulled high the locks will lock, and when the other input
     *  is pulled high the locks will unlock. The resting state should be 
     *  both inputs low. At no point should both inputs be pulled high at 
     *  the same time. 
     */
    PowerLocksDriverF150Custom(int lockPin, int unlockPin);
    ~PowerLocksDriverF150Custom();

    void lockDoors();
    void unlockDoors();

private:
    // intentionally unimplemented - use the public ctor with arguments
    PowerLocksDriverF150Custom();

    /* Waits for locks to settle up or down after pulling either lock or
     * unlock pin high. 
     */
    void waitForLocksToSettle();

    // member variables
    int lockPin;
    int unlockPin;
};

#endif
