#include "DriverFactoryImpl.h"
#include <CentralLockSystemF150Custom.h>

void setup()
{
    DriverFactory* df = DriverFactoryImpl::getInstance();
    CentralLockSystemF150Custom cls(df->getBluetoothDriver());
}

void loop()
{
    
}


