#ifndef MOCK_LINX_RX_MODULE_H
#define MOCK_LINX_RX_MODULE_H

#include "LinxRxModule.h"

class MockInternalPullupPin;

class MockLinxRxModule : public LinxRxModule
{
public:
    MockLinxRxModule();
    ~MockLinxRxModule();

    // mock methods for testing
    void raiseLockRequest();
    void raiseUnlockRequest();
    void clearLockRequest();
    void clearUnlockRequest();

private:
    // only _lockReqPinDriver or _unlockReqPinDriver should be passed to these methods
    void raiseRequest(InternalPullupPin* pin);
    void clearRequest(InternalPullupPin* pin);
};

#endif
