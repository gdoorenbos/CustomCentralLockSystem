#ifndef LINXCENTRALLOCKSYSTEM_H
#define LINXCENTRALLOCKSYSTEM_H

class LinxRxModule;
class PowerLocksDriver;
class PushButtonDriver;

class LinxCentralLockSystem
{
public:
    LinxCentralLockSystem(LinxRxModule* rxer, PowerLocksDriver* locksDriver, 
                          PushButtonDriver* lockButton, PushButtonDriver* unlockButton);
    ~LinxCentralLockSystem();

    void run();

private:
    // intentionally not implemented
    LinxCentralLockSystem();

    // helper method
    // void decipherRxModuleTransmission();

    // member variables
    LinxRxModule* _rxer;
    PowerLocksDriver* _locksDriver;
    PushButtonDriver* _lockButton;
    PushButtonDriver* _unlockButton;
};

#endif
