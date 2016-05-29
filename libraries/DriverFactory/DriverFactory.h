#ifndef DRIVER_FACTORY_H
#define DRIVER_FACTORY_H

// forward declarations
class BluetoothDriver;
class PowerLocksDriver;

class DriverFactory
{
protected:
    // don't instantiate this class directly
    DriverFactory();

public:
    virtual ~DriverFactory();
    virtual BluetoothDriver* getBluetoothDriver();
    virtual PowerLocksDriver* getPowerLocksDriver();
};

#endif
