#include <LinxCentralLockSystem.h>
#include "DriverFactoryImpl.h"
#include "LinxDeviceAddress.h"

LinxCentralLockSystem* cls;

void setup()
{
    DriverFactory* df = DriverFactoryImpl::getInstance();
    df->getLinuxRxModule()->setAddress(LINX_DEVICE_ADDRESS);
    cls = new LinxCentralLockSystem( df->getLinxRxModule()
                                   , df->getPowerLocksDriver() );
}

void loop()
{
    cls->run();
}

