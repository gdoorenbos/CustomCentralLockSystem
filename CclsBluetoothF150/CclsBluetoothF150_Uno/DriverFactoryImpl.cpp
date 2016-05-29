#include "DriverFactoryImpl.h"
#include <BluetoothMateSilverDriver.h>
#include <PowerLocksDriver.h>   // todo: replace with derived class

DriverFactoryImpl::DriverFactoryImpl()
{
}

DriverFactoryImpl::~DriverFactoryImpl()
{
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
    return new BluetoothMateSilverDriver();
}

PowerLocksDriver* DriverFactoryImpl::getPowerLocksDriver()
{
    //todo: return power locks driver
    return 0;
}
