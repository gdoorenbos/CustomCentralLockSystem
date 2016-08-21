#include "DriverFactoryImpl.h"
#include <LinxCentralLockSystem.h>

LinxCentralLockSystem* cls;

void setup()
{
    DriverFactory* df = DriverFactoryImpl::getInstance();
    cls = new LinxCentralLockSystem( df->getLinxRxModule()
                                   , df->getPowerLocksDriver()
                                   , df->getLockButton()
                                   , df->getUnlockButton() );
}

void loop()
{
    cls->run();
}

