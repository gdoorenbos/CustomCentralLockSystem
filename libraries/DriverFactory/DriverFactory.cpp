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

LinxRxModule* DriverFactory::getLinxRxModule()
{
    return 0;
}

PowerLocksDriver* DriverFactory::getPowerLocksDriver()
{
    return 0;
}

PushButtonDriver* DriverFactory::getLockButton()
{
    return 0;
}

PushButtonDriver* DriverFactory::getUnlockButton()
{
    return 0;
}
