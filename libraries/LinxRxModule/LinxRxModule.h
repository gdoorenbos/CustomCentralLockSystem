#ifndef LINX_RX_MODULE_H
#define LINX_RX_MODULE_H

#include "GenericInternalPullupPin.h"

class LinxRxModule
{
public:
    LinxRxModule(GpioDriver* lockReqPin, GpioDriver* unlockReqPin);
    virtual ~LinxRxModule();

    bool isLockRequested();
    bool isUnlockRequested();

private:
    GenericInternalPullupPin _lockReqPin;
    GenericInternalPullupPin _unlockReqPin;
};

#endif
