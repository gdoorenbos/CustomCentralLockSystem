#include "DriverFactoryImpl.h"
#include <CentralLockSystemF150Custom.h>

//DriverFactory* df;
//BluetoothDriver* bluetoothDriver
//CentralLockSystemF150Custom cls;

void setup()
{
    DriverFactory* df = DriverFactoryImpl::getInstance();
    CentralLockSystemF150Custom cls(df->getBluetoothDriver());
//    df = DriverFactoryImpl::getInstance();
}

void loop()
{
    
}


