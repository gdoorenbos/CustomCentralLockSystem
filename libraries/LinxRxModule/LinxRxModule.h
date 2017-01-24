#ifndef LINX_RX_MODULE_H
#define LINX_RX_MODULE_H

class InternalPullupPin;

class LinxRxModule
{
public:
    LinxRxModule(InternalPullupPin* lockReqPin, InternalPullupPin* unlockReqPin);
    virtual ~LinxRxModule();

    bool isLockRequested();
    bool isUnlockRequested();

protected:
    InternalPullupPin* _lockReqPin;
    InternalPullupPin* _unlockReqPin;
};

#endif
