#include "DriverFactory.h"

DriverFactory::DriverFactory()
{
}

DriverFactory::~DriverFactory()
{
}

BluetoothDriver* DriverFactory::getBluetoothDriver()
{
    return 0;
}

PowerLocksDriver* DriverFactory::getPowerLocksDriver()
{
    return 0;
}
