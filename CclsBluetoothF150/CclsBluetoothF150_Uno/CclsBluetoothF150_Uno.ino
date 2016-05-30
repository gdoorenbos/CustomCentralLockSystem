#include "DriverFactoryImpl.h"
#include <BluetoothCentralLockSystem.h>

void setup()
{
    DriverFactory* df = DriverFactoryImpl::getInstance();
    BluetoothCentralLockSystem cls(df->getBluetoothDriver(), df->getPowerLocksDriver());
}

void loop()
{
    
}

