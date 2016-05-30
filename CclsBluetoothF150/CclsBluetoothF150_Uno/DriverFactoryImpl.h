#ifndef DRIVER_FACTORY_IMPL_H
#define DRIVER_FACTORY_IMPL_H

#include <DriverFactory.h>

class DriverFactoryImpl : public DriverFactory
{
protected:
    // don't instantiate this class directly 
    DriverFactoryImpl();
    ~DriverFactoryImpl();

public:
    static DriverFactory* getInstance();

    // driver getters
    BluetoothDriver* getBluetoothDriver();
    PowerLocksDriver* getPowerLocksDriver();
    PushButtonDriver* getLockButton();
    PushButtonDriver* getUnlockButton();

private:
    BluetoothDriver* bluetoothDriver;
    PowerLocksDriver* powerLocksDriver;
    PushButtonDriver* lockButton;
    PushButtonDriver* unlockButton;
};

#endif

