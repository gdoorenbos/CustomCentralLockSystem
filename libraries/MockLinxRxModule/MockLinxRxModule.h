#ifndef MOCK_LINX_RX_MODULE_H
#define MOCK_LINX_RX_MODULE_H

#include "LinxRxModule.h"

class MockGpioDriver;

class MockLinxRxModule : public LinxRxModule
{
public:
    MockLinxRxModule(MockGpioDriver* lockReqPin, MockGpioDriver* unlockReqPin);
    MockLinxRxModule();
    ~MockLinxRxModule();

    // mock methods for testing
    void raiseLockRequest();
    void clearLockRequest();
    void raiseUnlockRequest();
    void clearUnlockRequest();

private:
    MockGpioDriver* _lockReqPinDriver;
    MockGpioDriver* _unlockReqPinDriver;

    // only _lockReqPinDriver or _unlockReqPinDriver should be passed to these methods
    void raiseRequest(MockGpioDriver* pin);
    void clearRequest(MockGpioDriver* pin);

    // intentionally not implemented
    MockLinxRxModule();
};

#endif
