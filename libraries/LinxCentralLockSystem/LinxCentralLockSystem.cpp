#include "LinxCentralLockSystem.h"
#include "LinxRxModule.h"
#include "PowerLocksDriver.h"
#include "PushButtonDriver.h"

// #define KEYFOB_LOCK_BUTTON_DATA_BIT     3
// #define KEYFOB_UNLOCK_BUTTON_DATA_BIT   1

LinxCentralLockSystem::LinxCentralLockSystem(LinxRxModule* rxer, PowerLocksDriver* locksDriver, 
                                             PushButtonDriver* lockButton, PushButtonDriver* unlockButton)
    : _rxer(rxer)
    , _locksDriver(locksDriver)
    , _lockButton(lockButton)
    , _unlockButton(unlockButton)
{
}

LinxCentralLockSystem::~LinxCentralLockSystem()
{
}

void LinxCentralLockSystem::run()
{
    if( _lockButton->isPressed() || _rxer->isLockRequested() )
        _locksDriver->lockDoors();
    else if( _unlockButton->isPressed() || _rxer->isUnlockRequested() )
        _locksDriver->unlockDoors();
}
