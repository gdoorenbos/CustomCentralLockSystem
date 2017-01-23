#include "LinxRxModule.h"
#include "GenericInternalPullupPin.h"
#include "GpioDriver.h"

LinxRxModule::LinxRxModule(GpioDriver* lockReqPin, GpioDriver* unlockReqPin)
    : _lockReqPin(GenericInternalPullupPin(lockReqPin))
    , _unlockReqPin(GenericInternalPullupPin(unlockReqPin))
{
}

LinxRxModule::~LinxRxModule()
{
}

bool LinxRxModule::isLockRequested()
{
    _lockReqPin.isLogicHigh();
}

bool LinxRxModule::isUnlockRequested()
{
    _unlockReqPin.isLogicHigh();
}
