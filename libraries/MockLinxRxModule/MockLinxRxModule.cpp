#include "MockLinxRxModule.h"
#include "MockInternalPullupPin.h"

MockLinxRxModule::MockLinxRxModule()
    : LinxRxModule(new MockInternalPullupPin(), new MockInternalPullupPin())
{
}

MockLinxRxModule::~MockLinxRxModule()
{
}

void MockLinxRxModule::raiseRequest(InternalPullupPin* pin)
{
    // ugly downcast, but in this class it should always work.
    ((MockInternalPullupPin*)pin)->setLogicHigh();
}

void MockLinxRxModule::clearRequest(InternalPullupPin* pin)
{
    // ugly downcast, but in this class it should always work.
    ((MockInternalPullupPin*)pin)->setLogicLow();
}

void MockLinxRxModule::raiseLockRequest()
{
    raiseRequest(_lockReqPin);
}

void MockLinxRxModule::raiseUnlockRequest()
{
    raiseRequest(_unlockReqPin);
}

void MockLinxRxModule::clearLockRequest()
{
    clearRequest(_lockReqPin);
}

void MockLinxRxModule::clearUnlockRequest()
{
    clearRequest(_unlockReqPin);
}
