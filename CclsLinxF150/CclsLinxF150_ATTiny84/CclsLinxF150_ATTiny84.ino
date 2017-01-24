/* Add the following URL to the boards manager to build on the ATTiny84
 *  
 *  https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json
 * 
 */

#include "DriverFactoryImpl.h"
#include "LinxCentralLockSystem.h"

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

