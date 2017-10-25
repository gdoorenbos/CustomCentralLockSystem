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
    return _lockReqPin->isLogicHigh();
}

bool LinxRxModule::isUnlockRequested()
{
    return _unlockReqPin->isLogicHigh();
}
