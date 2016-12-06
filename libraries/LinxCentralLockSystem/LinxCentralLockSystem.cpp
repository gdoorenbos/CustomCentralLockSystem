#include "LinxCentralLockSystem.h"
#include "LinxRxModule.h"
#include "PowerLocksDriver.h"

#define KEYFOB_LOCK_BUTTON_DATA_BIT     3
#define KEYFOB_UNLOCK_BUTTON_DATA_BIT   1

LinxCentralLockSystem::LinxCentralLockSystem(LinxRxModule* rxer, PowerLocksDriver* locksDriver)
    : rxer(rxer)
    , locksDriver(locksDriver)
{
}

LinxCentralLockSystem::~LinxCentralLockSystem()
{
}

void LinxCentralLockSystem::run()
{
    if( rxer->hasValidTransmission() )
        decipherRxModuleTransmission();
}

void LinxCentralLockSystem::decipherRxModuleTransmission()
{
    if( rxer->getDataBit(KEYFOB_LOCK_BUTTON_DATA_BIT) )
        locksDriver->lockDoors();
    else if( rxer->getDataBit(KEYFOB_UNLOCK_BUTTON_DATA_BIT) )
        locksDriver->unlockDoors();
}
