#include "DriverFactoryImpl.h"
#include <BluetoothCentralLockSystem.h>

BluetoothCentralLockSystem* cls;

void setup()
{
    DriverFactory* df = DriverFactoryImpl::getInstance();
    cls = new BluetoothCentralLockSystem( df->getBluetoothDriver()
                                        , df->getPowerLocksDriver()
                                        , df->getLockButton()
                                        , df->getUnlockButton() );
}

void loop()
{
    cls->run();
}

