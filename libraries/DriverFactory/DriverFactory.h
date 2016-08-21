#ifndef DRIVER_FACTORY_H
#define DRIVER_FACTORY_H

// forward declarations
class BluetoothDriver;
class LinxRxModule;
class PowerLocksDriver;
class PushButtonDriver;

class DriverFactory
{
protected:
    // don't instantiate this class directly
    DriverFactory();

public:
    virtual ~DriverFactory();
    virtual BluetoothDriver* getBluetoothDriver();
    virtual LinxRxModule* getLinxRxModule();
    virtual PowerLocksDriver* getPowerLocksDriver();
    virtual PushButtonDriver* getLockButton();
    virtual PushButtonDriver* getUnlockButton();
};

#endif
