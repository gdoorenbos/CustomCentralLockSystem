#include "MockLinxRxModule.h"
#include "MockGpioDriver.h"

MockLinxRxModule::MockLinxRxModule(MockGpioDriver* lockReqPin, MockGpioDriver* unlockReqPin)
    : LinxRxModule(lockReqPin, unlockReqPin)
    , _lockReqPinDriver(lockReqPin)
    , _unlockReqPinDriver(unlockReqPin)
{
}

MockLinxRxModule::MockLinxRxModule()
    : LinxRxModule(new MockGpioDriver(), new MockGpioDriver())
    , _lockReqPinDriver()
    , _unlockReqPinDriver()
{
}

MockLinxRxModule::~MockLinxRxModule()
{
}

void MockLinxRxModule::raiseRequest(MockGpioDriver* pin)
{
    pin->setLow();
}

void MockLinxRxModule::clearRequest(MockGpioDriver* pin)
{
    pin->setHigh();
}

void MockLinxRxModule::raiseLockRequest()
{
    raiseRequest(_lockReqPinDriver);
}

void MockLinxRxModule::clearLockRequest()
{
    clearRequest(_lockReqPinDriver);
}

void MockLinxRxModule::raiseUnlockRequest()
{
    raiseRequest(_unlockReqPinDriver);
}

void MockLinxRxModule::clearUnlockRequest()
{
    clearRequest(_unlockReqPinDriver);
}
