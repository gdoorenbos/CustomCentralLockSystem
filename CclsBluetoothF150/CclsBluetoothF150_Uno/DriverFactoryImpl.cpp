#include "DriverFactoryImpl.h"
#include "PinDefines.h"
#include <BluetoothMateSilverDriver.h>
#include <PowerLocksDriverF150Custom.h>   // todo: replace with derived class

DriverFactoryImpl::DriverFactoryImpl()
    : bluetoothDriver(new BluetoothMateSilverDriver())
    , powerLocksDriver(new PowerLocksDriverF150Custom(POWER_LOCKS_LOCK_PIN, POWER_LOCKS_UNLOCK_PIN))
{
}

DriverFactoryImpl::~DriverFactoryImpl()
{
    delete bluetoothDriver;
    delete powerLocksDriver;
}

DriverFactory* DriverFactoryImpl::getInstance()
{
    static DriverFactory* singleton = 0;

    if( singleton == 0 )
        singleton = new DriverFactoryImpl();

    return singleton;
}

BluetoothDriver* DriverFactoryImpl::getBluetoothDriver()
{
    return bluetoothDriver;
}

PowerLocksDriver* DriverFactoryImpl::getPowerLocksDriver()
{
    return powerLocksDriver;
}

