#include "LinxRxModule.h"
#include "InternalPullupPin.h"

LinxRxModule::LinxRxModule(InternalPullupPin* lockReqPin, InternalPullupPin* unlockReqPin)
    : _lockReqPin(lockReqPin)
    , _unlockReqPin(unlockReqPin)
{
}

LinxRxModule::~LinxRxModule()
{
}

bool LinxRxModule::isLockRequested()
{
    _lockReqPin->isLogicHigh();
}

bool LinxRxModule::isUnlockRequested()
{
    _unlockReqPin->isLogicHigh();
}
