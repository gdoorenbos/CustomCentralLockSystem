#include <LinxCentralLockSystem.h>
#include "DriverFactoryImpl.h"
#include "LinxDeviceAddress.h"

LinxCentralLockSystem* cls;

void setup()
{
    DriverFactory* df = DriverFactoryImpl::getInstance();
    cls = new LinxCentralLockSystem( df->getLinxRxModule()
                                   , df->getPowerLocksDriver()
                                   , df->getLockButton()
                                   , df->getUnlockButton() );
    cls->setDeviceAddress(LINX_DEVICE_ADDRESS);
}

void loop()
{
    cls->run();
}

